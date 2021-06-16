from aimbot.aimbot import Aimbot, ShotResult, Direction


def dump(*a: any):
    print(repr(a))


def dd(a: any):
    dump(a)
    exit()


def main():
    a = Aimbot()
    print("The first shot hits to the bottom left of the bull. Result should that we should move up and right:")
    r = a.compensate(ShotResult.BELOW_LEFT)
    dump(r, a)
    assert r.direction is Direction.UP_RIGHT
    print("The second shot hits above the bull. Result should be that we just have to move down")
    r = a.compensate(ShotResult.ABOVE)
    dump(r, a)
    assert r.direction is Direction.DOWN
    print("The third shot hits the bull, result should be None")
    r = a.compensate(ShotResult.PERFECT)
    dump(r, a)
    assert r is None


if __name__ == '__main__':
    main()
