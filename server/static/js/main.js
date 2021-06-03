const dialog = document.querySelector('#resultDialog')
const button = document.querySelector('#saveResults')
const container = document.querySelector('#container')
const checkboxes = Array.from(dialog.querySelectorAll('input[type="checkbox"]'))

const postData = (url, data = {}) =>
    fetch(url, {
        method: 'POST',
        cache: 'no-cache',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify(data),
    }).then((r) => r.json())

;(async () => {
    container.innerHTML = await fetch('/static/svg/dartbord.svg').then((r) =>
        r.text(),
    )

    Array.from(container.children[0].children[1].children, (el) => {
        el.addEventListener('click', (childEl) => {
            if (childEl.target.dataset.value) {
                postData('/target', {
                    target: childEl.target.dataset.value,
                }).then((data) => {
                    dialog.showModal()
                    button.addEventListener('click', submitDialog)
                })
            }
        })
    })
})()

const submitDialog = () => {
    const checked = Array.from(dialog.children, (el) => {
        if (el.nodeName === 'INPUT' && el.checked === true) {
            el.checked = false
            return el.value
        }
    }).filter(Boolean)

    postData('/result', { result: checked }).then((r) => console.log(r))

    dialog.close()
}

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
