const NO_CONTENT = 204

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
