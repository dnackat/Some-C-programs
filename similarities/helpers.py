# Functions to compare two files based different attributes

from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    # Split a and b to get individual lines. Store in sets to avoid duplicates
    a = set(a.split("\n"))
    b = set(b.split("\n"))

    # Create a list of lines that appear both in a and b to sim_lines
    sim_lines = list(a & b)

    return sim_lines


def sentences(a, b):
    """Return sentences in both a and b"""

    # Split a and b to get individual sentences. Store in sets to avoid duplicates
    a = set(sent_tokenize(a, language='english'))
    b = set(sent_tokenize(b, language='english'))

    # Create a list of sentences that appear both in a and b to sim_lines
    sim_sentences = list(a & b)

    return sim_sentences


# Define a helper function to return substrings of length n
def substr(a, n):
    """Return substrings of length n from string a"""

    # List to store substrings
    subs = []

    # Loop through a and create substrings of length n
    for i in range(len(a) - (n - 1)):
        subs.append(a[i:i + n])

    return subs


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # Get substrings of length n from a and b and store them as sets
    a = set(substr(a, n))
    b = set(substr(b, n))

    # Create a list of substrings that appear in both a and b
    sub_strings = list(a & b)

    return sub_strings
