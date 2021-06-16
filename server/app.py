from flask import Flask, render_template, request, abort
import json
import sqlite3

app = Flask(__name__, static_folder='static', template_folder='templates')

def get_db_connection():
    conn = sqlite3.connect('database.db')
    return conn

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


@app.route('/calibrationValues/<tableHeight>', methods=["GET"])
def getCalibration(tableHeight):
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute('SELECT * FROM calibration LEFT JOIN calibration_steps ON calibration.calibration_id = calibration_steps.calibration_id WHERE calibration.table_height = ? ORDER BY calibration.created_on',
                          (tableHeight,))

    result = cur.fetchall()
    conn.close()
    if result is None:
        abort(404)

    return json.dumps(result)

