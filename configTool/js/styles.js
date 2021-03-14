// file-input
const formInputs = document.getElementsByClassName("file");
const length = formInputs.length;
for (let i = 0; i < length; i++) {
    formInputs[i].onchange = function () {
        const file = this.files[0].name;
        const label = this.nextElementSibling;
        if (!label.classList.contains("changed")) {
            const span = document.createElement("span");
            span.className = "filename";
            this.parentNode.appendChild(span);
            label.classList.add("changed");
        }
        label.nextElementSibling.innerHTML = file;
    };
}

// hexadecimal -> decimal
function convert() {
    let val = document.querySelectorAll("input[name='mac']");
    val.forEach(function(elem){
        let hex = elem.value;
        let decimal = parseInt(hex,16);
        elem.value = decimal;
    });
}

window.onload = function () {
    let elmbtn = document.getElementById('btn');
    elmbtn.onclick = function () {
      convert();
    };
}