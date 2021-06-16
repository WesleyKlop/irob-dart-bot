from flask import Flask


def create_app() -> Flask:
    app = Flask(__name__, static_folder="../../static")
    from aimbot.web.api import api
    from aimbot.web.web import web
    app.register_blueprint(api)
    app.register_blueprint(web)

    return app
