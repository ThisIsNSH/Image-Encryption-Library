var key = "Gauravgauravsirav2399@gmail.com9079035112";
var grain = 100;

var encryptButton;
var decryptButton;
var canvas;
var context;

function init() {
  var image = document.getElementById("SourceImage");
  encryptButton = document.getElementById("EncryptButton");
  displayButton = document.getElementById("DisplayButton");
  canvas = document.getElementById("canvas");
  context = canvas.getContext("2d");
  canvas2 = document.getElementById("canvas2");
  context2 = canvas2.getContext("2d");

  // Set the canvas the same width and height of the image
  canvas.width = image.width;
  canvas.height = image.height;
  canvas2.width = image.width;
  canvas2.height = image.height;

  displayButton.addEventListener("click", function () {
    drawImage(image);
    // Or
    // var image = new Image();
    // image.onload = function () {
    //    drawImage(image);
    // }
    // image.src = 'image.jpg';
  });

  encryptButton.addEventListener("click", onClick);

  //add transparent layer
  var image2 = new Image();
  image2.onload = function () {
    context2.drawImage(image2, 0, 0);
  };
  image2.src = "./img/transparent.png";
}

function drawImage(image) {
  context.drawImage(image, 0, 0);
}

function onClick() {
  var imageData = context.getImageData(0, 0, canvas.width, canvas.height);
  test(imageData.data);
  context.putImageData(imageData, 0, 0);
}

function test(data) {
  for (let i = 0; i < canvas.height; i++) {
    for (let j = 0; j < canvas.width; j += 2) {
      let id = 4 * (j + i * canvas.width);
      let x = data[id + 12];
      data[id + 12] = data[id];
      data[id] = x;

      let y = data[id + 13];
      data[id + 13] = data[id + 1];
      data[id + 1] = y;

      let z = data[id + 14];
      data[id + 14] = data[id + 2];
      data[id + 2] = z;
    }
  }
}

function encryptImg() {
  var imageData = context.getImageData(0, 0, canvas.width, canvas.height);
  data = imageData.data;

  var base64 = CryptoJS.AES.encrypt(key, "10/14/2020/20/13");
  var len1 = base64.toString().length;
  var len2 = canvas.width;

  if (len2 < len1) {
    base64 = base64.toString().substring(0, len2);
  } else if (len2 > len1) {
    var s = new StringBuilder();
    for (var i = 0; i < len2 / len1; i++) {
      s.append(base64);
    }
    s.append(base64);
    base64 = s.toString().substring(0, len2);
  }

  var sb = new StringBuilder();

  let set = new Set();
  let max = canvas.width / grain; //temp.getWidth / grain

  for (var i = 0; i < base64.toString().length; i++) {
    sb.append(base64.charCodeAt(i));
  }

  let ch = [...sb.toString()];

  for (let i = 0; i < ch.length; i++) {
    var sb1 = new StringBuilder();
    for (let j = i; j < ch.length; j++) {
      sb1.append(ch[j]);
      let k = parseInt(sb1.toString());
      if (k < max) {
        if (set.add(k)) break;
      } else {
        while (k >= max || (k >= 0 && !set.add(k))) {
          k--;
        }
        break;
      }
    }
    if (set.size == max) break;
  }

  for (let i = 0; i < canvas.width / grain; i++) {
    //i<temp.getwidth
    set.add(i);
  }

  let col = 0,
    id1 = 0,
    id2 = 0;
  for (let k = 0; k < set.size; k++) {
    let num = k * grain;
    for (let i = 0; i < grain; i++) {
      for (let j = 0; j < canvas.height; j++) {
        id1 = 4 * (j + (num + i) * canvas.width);
        id2 = 4 * (j + col * canvas.width);
        data[id2] = data[id1];
        data[id2 + 1] = data[id1 + 1];
        data[id2 + 2] = data[id1 + 2];
      }
    }
    col++;
  }

  len1 = base64.toString().length;
  len2 = canvas.height; //temp.getHeight

  if (len2 < len1) {
    base64 = base64.toString().substring(0, len2);
  } else if (len2 > len1) {
    var s = new StringBuilder();
    for (let i = 0; i < len2 / len1; i++) {
      s.append(base64);
    }
    s.append(base64);
    base64 = s.toString().substring(0, len2);
  }

  var sb = new StringBuilder();

  set = new Set();
  max = canvas.height / grain; //temp.getHeight / grain

  for (let i = 0; i < base64.toString().length; i++) {
    sb.append(base64.charCodeAt(i));
  }

  ch = [...sb.toString()];

  for (var i = 0; i < ch.length; i++) {
    let sb1 = new StringBuilder();
    for (let j = i; j < ch.length; j++) {
      sb1.append(ch[j]);
      let k = parseInt(sb1.toString());
      if (k < max) {
        if (set.add(k)) break;
      } else {
        while (k >= max || (k >= 0 && !set.add(k))) {
          k--;
        }
        break;
      }
    }
    if (set.size == max) break;
  }

  for (let i = 0; i < canvas.height / grain; i++) {
    set.add(i);
  }

  let row = 0;
  for (let k = 0; k < set.size; k++) {
    let num = k * grain;
    for (let i = 0; i < grain; i++) {
      for (let j = 0; j < canvas.width; j++) {
        id1 = 4 * (num + i + j * canvas.height);
        id2 = 4 * (row + j * canvas.height);
        data[id2] = data[id1];
        data[id2 + 1] = data[id1 + 1];
        data[id2 + 2] = data[id1 + 2];
      }
    }
  }

  context.putImageData(imageData, 0, 0);
}
//temp1[4 * (j + col * image.width)] = 4 * temp[j + (num + i) * image.width];

window.addEventListener("load", init);
