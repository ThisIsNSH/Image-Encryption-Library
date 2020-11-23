const enpix = require('enpix-node')

var im = Array()

for (var i = 0; i < 16; i++) {
    im[i] = Array()
    for (var j = 0; j < 32; j++) {
        im[i][j] = Array()
        for (var k = 0; k < 3; k++) {
            im[i][j][k] = getRandomInt(256)
        }
    }
}

var encrypt = enpix.encrypt(im, "firstname.lastname@email.com-nameofuser-mobilenumber", 100000)
var decrypt = enpix.decrypt(encrypt, "firstname.lastname@email.com-nameofuser-mobilenumber", 100000)

console.log(decrypt==im)

function getRandomInt(max) {
    return Math.floor(Math.random() * Math.floor(max));
}