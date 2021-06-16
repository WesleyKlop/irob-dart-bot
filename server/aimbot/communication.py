from enum import Enum

from smbus2 import SMBus

addr = 0x8  # bus address
bus = SMBus(1)  # indicates /dev/ic2-1


class Directions(Enum):
    LEFT = 'l'
    RIGHT = 'r'
    UP = 'u'
    DOWN = 'd'


def send_command(payload: str) -> None:
    bus.write_i2c_block_data(addr, ord('c'), [ord(c) for c in payload])


def move_robot(direction: Directions, degrees: int) -> None:
    send_command(str(degrees) + 'm' + direction.value)
