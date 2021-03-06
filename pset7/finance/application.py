import os
import sqlite3

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

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
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """TODO implement cash update after buying
       TODO check for sufficient funds when trying to buy
       TODO check if user input is sane"""
    if request.method =="POST":
        # Assign share data to variables
        try:
            quote_search = lookup(request.form.get("quote"))
            quote_name = quote_search.get("name")
            quote_symbol = quote_search.get("symbol")
            quote_share_price = float(quote_search.get("price"))
            quote_shares = int(request.form.get("buy_quantity"))
        except:
            return apology("Could not read from input")

        #Sanity check on shares for valid input
        if quote_shares <= 0:
            return apology("Invalid Share number")

        #Calculate total cost of shares
        quote_price = quote_share_price * quote_shares
        quote_total_list=db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])[0]

        #Check if user has sufficient funds
        if quote_total_list.get("cash") < quote_price:
            return apology("Insufficient Funds")
        quote_total= quote_total_list.get("cash") - quote_price
        #Write new shares into shares.db and update cash in users.db
        try:
            db.execute("INSERT INTO shares(symbol, name, shares, price, total, user_id) VALUES(:symbol, :name, :shares, :price, :total, :user_id)", symbol=quote_symbol, name=quote_name, \
                shares=quote_shares, price=quote_price, total=quote_total, user_id=session["user_id"])
            db.execute("UPDATE users SET cash =:cash WHERE id = :id", cash=quote_total, id=session["user_id"])
        except:
            return apology("Could not write to db")
        finally:
            return render_template("index.html")
    else:
        return render_template("buy.html")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return render_template("index.html")


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
    if request.method == "POST":
        quote_search = lookup(request.form.get("quote"))
        quote_name = quote_search.get("name")
        quote_symbol = quote_search.get("symbol")
        quote_value = quote_search.get("price")
        return render_template("quoted.html", quote_name=quote_name, quote_symbol=quote_symbol, quote_price=quote_value)
    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Sanity check for empty fields
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        if not request.form.get("username"):
            return apology("must provide username", 403)
        elif not request.form.get("password"):
            return apology("must provide password", 403)
        elif request.form.get("password") != request.form.get("password_check"):
            return apology ("passwords do not match", 403)

        # Sanity check for existing user
        elif len(rows) != 0:
            return apology ("User already exists", 403)

        # Add user, pass to db
        else:
            rows = db.execute("INSERT INTO users (username, hash) \
                            VALUES(:username, :password)", \
                            username=request.form.get("username"), \
                            password=generate_password_hash(request.form.get("password")))
            session["user_id"] = rows
            return redirect("/")

    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
