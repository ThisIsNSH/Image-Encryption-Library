var crypto = require('crypto');

exports.encrypt = function (image, key, duration) {

    // Create temp array
    var image1 = Array()
    for (var i = 0; i < image.length; i++) {
        image1[i] = Array()
        for (var j = 0; j < image[0].length; j++) {
            image1[i][j] = Array()
        }
    }

    duration = Math.round(Date.now() / duration)

    // key generation
    var base64 = crypto.createHash('sha256').update(key + duration).digest('hex').toUpperCase()
    var len1 = ((image[0].length / 16) * 16)
    var column_key = [...Array(image[0].length).keys()]

    var counter = 0
    for (var i = 0; i < len1; i += 16) {
        var temp_key = base64.substring(counter, counter + 16) + "1A0B95C4D37286EF"
        var temp_set = []
        var temp_index = 0

        // fisher-yates algo
        for (var j = i; j < i + 16; j++) {

            // pick only unique 0-9A-F values 
            while (temp_set.includes(temp_key[temp_index])) {
                temp_index += 1
            }
            temp_set.push(temp_key[temp_index])

            // hex to decimal 
            index = parseInt("0x" + temp_key[temp_index])

            // swap
            var temp = column_key[j]
            column_key[j] = column_key[i + index]
            column_key[i + index] = temp

        }

        counter += 16
        if (counter == 256) {
            counter = 0
            base64 = crypto.createHash('sha256').update(base64).digest('hex').toUpperCase()
        }
    }

    // column transposition
    let col = 0
    column_key.forEach(function (k) {
        for (let j = 0; j < image.length; j++) {
            image1[j][col] = image[j][k]
        }
        col++
    });

    // key generation
    var base64 = crypto.createHash('sha256').update(key + duration).digest('hex').toUpperCase()
    var len1 = ((image.length / 16) * 16)
    var row_key = [...Array(image.length).keys()]

    var counter = 0
    for (var i = 0; i < len1; i += 16) {
        var temp_key = base64.substring(counter, counter + 16) + "1A0B95C4D37286EF"
        var temp_set = []
        var temp_index = 0

        // fisher-yates algo
        for (var j = i; j < i + 16; j++) {

            // pick only unique 0-9A-F values 
            while (temp_set.includes(temp_key[temp_index])) {
                temp_index += 1
            }
            temp_set.push(temp_key[temp_index])

            // hex to decimal 
            index = parseInt("0x" + temp_key[temp_index])

            // swap
            var temp = row_key[j]
            row_key[j] = row_key[i + index]
            row_key[i + index] = temp

        }

        counter += 16
        if (counter == 256) {
            counter = 0
            base64 = crypto.createHash('sha256').update(base64).digest('hex').toUpperCase()
        }
    }

    // row transposition
    let row = 0
    row_key.forEach(function (k) {
        for (let j = 0; j < image[0].length; j++) {
            image[row][j] = image1[k][j]
        }
        row++
    });

    return image
}

exports.decrypt = function (image, key, duration) {

    // Create temp array
    var image1 = Array()
    for (var i = 0; i < image.length; i++) {
        image1[i] = Array()
        for (var j = 0; j < image[0].length; j++) {
            image1[i][j] = Array()
        }
    }

    duration = Math.round(Date.now() / duration)

    // key generation
    var base64 = crypto.createHash('sha256').update(key + duration).digest('hex').toUpperCase()
    var len1 = ((image.length / 16) * 16)
    var row_key = [...Array(image.length).keys()]

    var counter = 0
    for (var i = 0; i < len1; i += 16) {
        var temp_key = base64.substring(counter, counter + 16) + "1A0B95C4D37286EF"
        var temp_set = []
        var temp_index = 0

        // fisher-yates algo
        for (var j = i; j < i + 16; j++) {

            // pick only unique 0-9A-F values 
            while (temp_set.includes(temp_key[temp_index])) {
                temp_index += 1
            }
            temp_set.push(temp_key[temp_index])

            // hex to decimal 
            index = parseInt("0x" + temp_key[temp_index])

            // swap
            var temp = row_key[j]
            row_key[j] = row_key[i + index]
            row_key[i + index] = temp

        }

        counter += 16
        if (counter == 256) {
            counter = 0
            base64 = crypto.createHash('sha256').update(base64).digest('hex').toUpperCase()
        }
    }

    // row transposition
    let row = 0
    row_key.forEach(function (k) {
        for (let j = 0; j < image[0].length; j++) {
            image1[k][j] = image[row][j]
        }
        row++
    });

    // key generation
    var base64 = crypto.createHash('sha256').update(key + duration).digest('hex').toUpperCase()
    var len1 = ((image[0].length / 16) * 16)
    var column_key = [...Array(image[0].length).keys()]

    var counter = 0
    for (var i = 0; i < len1; i += 16) {
        var temp_key = base64.substring(counter, counter + 16) + "1A0B95C4D37286EF"
        var temp_set = []
        var temp_index = 0

        // fisher-yates algo
        for (var j = i; j < i + 16; j++) {

            // pick only unique 0-9A-F values 
            while (temp_set.includes(temp_key[temp_index])) {
                temp_index += 1
            }
            temp_set.push(temp_key[temp_index])

            // hex to decimal 
            index = parseInt("0x" + temp_key[temp_index])

            // swap
            var temp = column_key[j]
            column_key[j] = column_key[i + index]
            column_key[i + index] = temp

        }

        counter += 16
        if (counter == 256) {
            counter = 0
            base64 = crypto.createHash('sha256').update(base64).digest('hex').toUpperCase()
        }
    }

    // column transposition
    let col = 0
    column_key.forEach(function (k) {
        for (let j = 0; j < image.length; j++) {
            image[j][k] = image1[j][col]
        }
        col++
    });

    return image
}
