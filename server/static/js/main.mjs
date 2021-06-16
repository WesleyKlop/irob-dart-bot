import { executeCommand, setMagnetState, submitResults } from './communication.mjs'

const dialog = document.querySelector('#result-dialog')
const resultForm = document.querySelector('#result-form')
const container = document.querySelector('#container')
const checkboxes = Array.from(dialog.querySelectorAll('input[type="checkbox"]'))
const shootStateButton = document.querySelector('#shoot-state-button')
const commandForm = document.querySelector('#command-form')

container.innerHTML = await fetch('/static/svg/dartbord.svg').then((r) =>
    r.text(),
)

commandForm.addEventListener('submit', evt => {
    evt.preventDefault()

    const command = commandForm.command.value

    executeCommand(command)
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

resultForm.addEventListener('submit', async (e) => {
    e.preventDefault()

    const result = Array.from(resultForm.result, (el) => {
        const val = el.checked ? parseInt(el.value) : 0
        el.checked = false

        return val
    }).reduce((total, curr) => total | curr, 0)

    await submitResults(result)

    dialog.close()
})

checkboxes.forEach((el) => {
    el.addEventListener('change', () => {
        // If we select the perfect one we want to disable all others, else we disable the perfect button
        const filterFn =
            el.value === 'perfect'
                ? (cb) => cb !== el
                : (cb) => cb.id === 'perfect'
        checkboxes.filter(filterFn).forEach((cb) => {
            if (el.checked) {
                cb.setAttribute('disabled', '')
            } else {
                cb.removeAttribute('disabled')
            }
        })
    })
})
