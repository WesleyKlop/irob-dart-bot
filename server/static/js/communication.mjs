import { postData } from './utils.mjs'

/**
 * Set the electromagnet state
 *
 * @param state
 * @returns {Promise<void>}
 */
export const setMagnetState = (state) => postData('/api/shoot', { state })

/**
 * Submit the results to the api
 *
 * @param {number} result
 * @returns {Promise<void>}
 */
export const submitResults = (result) =>
    postData('/api/results', {
        result,
    })

/**
 * Send a raw command to the robot.
 * @param {string} command
 * @returns {Promise<void>}
 */
export const executeCommand = (command) =>
    postData('/api/command', {
        command,
    })

/**
 * Calibrate robot to shoot in the bullseye
 *
 * @param {number} angle
 * @returns {Promise<void>}
 */
export const calibrateRobot = (angle) =>
    postData('/api/calibrate', { angle })
