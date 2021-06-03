from flask import Flask, render_template, request
import json

app = Flask(__name__)


@app.route('/')
def start():
    return render_template('index.html')

@app.route('/target', methods=["POST"])
def setTarget():
    data = request.get_json()
    print(data.get("target"))

    return json.dumps(True)

@app.route('/result', methods=["POST"])
def setResult():
    data = request.get_json()
    print(data.get("result"))

    return json.dumps(True)
