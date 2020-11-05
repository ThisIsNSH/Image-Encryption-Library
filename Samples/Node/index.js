const enpix = require('enpix-node')

var im = Array()

for (var i = 0; i < 5; i++) {
    im[i] = Array()
}

for (var i = 0; i < 5; i++) {
    for (var j = 0; j < 4; j++) {
        im[i][j] = Array()
    }
}

for (var i = 0; i < 5; i++) {
    for (var j = 0; j < 4; j++) {
        for (var k = 0; k < 3; k++) {
            im[i][j][k] = getRandomInt(256)
        }
    }
}

console.log(im)
var encrypt = enpix.encrypt(im, "FirstnameLastnameEmailID@Something.com", 10, 100000)
console.log(encrypt)
console.log(enpix.decrypt(encrypt, "FirstnameLastnameEmailID@Something.com", 10, 100000))

function getRandomInt(max) {
    return Math.floor(Math.random() * Math.floor(max));
}