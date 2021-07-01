from aimbot.aimbot import Aimbot
from aimbot.communication import FakeCommunication
from aimbot.serialcommunication import SerialCommunication

aimbot_inst = None
comms_inst = None


def get_aimbot() -> Aimbot:
    global aimbot_inst
    if aimbot_inst is None:
        aimbot_inst = Aimbot(3600)

    return aimbot_inst


def get_comms():
    global comms_inst
    if comms_inst is None:
        try:
            comms_inst = SerialCommunication()
        except FileNotFoundError:
            print("Fake communication registered")
            comms_inst = FakeCommunication()

    return comms_inst
