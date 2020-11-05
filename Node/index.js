exports.encrypt = function(image, key, grain, time) {

    var d = new Date()
    var n = d.getTime()

    // var base64 = CryptoJS.AES.encrypt(key, n/time);
    var base64 = Buffer.from(key).toString('base64')

    var len1 = base64.length
    var len2 = image[0].length

    if (len2 < len1) {
        base64 = base64.substring(0, len2)
    } else if (len2 > len1) {
        var s = base64
        for (var i = 0; i < len2 / len1; i++) {
            s += base64
        }
        base64 = s.substring(0, len2)
    }

    var sb = ""

    let set = new Set()
    let max = image[0].length / grain

    for (var i = 0; i < base64.length; i++) {
        sb += base64.charCodeAt(i)
    }

    let ch = [...sb]

    for (let i = 0; i < ch.length; i++) {
        var sb1 = ""
        for (let j = i; j < ch.length; j++) {
            sb1 += ch[j]
            let k = parseInt(sb1)
            if (k < max) {
                if (set.add(k)) break
            } else {
                while (k >= max || (k >= 0 && !set.add(k))) {
                    k--
                }
                break
            }
        }
        if (set.size == max) break
    }

    for (let i = 0; i < image[0].length / grain; i++) {
        set.add(i)
    }

    let col = 0
    var image1 = Array()

    for (var i = 0; i < 5; i++) {
        image1[i] = Array()
    }

    for (var i = 0; i < 5; i++) {
        for (var j = 0; j < 4; j++) {
            image1[i][j] = Array()
        }
    }

    set.forEach(function (k) {
        let num = k * grain
        for (let i = 0; i < grain; i++) {
            for (let j = 0; j < image.length; j++) {
                var px_red = image[j][num + i][0]
                var px_green = image[j][num + i][1]
                var px_blue = image[j][num + i][2]

                image1[j][col][0] = px_red
                image1[j][col][1] = px_green
                image1[j][col][2] = px_blue
            }
            col++
        }
    });

    len1 = base64.length
    len2 = image.length

    if (len2 < len1) {
        base64 = base64.substring(0, len2)
    } else if (len2 > len1) {
        var s = base64
        for (var i = 0; i < len2 / len1; i++) {
            s += base64
        }
        base64 = s.substring(0, len2)
    }

    sb = ""

    set = new Set()
    max = image.length / grain

    for (let i = 0; i < base64.toString().length; i++) {
        sb += base64.charCodeAt(i)
    }

    ch = [...sb.toString()]

    for (var i = 0; i < ch.length; i++) {
        let sb1 = ""
        for (let j = i; j < ch.length; j++) {
            sb1 += ch[j]
            let k = parseInt(sb1)
            if (k < max) {
                if (set.add(k)) break
            } else {
                while (k >= max || (k >= 0 && !set.add(k))) {
                    k--
                }
                break
            }
        }
        if (set.size == max) break
    }

    for (let i = 0; i < image.length / grain; i++) {
        set.add(i)
    }

    let row = 0
    set.forEach(function (k) {
        let num = k * grain
        for (let i = 0; i < grain; i++) {
            for (let j = 0; j < image[0].length; j++) {
                var px_red = image1[num + i][j][0]
                var px_green = image1[num + i][j][1]
                var px_blue = image1[num + i][j][2]

                image[row][j][0] = px_red
                image[row][j][1] = px_green
                image[row][j][2] = px_blue
            }
        row++
        }
    });

    return image
}

exports.decrypt = function(image, key, grain, time) {
    
    var d = new Date()
    var n = d.getTime()

    var base64 = Buffer.from(key).toString('base64')

    var len1 = base64.length
    var len2 = image.length

    if (len2 < len1) {
        base64 = base64.substring(0, len2)
    } else if (len2 > len1) {
        var s = base64
        for (var i = 0; i < len2 / len1; i++) {
            s += base64
        }
        base64 = s.substring(0, len2)
    }

    var sb = ""

    var set = new Set()
    var max = image.length / grain

    for (let i = 0; i < base64.toString().length; i++) {
        sb += base64.charCodeAt(i)
    }

    var ch = [...sb.toString()]

    for (var i = 0; i < ch.length; i++) {
        let sb1 = ""
        for (let j = i; j < ch.length; j++) {
            sb1 += ch[j]
            let k = parseInt(sb1)
            if (k < max) {
                if (set.add(k)) break
            } else {
                while (k >= max || (k >= 0 && !set.add(k))) {
                    k--
                }
                break
            }
        }
        if (set.size == max) break
    }

    for (let i = 0; i < image.length / grain; i++) {
        set.add(i)
    }

    let row = 0
    var image1 = Array()

    for (var i = 0; i < 5; i++) {
        image1[i] = Array()
    }

    for (var i = 0; i < 5; i++) {
        for (var j = 0; j < 4; j++) {
            image1[i][j] = Array()
        }
    }

    set.forEach(function (k) {
        let num = k * grain
        for (let i = 0; i < grain; i++) {
            for (let j = 0; j < image[0].length; j++) {
                var px_red = image[row][j][0]
                var px_green = image[row][j][1]
                var px_blue = image[row][j][2]

                image1[num + i][j][0] = px_red
                image1[num + i][j][1] = px_green
                image1[num + i][j][2] = px_blue
            }
            row++
        }
    });

    len1 = base64.length
    len2 = image[0].length

    if (len2 < len1) {
        base64 = base64.substring(0, len2)
    } else if (len2 > len1) {
        var s = base64
        for (var i = 0; i < len2 / len1; i++) {
            s += base64
        }
        base64 = s.substring(0, len2)
    }

    sb = ""

    set = new Set()
    max = image[0].length / grain

    for (var i = 0; i < base64.length; i++) {
        sb += base64.charCodeAt(i)
    }

    ch = [...sb]

    for (let i = 0; i < ch.length; i++) {
        var sb1 = ""
        for (let j = i; j < ch.length; j++) {
            sb1 += ch[j]
            let k = parseInt(sb1)
            if (k < max) {
                if (set.add(k)) break
            } else {
                while (k >= max || (k >= 0 && !set.add(k))) {
                    k--
                }
                break
            }
        }
        if (set.size == max) break
    }

    for (let i = 0; i < image[0].length / grain; i++) {
        set.add(i)
    }

    let col = 0

    set.forEach(function (k) {
        let num = k * grain
        for (let i = 0; i < grain; i++) {
            for (let j = 0; j < image.length; j++) {
                var px_red = image1[j][col][0]
                var px_green = image1[j][col][1]
                var px_blue = image1[j][col][2]

                image[j][num + i][0] = px_red
                image[j][num + i][1] = px_green
                image[j][num + i][2] = px_blue
            }
            col++
        }
    });

    return image
}
