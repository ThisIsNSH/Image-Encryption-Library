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
  canvas = document.getElementById("Canvas");
  context = canvas.getContext("2d");

  // Set the canvas the same width and height of the image
  canvas.width = image.width;
  canvas.height = image.height;

  displayButton.addEventListener("click", function () {
    drawImage(image);
  });

  encryptButton.addEventListener("click", encryptImg);
}

function drawImage(image) {
  context.drawImage(image, 0, 0);
}

function encryptImg() {
  var imageData = context.getImageData(0, 0, canvas.width, canvas.height);
  temp = imageData.data;

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

  var temp1 = new Array();
  var col = 0;
  for (let k = 0; k < set.size; k++) {
    var num = k * grain;
    for (let i = 0; i < grain; i++) {
      for (let j = 0; j < canvas.height; j++) {
        temp[4 * (j + col * canvas.width)] =
          temp[4 * (j + (num + i) * canvas.width)];
        temp[4 * (j + col * canvas.width) + 1] =
          temp[4 * (j + (num + i) * canvas.width) + 1];
        temp[4 * (j + col * canvas.width) + 2] =
          temp[4 * (j + (num + i) * canvas.width) + 2];
        temp[4 * (j + col * canvas.width) + 3] = 150;
      }
      col++;
    }
  }

  len1 = base64.toString().length;
  len2 = canvas.height; //temp.getHeight

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

  set = new Set();
  max = canvas.height / grain; //temp.getHeight / grain

  for (var i = 0; i < base64.toString().length; i++) {
    sb.append(base64.charCodeAt(i));
  }

  ch = [...sb.toString()];

  for (var i = 0; i < ch.length; i++) {
    var sb1 = new StringBuilder();
    for (var j = i; j < ch.length; j++) {
      sb1.append(ch[j]);
      var k = parseInt(sb1.toString());
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

  for (var i = 0; i < canvas.height / grain; i++) {
    //i<temp.getwidth
    set.add(i);
  }

  var temp2 = new Array();
  var row = 0;
  for (var k = 0; k < set.size; k++) {
    var num = k * grain;
    for (var i = 0; i < grain; i++) {
      for (var j = 0; j < canvas.width; j++) {
        temp[4 * (row + j * canvas.height)] =
          temp[4 * (num + i + j * canvas.height)];
        temp[4 * (row + j * canvas.height) + 1] =
          temp[4 * (num + i + j * canvas.height) + 1];
        temp[4 * (row + j * canvas.height) + 2] =
          temp[4 * (num + i + j * canvas.height) + 2];
        temp[4 * (row + j * canvas.height) + 3] = 255;
        row++;
      }
    }

    //image1.setimageBitmap(pic1);
    console.log(temp);

    context.putImageData(imageData, 0, 0);
  }
}
//temp1[4 * (j + col * image.width)] = 4 * temp[j + (num + i) * image.width];

window.addEventListener("load", init);
