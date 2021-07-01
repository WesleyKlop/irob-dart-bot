const NO_CONTENT = 204
const BOARD_HEIGHT = 1.73 //Height in M
const BULLS_EYE_HEIGHT = 0.2 //Height in M
const DART_SPEED = 7 //Speed in m/s ( 36KM/h)
const G = 9.81 //Gravitational pull
const CONSTRUCTION_HEIGHT = 0.254 //Height of the bot

export const calculateAngle = (tableheight, x) => {
    const y_diff =
        BOARD_HEIGHT + BULLS_EYE_HEIGHT - (tableheight + CONSTRUCTION_HEIGHT)
    const ans_disc =
        Math.pow(DART_SPEED, 4) -
        G * (G * Math.pow(x, 2) + 2 * y_diff * Math.pow(DART_SPEED, 2))

    //Impossible. No solution found /rekt
    if (ans_disc < 0) {
        return null
    }

    const ansPos = (Math.pow(DART_SPEED, 2) + Math.sqrt(ans_disc)) / (G * x)
    const ansNeg = (Math.pow(DART_SPEED, 2) - Math.sqrt(ans_disc)) / (G * x)

    return Math.min(
        (Math.atan(ansPos) * 180) / Math.PI,
        (Math.atan(ansNeg) * 180) / Math.PI,
    )
}


/**
 * Call the api
 * @param {string} url
 * @param {Record<string, any>} data
 * @returns {Promise<void|Object>}
 */
export const postData = (url, data = {}) =>
    fetch(url, {
        method: 'POST',
        cache: 'no-cache',
        headers: {
            'Content-Type': 'application/json',
            Accept: 'application/json',
        },
        body: JSON.stringify(data),
    })
        .then((r) => {
            if (r.status !== NO_CONTENT) return r.json()
        })
        .catch(console.error)

/**
 * Sleep for the given ms
 * @param {number} ms
 * @returns {Promise<void>}
 */
export const sleep = (ms = 500) => new Promise((res) => setTimeout(res, ms))

export const ShotResult = Object.freeze({
    PERFECT: 0,
    ABOVE: 1,
    BELOW: 2,
    LEFT: 4,
    RIGHT: 8,
})
