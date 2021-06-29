const BOARD_HEIGHT = 1.73 //Height in M
const BULLS_EYE_HEIGHT = 0.2 //Height in M
const DART_SPEED = 7 //Speed in m/s ( 36KM/h)
const G = 9.81 //Gravitational pull
const CONSTRUCTION_HEIGHT = 0.254 //Height of the bot

const MIN_POT = 0
const MAX_POT = 255

export const calculateAngle = (tableheight, x) => {
    const y_diff =
        BOARD_HEIGHT + BULLS_EYE_HEIGHT - (tableheight + CONSTRUCTION_HEIGHT)
    const ans_disc =
        Math.pow(DART_SPEED, 4) -
        G * (G * Math.pow(x, 2) + 2 * y_diff * Math.pow(DART_SPEED, 2))

    //Impossible. No solution found /rekt
    if (ans_disc < 0) {
        return -1
    }

    const ansPos = (Math.pow(DART_SPEED, 2) + Math.sqrt(ans_disc)) / (G * x)
    const ansNeg = (Math.pow(DART_SPEED, 2) - Math.sqrt(ans_disc)) / (G * x)

    const anglePos = Math.atan(ansPos)
    const angleNeg = Math.atan(ansNeg)

    return {
        pos: (anglePos * 180) / Math.PI,
        neg: (angleNeg * 180) / Math.PI,
        podValue: (MAX_POT - MIN_POT) / 2,
    }
}
