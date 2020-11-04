const enpix = require('enpix-node')

var im = Array()

for (var i = 0; i < 6; i++) {
    im[i] = Array()
}

for (var i = 0; i < 6; i++) {
    for (var j = 0; j < 5; j++) {
        im[i][j] = Array()
    }
}

for (var i = 0; i < 6; i++) {
    for (var j = 0; j < 5; j++) {
        for (var k = 0; k < 3; k++) {
            im[i][j][k] = getRandomInt(256)
        }
    }
}

var encrypt = enpix.encrypt(im, "FirstnameLastnameEmailID@Something.com", 1, 100000)
console.log(encrypt)
console.log(enpix.decrypt(encrypt, "FirstnameLastnameEmailID@Something.com", 1, 100000))

function getRandomInt(max) {
    return Math.floor(Math.random() * Math.floor(max));
}