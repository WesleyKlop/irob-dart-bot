import {
    executeCommand,
    setMagnetState,
    submitResults,
    calibrateRobot
} from './communication.mjs'

import{
    calculateAngle
} from './calibration.mjs'

const dialog = document.querySelector('#result-dialog')
const calibrationDialog = document.querySelector('#calibration-dialog')
const resultForm = document.querySelector('#result-form')
const checkboxes = Array.from(dialog.querySelectorAll('input[type="checkbox"]'))
const shootStateButton = document.querySelector('#shoot-state-button')
const commandForm = document.querySelector('#command-form')
const calibrationForm = document.querySelector('#calibration-form')

calibrationDialog.showModal()

calibrationForm.addEventListener('submit', async (evt) => {
    evt.preventDefault()

    const x = parseFloat(calibrationForm.X.value)
    const y = parseFloat(calibrationForm.Y.value)

    const angles = calculateAngle(y, x)


    await calibrateRobot(angles)
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

        dialog.showModal()
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

    await submitResults(result)

    dialog.close()
})

const ignoreList = {
    0: ['1', '2', '4', '8'],
    1: ['0', '2'],
    2: ['0', '1'],
    4: ['0', '8'],
    8: ['0', '4'],
}

checkboxes.forEach((el) => {
    el.addEventListener('change', () => {
        // If we select the perfect one we want to disable all others, else we disable the perfect button
        const handler = el.checked ? 'setAttribute' : 'removeAttribute'
        checkboxes
            .filter((cb) => ignoreList[el.value].includes(cb.value))
            .forEach((cb) => cb[handler]('disabled', ''))
    })
})
