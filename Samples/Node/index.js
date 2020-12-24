const enpix = require('enpix')

var im = Array()

for (var i = 0; i < 341; i++) {
    im[i] = Array()
    for (var j = 0; j < 763; j++) {
        im[i][j] = Array()
        for (var k = 0; k < 3; k++) {
            im[i][j][k] = getRandomInt(256)
        }
    }
}

var key = "firstname.lastname@email.com-nameofuser-mobilenumber"
var duration = 1000000

var encrypt = enpix.encrypt(im, key, duration)
var decrypt = enpix.decrypt(encrypt, key, duration)

console.log(decrypt==im)

function getRandomInt(max) {
    return Math.floor(Math.random() * Math.floor(max));
}