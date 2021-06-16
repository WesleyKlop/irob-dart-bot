from flask import Blueprint, render_template

web = Blueprint('web', __name__, template_folder="../../templates")


@web.route('/')
def start():
    return render_template('index.html')
