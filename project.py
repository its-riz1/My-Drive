from flask import Flask,render_template
from flask_bootstrap import Bootstrap
from flask_wtf import FlaskForm
from wtforms import StringField,PasswordField,BooleanField
from wtforms.validators import InputRequired,Email,Length
from flask_sqlalchemy import SQLAlchemy

app=Flask(__name__)
app.config['SECRET_KEY']='Thisissupposedtobesecret'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:////~/Project_IT/database.db'
Bootstrap(app)
db = SQLAlchemy(app)

class User(db.Model):
	id = db.Column(db.Integer,primary_Key=True)
	username = db.Column(db.String(10),unique=True)
	email = db.Column(db.String(70),unique=True)
	password = db.Column(db.String(32))

class LoginForm(FlaskForm):
	username = StringField('username',validators=[InputRequired(),Length(min=4,max=10)])
	password = PasswordField('password',validators=[InputRequired(),Length(min=8,max=32)])
	remember = BooleanField('remember me')

class RegisterForm(FlaskForm):
	email = StringField('email',validators=[InputRequired(),Email(message='Invalid Email'),Length(max=70)])
	username = StringField('username',validators=[InputRequired(),Length(min=4,max=10)])
	password = PasswordField('password',validators=[InputRequired(),Length(min=8,max=32)])

@app.route('/')
def index():
	return render_template('index.html')

@app.route('/login',methods=['GET','POST'])
def login():
	form=LoginForm()
	if form.validate_on_submit():
		return '<h1> Hello ' + form.username.data + '</h1>'
	return render_template('login.html',form=form)

@app.route('/signup',methods=['GET','POST'])
def signup():
	form = RegisterForm()
	return render_template('signup.html',form=form)

@app.route('/dashboard')
def dashboard():
	return render_template('dashboard.html')

if __name__ == '__main__':
	app.debug=True
	app.run()