const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html style="font-family: Arial, Helvetica, sans-serif">

<head>
  <title>Plantomation</title>
</head>

<body style="background-color: #b48346">

  <style type="text/css">
    .card {
      border-radius: 20px;
      border: 1px solid green;
      min-width: 280px;
      /* min-height: 280px;*/
      background: rgb(155, 222, 54);
      padding: 15px;
      box-sizing: border-box;
      color: #000;
      margin: 10px;
      box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.75);
    }

    .button {
      background-color: #04aa07;
      /* Green */
      border: none;
      border-radius: 5px;
      color: white;
      padding: 2px 32px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      margin: 4px 2px;
      cursor: pointer;
      -webkit-transition-duration: 0.2s;
      /* Safari */
      transition-duration: 0.2s;
    }

    .button:hover {
      box-shadow: 0 12px 16px 0 rgba(0, 0, 0, 0.24), 0 17px 50px 0 rgba(0, 0, 0, 0.19);
    }

    datalist {
      display: flex;
      flex-direction: row;
      justify-content: space-between;
      writing-mode: horizontal-lr;
      width: 250px;
    }

    option {
      padding: 0;
    }

    input[type="range"] {
      width: 250px;
      margin: 0;
      color: black;

    }
  </style>

  <h1 style="color: blue; padding-left: 160px;">Plantomation Interface</h1>
  <h3 style="padding-left: 180px;">System Status: <span id="system" style="color: green">Normal Operation</span></h3>
  <table>
    <tr>
      <td>
        <div class="card">
          <u>
            <h3>Channel 1</h3>
          </u>
          <form action="/get" target="hidden-form">
            <input type="hidden" name="channel1" value="0"><input type="checkbox" id="cb1" onclick="this.previousSibling.value=1-this.previousSibling.value">
            <span id="state1">Inactive</span><br><br>
            Plant Name:
            <input type="text" name="Name1" value="Foo" style="background-color: lightgreen"><br><br>
            <label for="hume1">Soil moisture threshold:</label><br>
            <input type="range" id="hume1" name="hume1" list="values" />
            <datalist id="values">
              <option value="0" label="dry"></option>
              <option value="25"></option>
              <option value="50" label="mid"></option>
              <option value="75"></option>
              <option value="100" label="wet"></option>
            </datalist><br>
            Current Moisture: <b><span id="ADCValue1">0</span> </b>%<br><br>
            <input type="submit" class="button" value="Save">
          </form>
        </div>
      </td>
      <td>
        <div class="card">
          <u>
            <h3>Channel 2</h3>
          </u>
          <form action="/get" target="hidden-form">
            <input type="hidden" name="channel2" value="0"><input type="checkbox" id="cb2" onclick="this.previousSibling.value=1-this.previousSibling.value">
            <span id="state2">Inactive</span><br><br>
            Plant Name:
            <input type="text" name="Name2" value="Bar" style="background-color: lightgreen"><br><br>
            <label for="hume2">Soil moisture threshold:</label><br>
            <input type="range" id="hume2" name="hume2" list="values" />
            <datalist id="values">
              <option value="0" label="dry"></option>
              <option value="25"></option>
              <option value="50" label="mid"></option>
              <option value="75"></option>
              <option value="100" label="wet"></option>
            </datalist><br>
            Current Moisture: <b><span id="ADCValue2">0</span> </b>%<br><br>
            <input type="submit" class="button" value="Save">
          </form>
        </div>
      </td>
    </tr>
    <tr>
      <td>
        <div class="card">
          <u>
            <h3>Channel 3</h3>
          </u>
          <form action="/get" target="hidden-form">
            <input type="hidden" name="channel3" value="0"><input type="checkbox" id="cb3" onclick="this.previousSibling.value=1-this.previousSibling.value">
            <span id="state3">Inactive</span><br><br>
            Plant Name:
            <input type="text" name="Name3" value="Baz" style="background-color: lightgreen"><br><br>
            <label for="hume3">Soil moisture threshold:</label><br>
            <input type="range" id="hume3" name="hume3" list="values" />
            <datalist id="values">
              <option value="0" label="dry"></option>
              <option value="25"></option>
              <option value="50" label="mid"></option>
              <option value="75"></option>
              <option value="100" label="wet"></option>
            </datalist><br>
            Current Moisture: <b><span id="ADCValue3">0</span> </b>%<br><br>
            <input type="submit" class="button" value="Save">
          </form>
        </div>
      </td>
      <td>
        <div class="card">
          <u>
            <h3>Channel 4</h3>
          </u>
          <form action="/get" target="hidden-form">
            <input type="hidden" name="channel4" value="0"><input type="checkbox" id="cb4" onclick="this.previousSibling.value=1-this.previousSibling.value">
            <span id="state4">Inactive</span><br><br>
            Plant Name:
            <input type="text" name="Name4" value="Qux" style="background-color: lightgreen"><br><br>
            <label for="hume4">Soil moisture threshold:</label><br>
            <input type="range" id="hume4" name="hume4" list="values" />
            <datalist id="values">
              <option value="0" label="dry"></option>
              <option value="25"></option>
              <option value="50" label="mid"></option>
              <option value="75"></option>
              <option value="100" label="wet"></option>
            </datalist><br>
            Current Moisture: <b><span id="ADCValue4">0</span> </b>%<br><br>
            <input type="submit" class="button" value="Save">
          </form>
        </div>
      </td>
    </tr>
  </table>

  <script>
    //Call function on Page Load
    //document.addEventListener("DOMContentLoaded", getInitial());

    setInterval(function () {
      // Call a function repetatively with 2 Second interval
      //getCyclic();
    }, 2000); //2000mSeconds update rate

    function getInitial() {
      var xhttp = new XMLHttpRequest();
      xhttp.open("GET", "cyclic", true);

      xhttp.onload = function () {
        if (this.status === 200) {
          var data = JSON.parse(xhttp.responseText);
          document.getElementById("hume1").value = data.hume1;
          document.getElementById("hume2").value = data.hume2;
          document.getElementById("hume3").value = data.hume3;
          document.getElementById("hume4").value = data.hume4;
          document.getElementById("Name1").value = data.Name1;
          document.getElementById("Name2").value = data.Name2;
          document.getElementById("Name3").value = data.Name3;
          document.getElementById("Name4").value = data.Name4;
          if (data.check1 == "1")
            document.getElementById("cb1").checked = true;
          else
            document.getElementById("cb1").checked = false;
          if (data.check2 == "1")
            document.getElementById("cb2").checked = true;
          else
            document.getElementById("cb2").checked = false;
          if (data.check3 == "1")
            document.getElementById("cb3").checked = true;
          else
            document.getElementById("cb3").checked = false;
          if (data.check4 == "1")
            document.getElementById("cb4").checked = true;
          else
            document.getElementById("cb4").checked = false;
        }
      };

      xhttp.send();
    }

    function getCyclic() {
      var xhttp = new XMLHttpRequest();
      xhttp.open("GET", "cyclic", true);

      xhttp.onload = function () {
        if (this.status === 200) {
          var data = JSON.parse(xhttp.responseText);
          document.getElementById("system").innerText = data.system;
          document.getElementById("system").style.color = data.systemcolor;
          document.getElementById("ADCValue1").innerText = data.ADCValue1;
          document.getElementById("ADCValue2").innerText = data.ADCValue2;
          document.getElementById("ADCValue3").innerText = data.ADCValue3;
          document.getElementById("ADCValue4").innerText = data.ADCValue4;
          document.getElementById("state1").innerText = data.state1;
          document.getElementById("state2").innerText = data.state2;
          document.getElementById("state3").innerText = data.state3;
          document.getElementById("state4").innerText = data.state4;
        }
      };
      xhttp.send();
    }
  </script>
</body>

</html>
)=====";