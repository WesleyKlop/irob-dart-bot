from flask import Flask, g

from aimbot.aimbot import Aimbot
from aimbot.communication import FakeCommunication, Communication


def create_app() -> Flask:
    app = Flask(__name__, static_folder="../../static")

    # Add our web and api blueprints
    from aimbot.web.api import api
    from aimbot.web.web import web
    app.register_blueprint(api)
    app.register_blueprint(web)

    return app
