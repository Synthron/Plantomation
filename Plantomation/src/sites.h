const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
	<title>Plantomation</title>

	<style type="text/css">
		:root {
			--bgcolor: #b48346;
			--cardbgcolor: #9bde36;
			--cardbordercolor: green;
			--cardtextcolor: navy;
			--buttonbgcolor: #04aa07;
			--buttontextcolor: white;
			--titlecolor: blue;
			--inputbgcolor: lightgreen;
			--rangescalecolor: black;
		}

		body {
			font-family: Arial, Helvetica, sans-serif;
			background-color: var(--bgcolor);
		}

		.cards {
			display: flex;
			flex-wrap: wrap;
			align-items: stretch;
			justify-content: center;
		}

		.card {
			flex: 0 0 200px;
			border-radius: 20px;
			border: 1px solid var(--cardbordercolor);
			min-width: 280px;
			background: var(--cardbgcolor);
			padding: 15px;
			box-sizing: border-box;
			color: var(--cardtextcolor);
			margin: 10px;
			box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.75);
		}

		.button {
			background-color: var(--buttonbgcolor);
			border: none;
			border-radius: 5px;
			color: var(--buttontextcolor);
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
			box-shadow: 0 12px 16px 0 rgba(0, 0, 0, 0.5), 0 17px 50px 0 rgba(0, 0, 0, 0.19);
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
			color: var(--rangescalecolor);

		}

		ul {
			list-style-type: none;
			border-radius: 15px;
			margin: 0;
			padding: 0;
			overflow: hidden;
			border: 1px solid var(--cardbordercolor);
			background-color: var(--cardbgcolor);
		}

		li {
			float: left;
		}

		li a {
			display: block;
			color: #666;
			text-align: center;
			padding: 14px 16px;
			text-decoration: none;
		}

		li a:hover:not(.active) {
			background-color: var(--inputbgcolor);
		}

		li a.active {
			color: white;
			background-color: var(--buttonbgcolor);
		}
	</style>

</head>

<body>
	<center>
		<h1 style="color: var(--titlecolor);">
			Plantomation Interface
		</h1>
		<!--Don't change this color in h3, it will be overridden by Ajax-->
		<h3>
			System Status: <span id="system" style="color: green">Normal Operation</span>
		</h3>
	</center>
	<ul>
		<li><a class="active" href="/">Control</a></li>
		<li><a href="/config">Configuration</a></li>
		<li><a href="/about">About</a></li>
	</ul>

	<main class="cards">
		<div class="card">
			<center>
				<h3>Channel 1</h3>
			</center>
			<form action="/ch1" target="hidden-form">
				<input type="checkbox" value="1" name="channel1" id="cb1">
				<span id="state1">Inactive</span><br><br>
				Plant Name:
				<input type="text" id="Name1" name="Name1" value="Foo"
					style="background-color: var(--inputbgcolor)"><br><br>
				<label for="hume1">Soil moisture threshold:</label><br>
				<input type="range" id="hume1" name="hume1" list="values" />
				<datalist id="values">
					<option value="0" label="dry"></option>
					<option value="12"></option>
					<option value="25"></option>
					<option value="38"></option>
					<option value="50" label="mid"></option>
					<option value="62"></option>
					<option value="75"></option>
					<option value="88"></option>
					<option value="100" label="wet"></option>
				</datalist><br>
				Current Moisture: <b><span id="ADCValue1">0</span> </b>%<br><br>
				<input type="submit" class="button" value="Save">
			</form>
		</div>
		
		<div class="card">
			<center>
				<h3>Channel 2</h3>
			</center>
			<form action="/ch2" target="hidden-form">
				<input type="checkbox" value="1" name="channel2" id="cb2">
				<span id="state2">Inactive</span><br><br>
				Plant Name:
				<input type="text" id="Name2" name="Name2" value="Bar"
					style="background-color: var(--inputbgcolor)"><br><br>
				<label for="hume2">Soil moisture threshold:</label><br>
				<input type="range" id="hume2" name="hume2" list="values" />
				<datalist id="values">
					<option value="0" label="dry"></option>
					<option value="50" label="mid"></option>
					<option value="100" label="wet"></option>
				</datalist><br>
				Current Moisture: <b><span id="ADCValue2">0</span> </b>%<br><br>
				<input type="submit" class="button" value="Save">
			</form>
		</div>

		<div class="card">
			<center>
				<h3>Channel 3</h3>
			</center>
			<form action="/ch3" target="hidden-form">
				<input type="checkbox" value="1" name="channel3" id="cb3">
				<span id="state3">Inactive</span><br><br>
				Plant Name:
				<input type="text" id="Name3" name="Name3" value="Baz"
					style="background-color: var(--inputbgcolor)"><br><br>
				<label for="hume3">Soil moisture threshold:</label><br>
				<input type="range" id="hume3" name="hume3" list="values" />
				<datalist id="values">
					<option value="0" label="dry"></option>
					<option value="50" label="mid"></option>
					<option value="100" label="wet"></option>
				</datalist><br>
				Current Moisture: <b><span id="ADCValue3">0</span> </b>%<br><br>
				<input type="submit" class="button" value="Save">
			</form>
		</div>

		<div class="card">
			<center>
				<h3>Channel 4</h3>
			</center>
			<form action="/ch4" target="hidden-form">
				<input type="checkbox" value="1" name="channel4" id="cb4">
				<span id="state4">Inactive</span><br><br>
				Plant Name:
				<input type="text" id="Name4" name="Name4" value="Qux"
					style="background-color: var(--inputbgcolor)"><br><br>
				<label for="hume4">Soil moisture threshold:</label><br>
				<input type="range" id="hume4" name="hume4" list="values" />
				<datalist id="values">
					<option value="0" label="dry"></option>
					<option value="50" label="mid"></option>
					<option value="100" label="wet"></option>
				</datalist><br>
				Current Moisture: <b><span id="ADCValue4">0</span> </b>%<br><br>
				<input type="submit" class="button" value="Save">
			</form>
		</div>
	</main>

	<script>
		setInterval(function () {
			// Call a function repetatively with 2 Second interval
			getCyclic();
		}, 2000); //2000mSeconds update rate

		//Call function on Page Load
		document.addEventListener("DOMContentLoaded", function () {
			var xhttp = new XMLHttpRequest();
			xhttp.open("GET", "initial", true);

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
					if (data.cb1 == 1)
						document.getElementById("cb1").checked = true;
					else
						document.getElementById("cb1").checked = false;
					if (data.cb2 == 1)
						document.getElementById("cb2").checked = true;
					else
						document.getElementById("cb2").checked = false;
					if (data.cb3 == 1)
						document.getElementById("cb3").checked = true;
					else
						document.getElementById("cb3").checked = false;
					if (data.cb4 == 1)
						document.getElementById("cb4").checked = true;
					else
						document.getElementById("cb4").checked = false;
				}
			};

			xhttp.send();
			getCyclic();
		});

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

