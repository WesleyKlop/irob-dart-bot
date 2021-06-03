const dialog = document.getElementById('resultDialog');
const button = document.querySelector('#saveResults');
const container = document.querySelector('#container');

(async () => {
    container.innerHTML = await fetch('/static/js/dartbord.svg').then((r) => r.text());

    [].forEach.call(container.children[0].children[1].children, function(el) {
        el.addEventListener('click', function(childEl) {
                if(childEl.target.dataset.value) {
                    postData('/target', {target: childEl.target.dataset.value})
                        .then(data => {
                            dialog.showModal()
                            button.addEventListener('click', submitDialog);
                        });
                }
        });
    });
})()

// Example POST method implementation:
async function postData(url = '', data = {}) {
  // Default options are marked with *
  const response = await fetch(url, {
    method: 'POST', // *GET, POST, PUT, DELETE, etc.
    mode: 'cors', // no-cors, *cors, same-origin
    cache: 'no-cache', // *default, no-cache, reload, force-cache, only-if-cached
    credentials: 'same-origin', // include, *same-origin, omit
    headers: {
      'Content-Type': 'application/json'
      // 'Content-Type': 'application/x-www-form-urlencoded',
    },
    redirect: 'follow', // manual, *follow, error
    referrerPolicy: 'no-referrer', // no-referrer, *no-referrer-when-downgrade, origin, origin-when-cross-origin, same-origin, strict-origin, strict-origin-when-cross-origin, unsafe-url
    body: JSON.stringify(data) // body data type must match "Content-Type" header
  });
  return response.json(); // parses JSON response into native JavaScript objects
}

let submitDialog = () => {
    let checked = [];

    [].forEach.call(dialog.children, function(el) {
        if(el.nodeName == "INPUT"){
            if(el.checked){
                checked.push(el.value);
                el.checked = false;
            }
        }
    });

    postData('/result', {result: checked});

    dialog.close();

}