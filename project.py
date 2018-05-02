from flask import Flask, render_template, redirect, url_for, request
from flask_bootstrap import Bootstrap
from flask_wtf import FlaskForm 
from wtforms.validators import InputRequired, Email, Length
from flask_sqlalchemy  import SQLAlchemy
from werkzeug.security import generate_password_hash, check_password_hash
from flask_login import LoginManager, UserMixin, login_user, login_required, logout_user, current_user
from wtforms import StringField, PasswordField, BooleanField
import os
import sqlite3

app = Flask(__name__)
app.config['SECRET_KEY'] = 'Thisissupposedtobesecret!'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///database.db'

bootstrap = Bootstrap(app)
db = SQLAlchemy(app)
login_manager = LoginManager()
login_manager.init_app(app)
login_manager.login_view = 'login'

class User(UserMixin, db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(15), unique=True)
    email = db.Column(db.String(50), unique=True)
    password = db.Column(db.String(80))

class FileContents(db.Model):
    id = db.Column(db.Integer,primary_key=True)
    name = db.Column(db.String(300))
    data = db.Column(db.LargeBinary)
    user_name = db.Column(db.String(15))

@login_manager.user_loader
def load_user(user_id):
    return User.query.get(int(user_id))

class LoginForm(FlaskForm):
    username = StringField('username', validators=[InputRequired(), Length(min=4, max=15)])
    password = PasswordField('password', validators=[InputRequired(), Length(min=8, max=80)])
    remember = BooleanField('remember me')

class RegisterForm(FlaskForm):
    email = StringField('email', validators=[InputRequired(), Email(message='Invalid email'), Length(max=50)])
    username = StringField('username', validators=[InputRequired(), Length(min=4, max=15)])
    password = PasswordField('password', validators=[InputRequired(), Length(min=8, max=80)])


@app.route('/')
def index():
    return render_template('index.html')

# tt=[""]

@app.route('/login', methods=['GET', 'POST'])
def login():
    form = LoginForm()

    if form.validate_on_submit():
        user = User.query.filter_by(username=form.username.data).first()
        if user:
            if check_password_hash(user.password, form.password.data):
                login_user(user, remember=form.remember.data)
                # tt = form.username.data
                # print(tt)
                return redirect(url_for('dashboard'))

        return render_template('lg2.html')

    return render_template('login.html', form=form)

@app.route('/signup', methods=['GET', 'POST'])
def signup():
    form = RegisterForm()

    if form.validate_on_submit():
        hashed_password = generate_password_hash(form.password.data, method='sha256')
        new_user = User(username=form.username.data, email=form.email.data, password=hashed_password)
        db.session.add(new_user)
        db.session.commit()

        return '<h1>New user has been created!</h1>'

    return render_template('signup.html', form=form)


@app.route('/dashboard')
@login_required
def dashboard():
	global tt
	tt = current_user.username
	return render_template('dashboard.html', name=current_user.username)

@app.route('/download')
def download():
    info = sqlite3.connect('database.db')
    cursor = info.cursor()
    cursor.execute("SELECT * FROM file_contents WHERE user_name = '%s'" % tt)
    # for i in cursor.fetchall() :
        # print(i)
    return render_template('download.html',x=cursor.fetchall())

@app.route('/dl/<int:id>')
def dl(id):
    info = sqlite3.connect('database.db')
    cursor = info.cursor()
    cursor.execute("SELECT * FROM file_contents WHERE id = %d" % id)
    file__name = str(cursor.fetchone()[1])
    # cursor.execute("SELECT CONVERT('data' USING utf8) FROM file_contents WHERE id = %d" % id)
    cursor.execute("SELECT CAST(data AS CHAR utf8) FROM file_contents WHERE id = %d" % id)
    # print(cursor.fetchone()[2])
    # return cursor.fetchone()[1]
    file__data = cursor.fetchone()[0]
    
    f = open(file__name,"w+")
    f.write(file__data)
    f.close()
    return "Successful Download"

@app.route('/upload',methods=['POST','GET'])
def uploadfile():
    file = request.files['inputFile']
    # prin  t(tt)
    newFile = FileContents(name=file.filename, data=file.read(),user_name=tt)
    db.session.add(newFile)
    db.session.commit()
    return "good"

@app.route('/uploadfile')
def upload():
    return render_template('upload.html')

@app.route('/logout')
@login_required
def logout():
    logout_user()
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.debug=True
    # db.init_app(app)
    # db.drop_all()
    # db.create_all()
    app.run()