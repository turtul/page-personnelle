var texteAcopie = document.getElementById("texte").getAttribute("href")
copierTexte = (e) => {
    e.preventDefault()
    if (texteAcopie.length) {
        navigator.clipboard.writeText(texteAcopie).then(() => {
            alert("Identifiant copié !")
        })
    } else {
        alert("Veillez saisir le texte à copier")
    }
}