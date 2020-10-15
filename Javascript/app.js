var key = "Gauravgauravsirav2399@gmail.com9079035112";
var grain = 100;

var encryptButton;
var decryptButton;
var canvas;
var context;

function init() {
  var image = document.getElementById("SourceImage");
  encryptButton = document.getElementById("EncryptButton");
  decryptButton = document.getElementById("DecryptButton");
  canvas = document.getElementById("Canvas");
  context = canvas.getContext("2d");

  // Set the canvas the same width and height of the image
  canvas.width = image.width;
  canvas.height = image.height;

  decryptButton.addEventListener("click", function () {
    drawImage(image);
    // Or
    // var image = new Image();
    // image.onload = function () {
    //    drawImage(image);
    // }
    // image.src = 'image.jpg';
  });

  encryptButton.addEventListener("click", encryptImg);
}

function drawImage(image) {
  context.drawImage(image, 0, 0);
}

function encryptImg() {
  var image = document.getElementById("SourceImage");
  canvas = document.getElementById("Canvas");
  context = canvas.getContext("2d");
  var imageData = context.getImageData(0, 0, canvas.width, canvas.height);
  temp = imageData.data;

  var tempo = new Array();
  for (let i = 0; i < 317; i++) {
    for (let j = 0; j < 240; j++) {
      for (let k = 0; k < 4; k++) {
        var x = temp[i * 240 * 4 + j * 4 + k];
        tempo[i] = [];
        tempo[i][j] = [];
        tempo[i][j][k] = x;
      }
    }
  }

  var base64 = CryptoJS.AES.encrypt(key, "10/14/2020/20/13");
  var len1 = base64.toString().length;
  var len2 = image.width;

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
  var max = image.width / grain; //temp.getWidth / grain

  for (var i = 0; i < base64.toString().length; i++) {
    sb.append(base64.charCodeAt(i));
  }

  var ch = [...sb.toString()];

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

  for (var i = 0; i < image.width / grain; i++) {
    //i<temp.getwidth
    set.add(i);
  }

  var temp1 = new Array();
  Array.prototype.push.apply(temp1, tempo);
  var col = 0;
  for (var k = 0; k < set.length; k++) {
    var num = k * grain;
    for (var i = 0; i < grain; i++) {
      for (var j = 0; j < image.height; j++) {
        temp1[col][j][0] = tempo[num + i][j][0];
        temp1[col][j][1] = tempo[num + i][j][1];
        temp1[col][j][2] = tempo[num + i][j][2];
      }
      col++;
    }
  }

  len1 = base64.toString().length;
  len2 = image.height; //temp.getHeight

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
  var max = image.height / grain; //temp.getHeight / grain

  for (var i = 0; i < base64.toString().length; i++) {
    sb.append(base64.charCodeAt(i));
  }

  var ch = [...sb.toString()];

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

  for (var i = 0; i < image.height / grain; i++) {
    //i<temp.getwidth
    set.add(i);
  }

  var temp2 = new Array();
  Array.prototype.push.apply(temp2, temp1);
  var row = 0;
  for (var k = 0; k < set.length; k++) {
    var num = k * grain;
    for (var i = 0; i < grain; i++) {
      for (var j = 0; j < image.height; j++) {
        temp2[j][row][0] = temp1[j][num + i][0];
        temp2[j][row][1] = temp1[j][num + i][1];
        temp2[j][row][2] = temp1[j][num + i][2];
      }
      col++;
    }
  }
  //image1.setimageBitmap(pic1);
  console.log("rget");

  context.putImageData(imageData, 0, 0);
}

window.addEventListener("load", init);
