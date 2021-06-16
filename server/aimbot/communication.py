from enum import Enum

from smbus2 import SMBus

from aimbot.aimbot import Movement


class Directions(Enum):
    LEFT = 'l'
    RIGHT = 'r'
    UP = 'u'
    DOWN = 'd'


class Commands(str, Enum):
    SHOOT = 's'
    MOVE = 'm'


class Communication:
    address: int
    command_prefix: int
    bus: SMBus

    def __init__(self: object, address: int = 0x8, command_prefix: str = 'c', bus: int = 1) -> None:
        self.address = address
        self.command_prefix = ord(command_prefix)
        self.bus = SMBus(bus)

    def send_command(self, payload: str) -> None:
        self.bus.write_i2c_block_data(self.address, self.command_prefix, [ord(c) for c in payload])

    def move_robot(self, movement: Movement) -> None:
        for (direction, degrees) in movement.instructions():
            self.send_command(str(degrees) + Commands.MOVE + direction)

    def shoot_dart(self, state: bool) -> None:
        self.send_command(Commands.SHOOT + '1' if state else '0')


class FakeCommunication:
    def send_command(self, payload: str) -> None:
        print("payload: c" + repr(payload))

    def move_robot(self, movement: Movement) -> None:
        self.send_command(repr(movement))

    def shoot_dart(self, state: bool) -> None:
        self.send_command(repr(state))
