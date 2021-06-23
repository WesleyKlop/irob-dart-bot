from http import HTTPStatus

from flask import Blueprint, request

from aimbot import get_comms, get_aimbot

api = Blueprint('api', __name__, url_prefix='/api')


@api.route('/shoot', methods=["POST"])
def shoot():
    print(repr(request.json["state"]))
    get_comms().shoot_dart(request.json["state"] is True)
    return '', HTTPStatus.NO_CONTENT


@api.route('/results', methods=["POST"])
def submit_results():
    aimbot = get_aimbot()
    movement = aimbot.compensate(request.json["result"])
    print(repr(movement))
    if movement is not None:
        get_comms().move_robot(movement)

    return '', HTTPStatus.NO_CONTENT


@api.route("/command", methods=["POST"])
def submit_command():
    command = request.json["command"]
    get_comms().send_command(command)
    return '', HTTPStatus.NO_CONTENT