const char CONFIG_page[] PROGMEM = R"=====(
<html>
<head>
	<title>Plantomation</title>

	<style type="text/css">
		:root {
			--bgcolor: #b48346;
			--cardbgcolor: #9bde36;
			--cardbordercolor: green;
			--cardtextcolor: navy;
			--buttonbgcolor: #04aa07;
			--buttontextcolor: white;
			--titlecolor: blue;
			--inputbgcolor: lightgreen;
			--rangescalecolor: black;
		}

		body {
			font-family: Arial, Helvetica, sans-serif;
			background-color: var(--bgcolor);
		}

		.card {
			flex: 0 0 200px;
			border-radius: 20px;
			border: 1px solid var(--cardbordercolor);
			min-width: 280px;
			/* min-height: 280px;*/
			background: var(--cardbgcolor);
			padding: 15px;
			box-sizing: border-box;
			color: var(--cardtextcolor);
			margin: 10px;
			box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.75);
		}

		.button {
			background-color: var(--buttonbgcolor);
			/* Green */
			border: none;
			border-radius: 5px;
			color: var(--buttontextcolor);
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
			box-shadow: 0 12px 16px 0 rgba(0, 0, 0, 0.5), 0 17px 50px 0 rgba(0, 0, 0, 0.19);
		}

		ul {
			list-style-type: none;
			border-radius: 15px;
			margin: 0;
			padding: 0;
			overflow: hidden;
			border: 1px solid var(--cardbordercolor);
			background-color: var(--cardbgcolor);
		}

		li {
			float: left;
		}

		li a {
			display: block;
			color: #666;
			text-align: center;
			padding: 14px 16px;
			text-decoration: none;
		}

		li a:hover:not(.active) {
			background-color: var(--inputbgcolor);
		}

		li a.active {
			color: white;
			background-color: var(--buttonbgcolor);
		}
	</style>
</head>

