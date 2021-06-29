import json
from enum import Enum

import serial

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
    command_prefix: str

    def __init__(self: object, comport: str = "/dev/serial0", baud: int = 115200):
        self.command_prefix = 'c'
        self.serial_obj = serial.Serial(comport, baud, timeout=2, bytesize=8, stopbits=serial.STOPBITS_ONE)

    def read_data(self):
        if self.serial_obj.is_open is False:
            return False

        while True:
            # Wait until there is data waiting in the serial buffer
            if self.serial_obj.in_waiting > 0:
                # Read data out of the buffer until a carraige return / new line is found
                return self.serial_obj.readline().decode('utf-8').rstrip()

    def send_data(self, data: str):
        if self.serial_obj.is_open is False:
            return False

        self.serial_obj.write((self.command_prefix + data).encode('utf-8'))

    def move_robot(self, movement: Movement) -> None:
        for (direction, degrees) in movement.instructions():
            self.send_data(Commands.MOVE + str(degrees) + direction)

    def shoot_dart(self, state: bool) -> None:
        self.send_data(Commands.SHOOT + ('1' if state else '0'))

    # Gets the current values of the robot.
    def current_values(self):
        self.send_data(Commands.STATUS)

        return json.loads(self.read_data())

    def close_port(self):
        self.serial_obj.close()
