import serial
from enum import Enum
import json

from aimbot.aimbot import Movement


class Directions(Enum):
    LEFT = 'l'
    RIGHT = 'r'
    UP = 'u'
    DOWN = 'd'


class Commands(str, Enum):
    SHOOT = 's'
    MOVE = 'm'
    STATUS = 'c'


class SerialCommunication:
    serial_obj: serial
    command_prefix: int

    def __init__(self: object, comport: str = "COM2", baud: int = 115200):
        self.command_prefix = ord("c")

        self.serial_obj = serial.Serial()
        self.serial_obj.port = comport
        self.serial_obj.baudrate = baud
        self.serial_obj.bytesize = 8
        self.serial_obj.timeout = 2
        self.serial_obj.stopbits = serial.STOPBITS_ONE
        self.serial_obj.open()

    def read_data(self):
        if self.serial_obj.is_open is False:
            return False

        await_data = True
        serial_string_decoded: str = ""

        while await_data:
            # Wait until there is data waiting in the serial buffer
            if self.serial_obj.in_waiting > 0:
                # Read data out of the buffer until a carraige return / new line is found
                serial_string = self.serial_obj.readline()

                serial_string_decoded = serial_string.decode('Ascii')

                await_data = False

        return serial_string_decoded

    def send_data(self, data: str):
        if self.serial_obj.is_open is False:
            return False

        self.serial_obj.write(self.command_prefix+data)

    def move_robot(self, movement: Movement) -> None:
        for (direction, degrees) in movement.instructions():
            self.send_data(Commands.MOVE + str(degrees) + direction)

    def shoot_dart(self, state: bool) -> None:
        self.send_data(Commands.SHOOT + ('1' if state else '0'))

    #Gets the current values of the robot.
    def current_values(self):
        self.send_data(Commands.STATUS)

        return json.loads(self.read_data())

    def close_port(self):
        self.serial_obj.close()