<body>

	<center>
		<h1 style="color: var(--titlecolor);">
			Plantomation Interface
		</h1>
		<!--Don't change this color in h3, it will be overridden by Ajax-->
		<h3>
			System Status: <span id="system" style="color: green">Normal Operation</span>
		</h3>
	</center>

	<ul>
		<li><a href="/">Control</a></li>
		<li><a class="active" href="/config">Configuration</a></li>
		<li><a href="/about">About</a></li>
	</ul>


	<div class="card">
		<form action="modes">
			<h3 style="margin: 0">
				<center>Control Mode Selection</center>
			</h3>
			<table style="width: 100%; text-align: left;">
				<tr>
					<th>
						<p>Channel 1</p>
						<input type="radio" id="ch1_moist" , name="ch1_mode" value="1" checked="checked">
						<label for="ch1_moist">Moisture</label><br>
						<input type="radio" id="ch1_time" , name="ch1_mode" value="2">
						<label for="ch1_moist">Time</label>
					</th>
					<th>
						<p>Channel 2</p>
						<input type="radio" id="ch2_moist" , name="ch2_mode" value="1" checked="checked">
						<label for="ch2_moist">Moisture</label><br>
						<input type="radio" id="ch2_time" , name="ch2_mode" value="2">
						<label for="ch2_moist">Time</label>
					</th>
					<th>
						<p>Channel 3</p>
						<input type="radio" id="ch3_moist" , name="ch3_mode" value="1" checked="checked">
						<label for="ch3_moist">Moisture</label><br>
						<input type="radio" id="ch3_time" , name="ch3_mode" value="2">
						<label for="ch3_moist">Time</label>
					</th>
					<th>
						<p>Channel 4</p>
						<input type="radio" id="ch4_moist" , name="ch4_mode" value="1" checked="checked">
						<label for="ch4_moist">Moisture</label><br>
						<input type="radio" id="ch4_time" , name="ch4_mode" value="2">
						<label for="ch4_moist">Time</label>
					</th><br>
				</tr>
			</table>
			<center><input type="submit" class="button" value="Save"></center>
		</form>
	</div>

	<div class="card">
		<center><h3>New WiFi Config</h3>
    </center>
    <form action="wifi_set" method="post">
      <table>
        <tr>
          <td>
            Wifi-Name:
          </td>
          <td>
            <input type="text" id="ssid" name="ssid" value=""
					style="background-color: var(--inputbgcolor)"><br>
          </td>
          <td>
            <input type="radio" id="wifimode" , name="wifimode" value="1" checked="checked">
						<label for="ch4_moist">Station Mode</label><br>
          </td>
        </tr>
        <tr>
          <td>
            Wifi-Password:
          </td>
          <td>
            <input type="password" id="passwd" name="passwd" value=""
					style="background-color: var(--inputbgcolor)"><br>
          </td>
          <td>
            <input type="radio" id="wifimode" , name="wifimode" value="0">
						<label for="ch4_moist">AccesPoint Mode</label><br>
          </td>
        </tr>
        <tr>
          <td>
            Device Hostname:
          </td>
          <td>
            <input type="text" id="hostname" name="hostname" value="Plantomation"
					style="background-color: var(--inputbgcolor)"><br>
          </td>
        </tr>
      </table>
      <center><input type="submit" class="button" value="Save"></center>
    </form>
	</div>

	<script>
		//Call function on Page Load
		/*
		document.addEventListener("DOMContentLoaded", function () {
			var xhttp = new XMLHttpRequest();
			xhttp.open("GET", "initial", true);

			xhttp.onload = function () {
				if (this.status === 200) {
					var data = JSON.parse(xhttp.responseText);

					document.getElementById("Name4").value = data.Name4;
					if (data.cb1 == 1)
						document.getElementById("cb1").checked = true;
					else
						document.getElementById("cb1").checked = false;
				}
			};

			xhttp.send();
		});
		*/
	</script>
</body>
</html>
)=====";

const char ABOUT_page[] PROGMEM = R"=====(
<html>

<head>
	<title>Plantomation</title>

	<style type="text/css">
		:root {
			--bgcolor: #b48346;
			--cardbgcolor: #9bde36;
			--cardbordercolor: green;
			--cardtextcolor: navy;
			--buttonbgcolor: #04aa07;
			--buttontextcolor: white;
			--titlecolor: blue;
			--inputbgcolor: lightgreen;
			--rangescalecolor: black;
		}

		body {
			font-family: Arial, Helvetica, sans-serif;
			background-color: var(--bgcolor);
		}

		.card {
			flex: 0 0 200px;
			border-radius: 20px;
			border: 1px solid var(--cardbordercolor);
			min-width: 280px;
			/* min-height: 280px;*/
			background: var(--cardbgcolor);
			padding: 15px;
			box-sizing: border-box;
			color: var(--cardtextcolor);
			margin: 10px;
			box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.75);
		}

		ul {
			list-style-type: none;
			border-radius: 15px;
			margin: 0;
			padding: 0;
			overflow: hidden;
			border: 1px solid var(--cardbordercolor);
			background-color: var(--cardbgcolor);
		}

		li {
			float: left;
		}

		li a {
			display: block;
			color: #666;
			text-align: center;
			padding: 14px 16px;
			text-decoration: none;
		}

		li a:hover:not(.active) {
			background-color: var(--inputbgcolor);
		}

		li a.active {
			color: white;
			background-color: var(--buttonbgcolor);
		}
	</style>

</head>

<body>
	<center>
		<h1 style="color: var(--titlecolor);">
			Plantomation Interface
		</h1>

	</center>

	<ul>
		<li><a href="/">Control</a></li>
		<li><a href="/config">Configuration</a></li>
		<li><a class="active" href="/about">About</a></li>
	</ul>

	<div class="card">
		<center><h2>About Plantomation</h2></center>
		
	</div>
</body>
</html>
)=====";