import json

from flask import Blueprint, request

api = Blueprint('api', __name__, url_prefix='/api')


@api.route('/target', methods=["POST"])
def set_target():
    data = request.get_json()
    print(data.get("target"))

    return json.dumps(True)


@api.route('/result', methods=["POST"])
def set_result():
    data = request.get_json()
    print(data.get("result"))

    return json.dumps(True)
