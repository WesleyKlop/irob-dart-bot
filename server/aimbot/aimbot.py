from enum import IntFlag
from typing import Optional


class Direction(IntFlag):
    UP = 1
    DOWN = 2
    LEFT = 4
    UP_LEFT = UP | LEFT
    DOWN_LEFT = DOWN | LEFT
    RIGHT = 8
    UP_RIGHT = UP | RIGHT
    DOWN_RIGHT = DOWN | RIGHT
    ALL = DOWN_LEFT | UP_RIGHT


class ShotResult(IntFlag):
    PERFECT = 0
    ABOVE = 1
    BELOW = 2
    LEFT = 4
    ABOVE_LEFT = ABOVE | LEFT
    BELOW_LEFT = BELOW | LEFT
    RIGHT = 8
    ABOVE_RIGHT = ABOVE | RIGHT
    BELOW_RIGHT = BELOW | RIGHT


class Movement:
    def __init__(self, direction: Direction, horizontal: int = 0, vertical: int = 0):
        self.direction = direction
        self.horizontal = horizontal
        self.vertical = vertical

    def __repr__(self):
        return repr(
            '<Movement direction: ' + str(self.direction) +
            ' | horizontal: ' + str(self.horizontal) +
            ' | vertical: ' + str(self.vertical) + '>'
        )

    def instructions(self):
        chars = ()
        if Direction.UP in self.direction:
            chars += ('u', self.vertical)
        if Direction.DOWN in self.direction:
            chars += ('d', self.vertical)
        if Direction.LEFT in self.direction:
            chars += ('l', self.horizontal)
        if Direction.RIGHT in self.direction:
            chars += ('r', self.horizontal)
        return chars


class Aimbot:
    prev_state: Optional[ShotResult]
    ver_step_size: int
    hor_step_size: int
    direction: Direction

    def __init__(self, initial_step_size: int = 25):
        self.hor_step_size = initial_step_size
        self.ver_step_size = initial_step_size
        self.direction = Direction(Direction.RIGHT | Direction.DOWN)
        self.prev_state = None

    def compensate(self, result: ShotResult) -> Optional[Movement]:
        if result not in ShotResult.__members__.values() or result is ShotResult.PERFECT:
            return None

        self.update_direction(result)
        movement = Movement(self.direction, self.hor_step_size, self.ver_step_size)

        if self.prev_state is not None:
            self.update_step_size(result)

        self.prev_state = result
        return movement

    def __repr__(self):
        return repr(
            '<Aimbot direction: ' + str(self.direction) +
            ' | prev_state: ' + str(self.prev_state) +
            ' | hor_step_size: ' + str(self.hor_step_size) +
            ' | ver_step_size: ' + str(self.ver_step_size) + '>'
        )

    def update_step_size(self, result: ShotResult):
        if ShotResult.LEFT in result and ShotResult.RIGHT in self.prev_state:
            self.hor_step_size /= 2
        elif ShotResult.RIGHT in result and ShotResult.LEFT in self.prev_state:
            self.hor_step_size /= 2
        if ShotResult.ABOVE in result and ShotResult.BELOW in self.prev_state:
            self.ver_step_size /= 2
        elif ShotResult.BELOW in result and ShotResult.ABOVE in self.prev_state:
            self.ver_step_size /= 2

    def update_direction(self, result: ShotResult):
        self.direction = Direction(Direction.ALL ^ result)
        if Direction.UP in self.direction and Direction.DOWN in self.direction:
            self.direction ^= Direction.DOWN | Direction.UP
        if Direction.LEFT in self.direction and Direction.RIGHT in self.direction:
            self.direction ^= Direction.LEFT | Direction.RIGHT
