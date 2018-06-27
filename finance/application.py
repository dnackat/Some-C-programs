import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, Markup
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash
import re

from helpers import apology, login_required, lookup, usd

# Ensure environment variable is set


if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get user's cash balance
    row = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
    cash = row[0]["cash"]

    # Get user's stocks
    stocks = db.execute(
        "SELECT symbol, SUM(shares) AS total_shares FROM portfolio WHERE user_id=:id GROUP BY symbol HAVING total_shares > 0 ORDER BY date", id=session["user_id"])

    # Iterate through stocks and calculate current value of holdings
    curr_holdings = 0
    if stocks:
        for stock in stocks:
            stock["price"] = lookup(stock.get("symbol"))["price"]
            stock["value"] = stock.get("price") * stock.get("total_shares")
            curr_holdings += stock["value"]

    # Calculate user's total worth
    curr_worth = cash + curr_holdings

    # Show portfolio to user
    return render_template("index.html", worth=curr_worth, stocks=stocks, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Raise an exception if either field is blank
        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("invalid input", 400)

        # Check if symbol is valid
        stock = lookup(request.form.get("symbol"))

        if not stock:
            return apology("invalid symbol", 400)

        # Check if shares is a positive integer
        try:
            shares = int(request.form.get("shares"))
            if shares < 0:
                return apology("need a positive number", 400)
        except ValueError:
            return apology("invalid number of shares", 400)

        # Total value of shares
        price = stock.get("price")
        symbol = stock.get("symbol")
        share_value = price * shares

        # How much cash does the user have?
        row = db.execute("SELECT cash FROM users WHERE id = :id",
                         id=session["user_id"])

        if not row:
            return apology("ran into an error. try again", 400)

        cash = row[0]["cash"]

        # If cash < share_value, return apology, else buy and update portfolio
        if cash < share_value:
            return apology("can't afford", 400)
        else:
            # Add transaction to portfolio
            row = db.execute("INSERT INTO portfolio (user_id, symbol, name, shares, price, total) VALUES (:id, :symbol, :name, :shares, :price, :total)",
                             id=session["user_id"], symbol=symbol, name=symbol, shares=shares, price=price, total=share_value)

            # Check if insertion was successful
            if not row:
                return apology("could not buy", 400)

            # Update cash balance
            db.execute("UPDATE users SET cash = cash - :purchase WHERE id = :id", purchase=share_value, id=session["user_id"])

            # Show portfolio
            flash(Markup("Bought!"))
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Get user's stocks
    stocks = db.execute("SELECT symbol, shares, price, date FROM portfolio WHERE user_id=:id ORDER BY date", id=session["user_id"])

    if not stocks:
        return apology("ran into an error. try again", 400)

    # Show portfolio to user
    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via GET (as by clicking a link or via redirect)
    if request.method == "GET":

        return render_template("quote.html")

    # User reached route via POST (as by submitting a form via POST)
    else:

        # Get stock
        stock = lookup(request.form.get("symbol"))

        # Check if symbol is valid
        if not stock:
            return apology("invalid symbol", 400)

        # Get stock symbol and price for display
        stock_symbol = stock["symbol"]
        stock_price = stock["price"]

        # Display stock price
        return render_template("quoted.html", stock_symbol=stock_symbol, stock_price=usd(stock_price))


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Ensure confirmation was submitted and matches password
        elif not request.form.get("confirmation") or (request.form.get("confirmation") != request.form.get("password")):
            return apology("passwords must match")

        # Check if password is atleast 6 chars long and contains a number
        elif len(request.form.get("password")) < 6 or not bool(re.search(r'\d', request.form.get("password"))):
            return apology("password must be atleast 6 characters long and must contain a number")

        # Create password hash
        hashval = generate_password_hash(request.form.get("password"))

        # Insert user into database
        result = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hashval)",
                            username=request.form.get("username"), hashval=hashval)

        # Check for duplicates
        if not result:
            return apology("username already exists", 400)

        # Log the user in if registration is successful
        session["user_id"] = result

        # Flash success
        flash(Markup("Registered!"))

        # Show portfolio
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Raise an exception if either field is blank
        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("invalid input", 400)

        # Check if shares is a positive integer
        try:
            shares_to_sell = int(request.form.get("shares"))
            if shares_to_sell < 0:
                return apology("need a positive number", 400)
        except ValueError:
            return apology("invalid number of shares", 400)

        # Get current value of stock
        stock = lookup(request.form.get("symbol"))

        # Total value of shares
        price = stock.get("price")
        symbol = stock.get("symbol")
        share_value = price * shares_to_sell

        # Get user's portfolio
        row = db.execute("SELECT symbol, SUM(shares) AS total_shares FROM portfolio WHERE user_id = :id AND symbol = :symbol GROUP BY symbol",
                         id=session["user_id"], symbol=symbol)

        if not row:
            return apology("ran into an error. try again", 400)

        # How many shares of this stock does the user have?
        num_shares = row[0]["total_shares"]

        # If num_shares < shares_to_sell, return apology, else buy and update portfolio
        if num_shares < shares_to_sell:
            return apology("don't have that many shares to sell", 400)
        else:
            # Add transaction to portfolio as a negative transaction
            row = db.execute("INSERT INTO portfolio (user_id, symbol, name, shares, price, total) VALUES (:id, :symbol, :name, :shares, :price, :total)",
                             id=session["user_id"], symbol=symbol, name=symbol, shares=-shares_to_sell, price=price, total=share_value)

            # Check if insertion was successful
            if not row:
                return apology("could not sell", 400)

            # Update cash balance
            db.execute("UPDATE users SET cash = cash + :sold WHERE id = :id", sold=share_value, id=session["user_id"])

            # Show portfolio
            flash(Markup("Sold!"))
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        # Get user's portfolio for selling options
        options = db.execute("SELECT symbol, SUM(shares) AS total_shares FROM portfolio WHERE user_id = :id GROUP BY symbol HAVING total_shares > 0",
                             id=session["user_id"])

        if not options:
            return apology("ran into an error. try again", 400)

        return render_template("sell.html", options=options)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
