### Finance ###  
_This is a dummy share trading website where users can register, login, quote, buy, sell, browse 
transaction history, and logout. This website is implemented using Python/Flask on the back-end with a SQLite database
and HTML/CSS/Jinja2 on the front-end. Follow these instructions to launch the website_:  
  
1. This website uses AlphaVantage to pull share prices, so you will need to get an API key [here](https://www.alphavantage.co/support/#api-key).  
2. Once you have the key run `export API_KEY=value` in your terminal, where value is your API key.  
3. This program uses the cs50 python libarary. You can install this by running the following command:  
```
  $ pip install cs50   
```
4. Once cs50 library is installed, navigate to the folder where the application (`application.py`) lives and do:  
```
  $ flask run  
````  
5. Open the link on a web browser.  
