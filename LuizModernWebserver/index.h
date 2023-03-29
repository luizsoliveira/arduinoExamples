const char INDEX_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-aFq/bzH65dt+w6FI2ooMVUpc+21e0SRygnTpmBvdBgSdnuTN7QbdgL+OapgHtvPp" crossorigin="anonymous">
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha2/dist/js/bootstrap.bundle.min.js" integrity="sha384-qKXV1j0HvMUeCBQ+QVp7JcfGl760yU08IQ+GpUo5hlbpg51QRiuqHAJz8+BrxE/N" crossorigin="anonymous"></script>
<script src="https://code.jquery.com/jquery-3.6.4.min.js" integrity="sha256-oP6HI9z1XaZNBrJURtCoUT5SUnxFr8s3BzRl+cbzUq8=" crossorigin="anonymous"></script>
<style>
body {
  font-family: Arial, Helvetica, sans-serif;
}

.mobile-container {
  margin: auto;
  background-color: #555;
  height: 500px;
  color: white;
  border-radius: 10px;
}

.topnav {
  overflow: hidden;
  background-color: #333;
  position: relative;
}

.topnav #myLinks {
  display: none;
}

.topnav a {
  color: white;
  padding: 14px 16px;
  text-decoration: none;
  font-size: 17px;
  display: block;
}

.topnav a.icon {
  background: black;
  display: block;
  position: absolute;
  right: 0;
  top: 0;
}

.topnav a:hover {
  background-color: #ddd;
  color: black;
}

.active {
  background-color: #04AA6D;
  color: white;
}
</style>
</head>
<body>

<!-- Simulate a smartphone / tablet -->
<div class="mobile-container">

<!-- Top Navigation Menu -->
<div class="topnav">
  <a href="#home" class="active"><img  height="15px" src="https://inf.passofundo.ifsul.edu.br/images/favicon_white.png">./Niterói</a>
  <div id="myLinks">
    <a href="/on">On</a>
    <a href="/off">Off</a>
  </div>
  <a href="javascript:void(0);" class="icon" onclick="myFunction()">
    <i class="fa fa-bars"></i>
  </a>
</div>

<div style="padding:16px">
  <h3>Seja bem-vindo ao exemplo inicial de Webserver Station</h3>
 
  
 <div class="form-check form-switch form-control-lg">
    <input class="form-check-input" type="checkbox" role="switch" id="flexSwitchCheckDefault" name="led">
    <label class="form-check-label" for="flexSwitchCheckDefault">Ligar/Desligar LED</label>
 </div>
 <div class="mb-3">
    <p>Você pode produzir desde a páginas HTML simples, sem uso de frameworks; até mesmo construir exemplos complexos com Bootstrap, dentre outros frameworks HTML/CSS/JS.  </p>
    <p>Clique no menu hamburguer (três barras) no canto direito superior, para ter acesso ao menu.</p>
 </div>

 <div class="mb-3">
    <label for="result" class="form-label">Result:</label>
    <div id="result"></div>   
  </div>

</div>


<!-- End smartphone / tablet look -->
</div>

<script>
function myFunction() {
  var x = document.getElementById("myLinks");
  if (x.style.display === "block") {
    x.style.display = "none";
  } else {
    x.style.display = "block";
  }
}

var checkbox = document.querySelector("input[name=led]");

checkbox.addEventListener('change', function() {
  if (this.checked) {
    $("#result").load( "/on");
  } else {
    $("#result").load( "/off");
  }
});

</script>

</body>
</html>
)=====";
