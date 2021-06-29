import {
    calibrateRobot,
    executeCommand,
    setMagnetState,
    submitResults,
} from './communication.mjs'

import { calculateAngle } from './calibration.mjs'
import { ShotResult } from './utils.mjs'

const resultDialog = document.querySelector('#result-dialog')
const resultDialogCheckboxes = Array.from(resultDialog.querySelectorAll('input[type="checkbox"]'))
const calibrationDialog = document.querySelector('#calibration-dialog')
const shootStateButton = document.querySelector('#shoot-state-button')
const resultForm = document.querySelector('#result-form')
const commandForm = document.querySelector('#command-form')
const calibrationForm = document.querySelector('#calibration-form')

let isCalibrating = true

if (localStorage.getItem('x')) {
    calibrationForm.x.value = localStorage.getItem('x')
}
if (localStorage.getItem('y')) {
    calibrationForm.y.value = localStorage.getItem('y')
}

calibrationDialog.showModal()

calibrationForm.addEventListener('submit', async (evt) => {
    evt.preventDefault()
    await setMagnetState(true)

    const x = parseFloat(calibrationForm.x.value)
    const y = parseFloat(calibrationForm.y.value)

    localStorage.setItem('x', x)
    localStorage.setItem('y', y)

    const angles = calculateAngle(y, x)

    await calibrateRobot(angles)
    calibrationDialog.close()
    await setMagnetState(false)
    resultDialog.showModal()
})

commandForm.addEventListener('submit', async (evt) => {
    evt.preventDefault()

    const command = commandForm.command.value
    commandForm.command.value = ''

    await executeCommand(command)
})

shootStateButton.addEventListener('click', async () => {
    const currentStateActive = 'active' in shootStateButton.dataset

    await setMagnetState(!currentStateActive)
    if (currentStateActive) {
        delete shootStateButton.dataset.active
        shootStateButton.innerText = 'Activeer magneet'

        resultDialog.showModal()
    } else {
        shootStateButton.dataset.active = ''
        shootStateButton.innerText = 'Schiet!'
    }
})

resultForm.addEventListener('submit', async (evt) => {
    evt.preventDefault()

    const result = Array.from(resultForm.result, (el) => {
        const val = el.checked ? parseInt(el.value) : 0
        el.checked = false
        el.disabled = false

        return val
    }).reduce((total, curr) => total | curr, 0)

    if (result === ShotResult.PERFECT) {
        isCalibrating = false
    }

    await submitResults(result)

    resultDialog.close()
    if (isCalibrating === true) {
        calibrationDialog.showModal()
    }
})

const ignoreList = {
    0: ['1', '2', '4', '8'],
    1: ['0', '2'],
    2: ['0', '1'],
    4: ['0', '8'],
    8: ['0', '4'],
}

resultDialogCheckboxes.forEach((el) => {
    el.addEventListener('change', () => {
        // If we select the perfect one we want to disable all others, else we disable the perfect button
        const handler = el.checked ? 'setAttribute' : 'removeAttribute'
        resultDialogCheckboxes
            .filter((cb) => ignoreList[el.value].includes(cb.value))
            .forEach((cb) => cb[handler]('disabled', ''))
    })
})
