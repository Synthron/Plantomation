const char MAIN_page[] = R"=====(
<!DOCTYPE html>
<html>

<head>
	<title>Plantomation</title>

	<style type="text/css">
		:root {
			--bgcolor: #d1974f;
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
		input[type="number"] {
			width: 80px;
			background-color: var(--inputbgcolor);
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
			System Status: <span id="system" style="color: green"></span>
		</h3>
	</center>
	<ul>
		<li><a class="active" href="/">Control</a></li>
		<li><a href="/config">Configuration</a></li>
		<li><a href="/about">About</a></li>
	</ul>

	

	<main class="cards">

		<div class="card" id="card1" >
			<center>
				<h3>Channel 1</h3>
			</center>
			<form action="/ch1" target="_blank">
				<b>Mode:</b> <span id="state1"></span><br><br>
				Plant Name:<br>
				<input type="text" id="Name1" name="Name1" value=""
							 style="background-color: var(--inputbgcolor)"><br><br>
				
				<div id="timediv1" >
				<table>
				<tr>
					<td>Pump 1 Interval [hours]:</td>
					<td>Pump 2 Interval [hours]:</td>
				</tr>
				<tr>
					<td><input type="number" id="time1_1" name="time1_1" value=""></td>
					<td><input type="number" id="time1_2" name="time1_2" value=""></td>
		</tr>
				<tr>
					<td>Pump 1 Volume [ml]:</td>
					<td>Pump 2 Volume [ml]:</td>
				</tr>
				<tr>
					<td><input type="number" id="vol1_1" name="vol1_1" value=""></td>
					<td><input type="number" id="vol1_2" name="vol1_2" value=""></td>
				</tr>
				</table>
				</div>
				<div id="moistdiv1" >
					<label for="hume1">Soil moisture threshold:</label><br>
					<input type="range" id="hume1" name="hume1" list="values" />
					<datalist id="values">
						<option value="0" label="dry"></option>
						<option value="25"></option>
						<option value="50" label="mid"></option>
						<option value="75"></option>
						<option value="100" label="wet"></option>
					</datalist><br><br>
					Current Moisture: <b><span id="ADCValue1">0</span> </b>%<br><br>
				</div>
				<center><input type="submit" class="button" value="Save"></center>
			</form>
		</div>

		<div class="card" id="card1" hidden>
			<center>
				<h3>Channel 1</h3>
			</center>
			<form action="/ch1" target="_blank">
				<b>Mode:</b> <span id="state1"></span><br><br>
				Plant Name:<br>
				<input type="text" id="Name1" name="Name1" value=""
					style="background-color: var(--inputbgcolor)"><br><br>
					<div id="timediv1" hidden>
						Watering Interval [hours]:<br>
					<input type="text" id="time1" name="time1" value=""
						style="background-color: var(--inputbgcolor)"><br>
						Water Volume [ml]:<br>
					<input type="text" id="vol1" name="vol1" value=""
						style="background-color: var(--inputbgcolor)"><br>
					</div>
        <div id="moistdiv1" hidden>
          <label for="hume1">Soil moisture threshold:</label><br>
          <input type="range" id="hume1" name="hume1" list="values" />
          <datalist id="values">
            <option value="0" label="dry"></option>
						<option value="25"></option>
            <option value="50" label="mid"></option>
						<option value="75"></option>
            <option value="100" label="wet"></option>
          </datalist><br><br>
					Current Moisture: <b><span id="ADCValue1">0</span> </b>%<br><br>
        </div>
				<center><input type="submit" class="button" value="Save"></center>
			</form>
		</div>

		<div class="card" id="card2" hidden>
			<center>
				<h3>Channel 2</h3>
			</center>
			<form action="/ch2" target="_blank">
				<b>Mode:</b> <span id="state2"></span><br><br>
				Plant Name:<br>
				<input type="text" id="Name2" name="Name2" value=""
					style="background-color: var(--inputbgcolor)"><br><br>
					<div id="timediv2" hidden>
						Watering Interval [hours]:<br>
					<input type="text" id="time2" name="time2" value=""
						style="background-color: var(--inputbgcolor)"><br>
						Water Volume [ml]:<br>
					<input type="text" id="vol2" name="vol2" value=""
						style="background-color: var(--inputbgcolor)"><br>
					</div>
        <div id="moistdiv2" hidden>
          <label for="hume2">Soil moisture threshold:</label><br>
          <input type="range" id="hume2" name="hume2" list="values" />
          <datalist id="values">
            <option value="0" label="dry"></option>
						<option value="25"></option>
            <option value="50" label="mid"></option>
						<option value="75"></option>
            <option value="100" label="wet"></option>
          </datalist><br><br>
					Current Moisture: <b><span id="ADCValue2">0</span> </b>%<br><br>
        </div>
				<center><input type="submit" class="button" value="Save"></center>
			</form>
		</div>

		<div class="card" id="card3" hidden>
			<center>
				<h3>Channel 3</h3>
			</center>
			<form action="/ch3" target="_blank">
				<b>Mode:</b> <span id="state3"></span><br><br>
				Plant Name:<br>
				<input type="text" id="Name3" name="Name3" value=""
					style="background-color: var(--inputbgcolor)"><br><br>
					<div id="timediv3" hidden>
						Watering Interval [hours]:<br>
					<input type="text" id="time3" name="time3" value=""
						style="background-color: var(--inputbgcolor)"><br>
						Water Volume [ml]:<br>
					<input type="text" id="vol3" name="vol3" value=""
						style="background-color: var(--inputbgcolor)"><br>
					</div>
        <div id="moistdiv3" hidden>
          <label for="hume3">Soil moisture threshold:</label><br>
          <input type="range" id="hume3" name="hume3" list="values" />
          <datalist id="values">
            <option value="0" label="dry"></option>
						<option value="25"></option>
            <option value="50" label="mid"></option>
						<option value="75"></option>
            <option value="100" label="wet"></option>
          </datalist><br><br>
					Current Moisture: <b><span id="ADCValue3">0</span> </b>%<br><br>
        </div>
				<center><input type="submit" class="button" value="Save"></center>
			</form>
		</div>

		<div class="card" id="card4" hidden>
			<center>
				<h3>Channel 4</h3>
			</center>
			<form action="/ch4" target="_blank">
				<b>Mode:</b> <span id="state4"></span><br><br>
				Plant Name:<br>
				<input type="text" id="Name4" name="Name4" value=""
					style="background-color: var(--inputbgcolor)"><br><br>
					<div id="timediv4" hidden>
						Watering Interval [hours]:<br>
					<input type="text" id="time4" name="time4" value=""
						style="background-color: var(--inputbgcolor)"><br>
						Water Volume [ml]:<br>
					<input type="text" id="vol4" name="vol4" value=""
						style="background-color: var(--inputbgcolor)"><br>
					</div>
        <div id="moistdiv4" hidden>
          <label for="hume4">Soil moisture threshold:</label><br>
          <input type="range" id="hume4" name="hume4" list="values" />
          <datalist id="values">
            <option value="0" label="dry"></option>
						<option value="25"></option>
            <option value="50" label="mid"></option>
						<option value="75"></option>
            <option value="100" label="wet"></option>
          </datalist><br><br>
					Current Moisture: <b><span id="ADCValue4">0</span> </b>%<br><br>
        </div>
				<center><input type="submit" class="button" value="Save"></center>
			</form>
		</div>

		<div class="card" id="card5" hidden>
			<center>
				<h3>Channel 5</h3>
			</center>
			<form action="/ch5" target="_blank">
				<b>Mode:</b> <span id="state5"></span><br><br>
				Plant Name:<br>
				<input type="text" id="Name5" name="Name5" value=""
					style="background-color: var(--inputbgcolor)"><br><br>
					<div id="timediv5" hidden>
						Watering Interval [hours]:<br>
					<input type="text" id="time5" name="time5" value=""
						style="background-color: var(--inputbgcolor)"><br>
						Water Volume [ml]:<br>
					<input type="text" id="vol5" name="vol5" value=""
						style="background-color: var(--inputbgcolor)"><br>
					</div>
        <div id="moistdiv5" hidden>
          <label for="hume5">Soil moisture threshold:</label><br>
          <input type="range" id="hume5" name="hume5" list="values" />
          <datalist id="values">
            <option value="0" label="dry"></option>
						<option value="25"></option>
            <option value="50" label="mid"></option>
						<option value="75"></option>
            <option value="100" label="wet"></option>
          </datalist><br><br>
					Current Moisture: <b><span id="ADCValue5">0</span> </b>%<br><br>
        </div>
				<center><input type="submit" class="button" value="Save"></center>
			</form>
		</div>

		<div class="card" id="card6" hidden>
			<center>
				<h3>Channel 6</h3>
			</center>
			<form action="/ch6" target="_blank">
				<b>Mode:</b> <span id="state6"></span><br><br>
				Plant Name:<br>
				<input type="text" id="Name6" name="Name6" value=""
					style="background-color: var(--inputbgcolor)"><br><br>
					<div id="timediv6" hidden>
						Watering Interval [hours]:<br>
					<input type="text" id="time6" name="time6" value=""
						style="background-color: var(--inputbgcolor)"><br>
						Water Volume [ml]:<br>
					<input type="text" id="vol6" name="vol6" value=""
						style="background-color: var(--inputbgcolor)"><br>
					</div>
        <div id="moistdiv6" hidden>
          <label for="hume6">Soil moisture threshold:</label><br>
          <input type="range" id="hume6" name="hume6" list="values" />
          <datalist id="values">
            <option value="0" label="dry"></option>
						<option value="25"></option>
            <option value="50" label="mid"></option>
						<option value="75"></option>
            <option value="100" label="wet"></option>
          </datalist><br><br>
					Current Moisture: <b><span id="ADCValue6">0</span> </b>%<br><br>
        </div>
				<center><input type="submit" class="button" value="Save"></center>
			</form>
		</div>

		<div class="card" id="card7" hidden>
			<center>
				<h3>Channel 7</h3>
			</center>
			<form action="/ch7" target="_blank">
				<b>Mode:</b> <span id="state7"></span><br><br>
				Plant Name:<br>
				<input type="text" id="Name7" name="Name7" value=""
					style="background-color: var(--inputbgcolor)"><br><br>
					<div id="timediv7" hidden>
						Watering Interval [hours]:<br>
					<input type="text" id="time7" name="time7" value=""
						style="background-color: var(--inputbgcolor)"><br>
						Water Volume [ml]:<br>
					<input type="text" id="vol7" name="vol7" value=""
						style="background-color: var(--inputbgcolor)"><br>
					</div>
        <div id="moistdiv7" hidden>
          <label for="hume7">Soil moisture threshold:</label><br>
          <input type="range" id="hume7" name="hume7" list="values" />
          <datalist id="values">
            <option value="0" label="dry"></option>
						<option value="25"></option>
            <option value="50" label="mid"></option>
						<option value="75"></option>
            <option value="100" label="wet"></option>
          </datalist><br><br>
					Current Moisture: <b><span id="ADCValue7">0</span> </b>%<br><br>
        </div>
				<center><input type="submit" class="button" value="Save"></center>
			</form>
		</div>

		<div class="card" id="card8" hidden>
			<center>
				<h3>Channel 8</h3>
			</center>
			<form action="/ch8" target="_blank">
				<b>Mode:</b> <span id="state8"></span><br><br>
				Plant Name:<br>
				<input type="text" id="Name8" name="Name8" value=""
					style="background-color: var(--inputbgcolor)"><br><br>
					<div id="timediv8" hidden>
						Watering Interval [hours]:<br>
					<input type="text" id="time8" name="time8" value=""
						style="background-color: var(--inputbgcolor)"><br>
						Water Volume [ml]:<br>
					<input type="text" id="vol8" name="vol8" value=""
						style="background-color: var(--inputbgcolor)"><br>
					</div>
        <div id="moistdiv8" hidden>
          <label for="hume8">Soil moisture threshold:</label><br>
          <input type="range" id="hume8" name="hume8" list="values" />
          <datalist id="values">
            <option value="0" label="dry"></option>
						<option value="25"></option>
            <option value="50" label="mid"></option>
						<option value="75"></option>
            <option value="100" label="wet"></option>
          </datalist><br><br>
					Current Moisture: <b><span id="ADCValue8">0</span> </b>%<br><br>
        </div>
				<center><input type="submit" class="button" value="Save"></center>
			</form>
		</div>

		<div class="card" id="card9" hidden>
			<center>
				<h3>Channel 9</h3>
			</center>
			<form action="/ch9" target="_blank">
				<b>Mode:</b> <span id="state9"></span><br><br>
				Plant Name:<br>
				<input type="text" id="Name9" name="Name9" value=""
					style="background-color: var(--inputbgcolor)"><br><br>
					<div id="timediv9" hidden>
						Watering Interval [hours]:<br>
					<input type="text" id="time9" name="time9" value=""
						style="background-color: var(--inputbgcolor)"><br>
						Water Volume [ml]:<br>
					<input type="text" id="vol9" name="vol9" value=""
						style="background-color: var(--inputbgcolor)"><br>
					</div>
        <div id="moistdiv9" hidden>
          <label for="hume9">Soil moisture threshold:</label><br>
          <input type="range" id="hume9" name="hume9" list="values" />
          <datalist id="values">
            <option value="0" label="dry"></option>
						<option value="25"></option>
            <option value="50" label="mid"></option>
						<option value="75"></option>
            <option value="100" label="wet"></option>
          </datalist><br><br>
					Current Moisture: <b><span id="ADCValue9">0</span> </b>%<br><br>
        </div>
				<center><input type="submit" class="button" value="Save"></center>
			</form>
		</div>

		<div class="card" id="card10" hidden>
			<center>
				<h3>Channel 10</h3>
			</center>
			<form action="/ch10" target="_blank">
				<b>Mode:</b> <span id="state10"></span><br><br>
				Plant Name:<br>
				<input type="text" id="Name10" name="Name10" value=""
					style="background-color: var(--inputbgcolor)"><br><br>
					<div id="timediv10" hidden>
						Watering Interval [hours]:<br>
					<input type="text" id="time10" name="time10" value=""
						style="background-color: var(--inputbgcolor)"><br>
						Water Volume [ml]:<br>
					<input type="text" id="vol10" name="vol10" value=""
						style="background-color: var(--inputbgcolor)"><br>
					</div>
        <div id="moistdiv10" hidden>
          <label for="hume10">Soil moisture threshold:</label><br>
          <input type="range" id="hume10" name="hume10" list="values" />
          <datalist id="values">
            <option value="0" label="dry"></option>
						<option value="25"></option>
            <option value="50" label="mid"></option>
						<option value="75"></option>
            <option value="100" label="wet"></option>
          </datalist><br><br>
					Current Moisture: <b><span id="ADCValue10">0</span> </b>%<br><br>
        </div>
				<center><input type="submit" class="button" value="Save"></center>
			</form>
		</div>

		<div class="card" id="card11" hidden>
			<center>
				<h3>Channel 11</h3>
			</center>
			<form action="/ch11" target="_blank">
				<b>Mode:</b> <span id="state11"></span><br><br>
				Plant Name:<br>
				<input type="text" id="Name11" name="Name11" value=""
					style="background-color: var(--inputbgcolor)"><br><br>
					<div id="timediv11" hidden>
						Watering Interval [hours]:<br>
					<input type="text" id="time11" name="time11" value=""
						style="background-color: var(--inputbgcolor)"><br>
						Water Volume [ml]:<br>
					<input type="text" id="vol11" name="vol11" value=""
						style="background-color: var(--inputbgcolor)"><br>
					</div>
        <div id="moistdiv11" hidden>
          <label for="hume11">Soil moisture threshold:</label><br>
          <input type="range" id="hume11" name="hume11" list="values" />
          <datalist id="values">
            <option value="0" label="dry"></option>
						<option value="25"></option>
            <option value="50" label="mid"></option>
						<option value="75"></option>
            <option value="100" label="wet"></option>
          </datalist><br><br>
					Current Moisture: <b><span id="ADCValue11">0</span> </b>%<br><br>
        </div>
				<center><input type="submit" class="button" value="Save"></center>
			</form>
		</div>

		<div class="card" id="card12" hidden>
			<center>
				<h3>Channel 12</h3>
			</center>
			<form action="/ch12" target="_blank">
				<b>Mode:</b> <span id="state12"></span><br><br>
				Plant Name:<br>
				<input type="text" id="Name12" name="Name12" value=""
					style="background-color: var(--inputbgcolor)"><br><br>
					<div id="timediv12" hidden>
						Watering Interval [hours]:<br>
					<input type="text" id="time12" name="time12" value=""
						style="background-color: var(--inputbgcolor)"><br>
						Water Volume [ml]:<br>
					<input type="text" id="vol12" name="vol12" value=""
						style="background-color: var(--inputbgcolor)"><br>
					</div>
        <div id="moistdiv12" hidden>
          <label for="hume12">Soil moisture threshold:</label><br>
          <input type="range" id="hume12" name="hume12" list="values" />
          <datalist id="values">
            <option value="0" label="dry"></option>
						<option value="25"></option>
            <option value="50" label="mid"></option>
						<option value="75"></option>
            <option value="100" label="wet"></option>
          </datalist><br><br>
					Current Moisture: <b><span id="ADCValue12">0</span> </b>%<br><br>
        </div>
				<center><input type="submit" class="button" value="Save"></center>
			</form>
		</div>
		

	</main>

	<script>
		setInterval(function () {
			// Call a function repetatively with 2 Second interval
			getCyclic();
		}, 10000); //2000mSeconds update rate

		//Call function on Page Load
		document.addEventListener("DOMContentLoaded", function () {
			var xhttp = new XMLHttpRequest();
			xhttp.open("GET", "initial", true);

			xhttp.onload = function () {
				if (this.status === 200) {
					var data = JSON.parse(xhttp.responseText);
					document.getElementById("Name1").value = data.Name1;
					document.getElementById("Name2").value = data.Name2;
					document.getElementById("Name3").value = data.Name3;
					document.getElementById("Name4").value = data.Name4;
					document.getElementById("Name5").value = data.Name5;
					document.getElementById("Name6").value = data.Name6;
					document.getElementById("Name7").value = data.Name7;
					document.getElementById("Name8").value = data.Name8;
					document.getElementById("Name9").value = data.Name9;
					document.getElementById("Name10").value = data.Name10;
					document.getElementById("Name11").value = data.Name11;
					document.getElementById("Name12").value = data.Name12;


          switch (data.mode1) 
					{
            case 0:
              document.getElementById("state1").innerText = "Disabled";
							document.getElementById("card1").hidden = true;
              break;
            case 1:
              document.getElementById("state1").innerText = "Moisture";
              document.getElementById("moistdiv1").hidden = false;
					    document.getElementById("hume1").value = data.hume1;
							document.getElementById("card1").hidden = false;
              break;
            case 2:
              document.getElementById("state1").innerText = "Time";
              document.getElementById("timediv1").hidden = false;
              document.getElementById("time1").value = data.time1;
              document.getElementById("vol1").value = data.vol1;
							document.getElementById("card1").hidden = false;
              break;
          }

					switch (data.mode2) 
					{
            case 0:
              document.getElementById("state2").innerText = "Disabled";
							document.getElementById("card2").hidden = true;
              break;
            case 1:
              document.getElementById("state2").innerText = "Moisture";
              document.getElementById("moistdiv2").hidden = false;
					    document.getElementById("hume2").value = data.hume2;
							document.getElementById("card2").hidden = false;
              break;
            case 2:
              document.getElementById("state2").innerText = "Time";
              document.getElementById("timediv2").hidden = false;
              document.getElementById("time2").value = data.time2;
              document.getElementById("vol2").value = data.vol2;
							document.getElementById("card2").hidden = false;
              break;
          }

					switch (data.mode3) 
					{
            case 0:
              document.getElementById("state3").innerText = "Disabled";
							document.getElementById("card3").hidden = true;
              break;
            case 1:
              document.getElementById("state3").innerText = "Moisture";
              document.getElementById("moistdiv3").hidden = false;
					    document.getElementById("hume3").value = data.hume3;
							document.getElementById("card3").hidden = false;
              break;
            case 2:
              document.getElementById("state3").innerText = "Time";
              document.getElementById("timediv3").hidden = false;
              document.getElementById("time3").value = data.time3;
              document.getElementById("vol3").value = data.vol3;
							document.getElementById("card3").hidden = false;
              break;
          }

					switch (data.mode4) 
					{
            case 0:
              document.getElementById("state4").innerText = "Disabled";
							document.getElementById("card4").hidden = true;
              break;
            case 1:
              document.getElementById("state4").innerText = "Moisture";
              document.getElementById("moistdiv4").hidden = false;
					    document.getElementById("hume4").value = data.hume4;
							document.getElementById("card4").hidden = false;
              break;
            case 2:
              document.getElementById("state4").innerText = "Time";
              document.getElementById("timediv4").hidden = false;
              document.getElementById("time4").value = data.time4;
              document.getElementById("vol4").value = data.vol4;
							document.getElementById("card4").hidden = false;
              break;
          }

					switch (data.mode5) 
					{
            case 0:
              document.getElementById("state5").innerText = "Disabled";
							document.getElementById("card5").hidden = true;
              break;
            case 1:
              document.getElementById("state5").innerText = "Moisture";
              document.getElementById("moistdiv5").hidden = false;
					    document.getElementById("hume5").value = data.hume5;
							document.getElementById("card5").hidden = false;
              break;
            case 2:
              document.getElementById("state5").innerText = "Time";
              document.getElementById("timediv5").hidden = false;
              document.getElementById("time5").value = data.time5;
              document.getElementById("vol5").value = data.vol5;
							document.getElementById("card5").hidden = false;
              break;
          }

					switch (data.mode6) 
					{
            case 0:
              document.getElementById("state6").innerText = "Disabled";
							document.getElementById("card6").hidden = true;
              break;
            case 1:
              document.getElementById("state6").innerText = "Moisture";
              document.getElementById("moistdiv6").hidden = false;
					    document.getElementById("hume6").value = data.hume6;
							document.getElementById("card6").hidden = false;
              break;
            case 2:
              document.getElementById("state6").innerText = "Time";
              document.getElementById("timediv6").hidden = false;
              document.getElementById("time6").value = data.time6;
              document.getElementById("vol6").value = data.vol6;
							document.getElementById("card6").hidden = false;
              break;
          }

					switch (data.mode7) 
					{
            case 0:
              document.getElementById("state7").innerText = "Disabled";
							document.getElementById("card7").hidden = true;
              break;
            case 1:
              document.getElementById("state7").innerText = "Moisture";
              document.getElementById("moistdiv7").hidden = false;
					    document.getElementById("hume7").value = data.hume7;
							document.getElementById("card7").hidden = false;
              break;
            case 2:
              document.getElementById("state7").innerText = "Time";
              document.getElementById("timediv7").hidden = false;
              document.getElementById("time7").value = data.time7;
              document.getElementById("vol7").value = data.vol7;
							document.getElementById("card7").hidden = false;
              break;
          }

					switch (data.mode8) 
					{
            case 0:
              document.getElementById("state8").innerText = "Disabled";
							document.getElementById("card8").hidden = true;
              break;
            case 1:
              document.getElementById("state8").innerText = "Moisture";
              document.getElementById("moistdiv8").hidden = false;
					    document.getElementById("hume8").value = data.hume8;
							document.getElementById("card8").hidden = false;
              break;
            case 2:
              document.getElementById("state8").innerText = "Time";
              document.getElementById("timediv8").hidden = false;
              document.getElementById("time8").value = data.time8;
              document.getElementById("vol8").value = data.vol8;
							document.getElementById("card8").hidden = false;
              break;
          }

					switch (data.mode9) 
					{
            case 0:
              document.getElementById("state9").innerText = "Disabled";
							document.getElementById("card9").hidden = true;
              break;
            case 1:
              document.getElementById("state9").innerText = "Moisture";
              document.getElementById("moistdiv9").hidden = false;
					    document.getElementById("hume9").value = data.hume9;
							document.getElementById("card9").hidden = false;
              break;
            case 2:
              document.getElementById("state9").innerText = "Time";
              document.getElementById("timediv9").hidden = false;
              document.getElementById("time9").value = data.time9;
              document.getElementById("vol9").value = data.vol9;
							document.getElementById("card9").hidden = false;
              break;
          }

					switch (data.mode10) 
					{
            case 0:
              document.getElementById("state10").innerText = "Disabled";
							document.getElementById("card10").hidden = true;
              break;
            case 1:
              document.getElementById("state10").innerText = "Moisture";
              document.getElementById("moistdiv10").hidden = false;
					    document.getElementById("hume10").value = data.hume10;
							document.getElementById("card10").hidden = false;
              break;
            case 2:
              document.getElementById("state10").innerText = "Time";
              document.getElementById("timediv10").hidden = false;
              document.getElementById("time10").value = data.time10;
              document.getElementById("vol10").value = data.vol10;
							document.getElementById("card10").hidden = false;
              break;
          }

					switch (data.mode11) 
					{
            case 0:
              document.getElementById("state11").innerText = "Disabled";
							document.getElementById("card11").hidden = true;
              break;
            case 1:
              document.getElementById("state11").innerText = "Moisture";
              document.getElementById("moistdiv11").hidden = false;
					    document.getElementById("hume11").value = data.hume11;
							document.getElementById("card11").hidden = false;
              break;
            case 2:
              document.getElementById("state11").innerText = "Time";
              document.getElementById("timediv11").hidden = false;
              document.getElementById("time11").value = data.time11;
              document.getElementById("vol11").value = data.vol11;
							document.getElementById("card11").hidden = false;
              break;
          }

					switch (data.mode12) 
					{
            case 0:
              document.getElementById("state12").innerText = "Disabled";
							document.getElementById("card12").hidden = true;
              break;
            case 1:
              document.getElementById("state12").innerText = "Moisture";
              document.getElementById("moistdiv12").hidden = false;
					    document.getElementById("hume12").value = data.hume12;
							document.getElementById("card12").hidden = false;
              break;
            case 2:
              document.getElementById("state12").innerText = "Time";
              document.getElementById("timediv12").hidden = false;
              document.getElementById("time12").value = data.time12;
              document.getElementById("vol12").value = data.vol12;
							document.getElementById("card12").hidden = false;
              break;
          }
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
					document.getElementById("ADCValue5").innerText = data.ADCValue5;
					document.getElementById("ADCValue6").innerText = data.ADCValue6;
					document.getElementById("ADCValue7").innerText = data.ADCValue7;
					document.getElementById("ADCValue8").innerText = data.ADCValue8;
					document.getElementById("ADCValue9").innerText = data.ADCValue9;
					document.getElementById("ADCValue10").innerText = data.ADCValue10;
					document.getElementById("ADCValue11").innerText = data.ADCValue11;
					document.getElementById("ADCValue12").innerText = data.ADCValue12;
          
				}
			};
			xhttp.send();
		}
	</script>
</body>

</html>)=====";

const char CONFIG_page[] = R"=====(
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
		<form action="modes" target="_blank">
			<h3 style="margin: 0">
				<center>Control Mode Selection</center>
			</h3><br>
			<center>Channels</center>
			<table style="width: 100%; text-align: left" rules="all">
				<thead>
					<tr>
						<th>Op-Mode</th>
						<th>1</th>
						<th>2</th>
						<th>3</th>
						<th>4</th>
						<th>5</th>
						<th>6</th>
						<th>7</th>
						<th>8</th>
						<th>9</th>
						<th>10</th>
						<th>11</th>
						<th>12</th>
					</tr>
				</thead>
				<tbody>
					<tr>
						<td>Disabled</td>
						<td><input type="radio" id="ch1_disable" , name="ch1_mode" value="0"></td>
						<td><input type="radio" id="ch2_disable" , name="ch2_mode" value="0"></td>
						<td><input type="radio" id="ch3_disable" , name="ch3_mode" value="0"></td>
						<td><input type="radio" id="ch4_disable" , name="ch4_mode" value="0"></td>
						<td><input type="radio" id="ch5_disable" , name="ch5_mode" value="0"></td>
						<td><input type="radio" id="ch6_disable" , name="ch6_mode" value="0"></td>
						<td><input type="radio" id="ch7_disable" , name="ch7_mode" value="0"></td>
						<td><input type="radio" id="ch8_disable" , name="ch8_mode" value="0"></td>
						<td><input type="radio" id="ch9_disable" , name="ch9_mode" value="0"></td>
						<td><input type="radio" id="ch10_disable" , name="ch10_mode" value="0"></td>
						<td><input type="radio" id="ch11_disable" , name="ch11_mode" value="0"></td>
						<td><input type="radio" id="ch12_disable" , name="ch12_mode" value="0"></td>
					</tr>
					<tr>
						<td>Time</td>
						<td><input type="radio" id="ch1_time" , name="ch1_mode" value="1"></td>
						<td><input type="radio" id="ch2_time" , name="ch2_mode" value="1"></td>
						<td><input type="radio" id="ch3_time" , name="ch3_mode" value="1"></td>
						<td><input type="radio" id="ch4_time" , name="ch4_mode" value="1"></td>
						<td><input type="radio" id="ch5_time" , name="ch5_mode" value="1"></td>
						<td><input type="radio" id="ch6_time" , name="ch6_mode" value="1"></td>
						<td><input type="radio" id="ch7_time" , name="ch7_mode" value="1"></td>
						<td><input type="radio" id="ch8_time" , name="ch8_mode" value="1"></td>
						<td><input type="radio" id="ch9_time" , name="ch9_mode" value="1"></td>
						<td><input type="radio" id="ch10_time" , name="ch10_mode" value="1"></td>
						<td><input type="radio" id="ch11_time" , name="ch11_mode" value="1"></td>
						<td><input type="radio" id="ch12_time" , name="ch12_mode" value="1"></td>
					</tr>
					<tr>
						<td>Moisture</td>
						<td><input type="radio" id="ch1_moist" , name="ch1_mode" value="2"></td>
						<td><input type="radio" id="ch2_moist" , name="ch2_mode" value="2"></td>
						<td><input type="radio" id="ch3_moist" , name="ch3_mode" value="2"></td>
						<td><input type="radio" id="ch4_moist" , name="ch4_mode" value="2"></td>
						<td><input type="radio" id="ch5_moist" , name="ch5_mode" value="2"></td>
						<td><input type="radio" id="ch6_moist" , name="ch6_mode" value="2"></td>
						<td><input type="radio" id="ch7_moist" , name="ch7_mode" value="2"></td>
						<td><input type="radio" id="ch8_moist" , name="ch8_mode" value="2"></td>
						<td><input type="radio" id="ch9_moist" , name="ch9_mode" value="2"></td>
						<td><input type="radio" id="ch10_moist" , name="ch10_mode" value="2"></td>
						<td><input type="radio" id="ch11_moist" , name="ch11_mode" value="2"></td>
						<td><input type="radio" id="ch12_moist" , name="ch12_mode" value="2"></td>
					</tr>
				</tbody>
				</table>
			<center><input type="submit" class="button" value="Save"></center>
		</form>
	</div>

	<div class="card">
		<center><h3>System Config</h3></center>
		<form action="sysconf" target="_blank">
			<table>
				<tr>
					<td>Pump 1 rate [ml/min]: </td>
					<td><input type="number" id="pumprate1" name="pumprate1" style="background-color: var(--inputbgcolor); width: 50px;" value=""></td>
				</tr>
				<tr>
					<td>Pump 2 rate [ml/min]: </td>
					<td><input type="number" id="pumprate2" name="pumprate2" style="background-color: var(--inputbgcolor); width: 50px;" value=""></td>
				</tr>
				<tr><td><br></td>
				</tr>
				<tr>
					<td>Log Level  (SD Only)</td>
					<td>
						<input type="radio" id="loglevel0" , name="loglevel" value="0" checked="checked">
						<label for="loglevel0">None</label> 
					</td><td>
						<input type="radio" id="loglevel1" , name="loglevel" value="1">
						<label for="loglevel1">Events</label> 
					</td><td>
						<input type="radio" id="loglevel2" , name="loglevel" value="2">
						<label for="loglevel2">All</label> 
					</td>
				<tr>
					<td>Debug Level (USB)</td>
					<td>
						<input type="radio" id="debuglevel0" , name="debuglevel" value="0" checked="checked">
						<label for="debuglevel0">None</label> 
										</td><td>
						<input type="radio" id="debuglevel1" , name="debuglevel" value="1">
						<label for="debuglevel1">Actions</label> 
					</td><td>
						<input type="radio" id="debuglevel2" , name="debuglevel" value="2">
						<label for="debuglevel2">All</label> 
					</td>				</tr>
			</table>
			<center><input type="submit" class="button" value="Save"></center>
		</form>
		<hr style="border-color:var(--cardtextcolor);background-color:var(--cardtextcolor)">
		<center><h3>Sensor Calibration</h3></center>
		<p>For calibration please have the sensor of <b>Channel 1</b> as well as dry and wet medium at hand!</p>
		<center><input type="button" class="button" value="Calibrate"></center>
	</div>

	<div class="card">
		<center><h3>New WiFi Config</h3>
    </center>
		<h4>IMPORTANT: Wifi-Password needs at least 8 characters for AccessPoint!</h4>
    <form action="wifi_set" method="post" target="_blank">
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
            <input type="radio" id="wifimode1" , name="wifimode" value="1" checked="checked">
						<label for="wifimode1">Station Mode</label><br>
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
            <input type="radio" id="wifimode0" , name="wifimode" value="0">
						<label for="wifimode0">AccesPoint Mode</label><br>
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
		document.addEventListener("DOMContentLoaded", function () {
			var xhttp = new XMLHttpRequest();
			xhttp.open("GET", "conf", true);

			xhttp.onload = function () {
				if (this.status === 200) {
					var data = JSON.parse(xhttp.responseText);

					document.getElementById("system").innerText = data.system;
					document.getElementById("system").style.color = data.systemcolor;
					document.getElementById("pumprate1").value = data.pumprate1;
					document.getElementById("pumprate2").value = data.pumprate2;
					
					switch (data.debug) 
					{
						case 0:
							document.getElementById("debuglevel0").checked = true;
							break;
						case 1:
							document.getElementById("debuglevel1").checked = true;
							break;
						case 2:
							document.getElementById("debuglevel2").checked = true;
							break;
					}

					switch (data.log) 
					{
						case 0:
							document.getElementById("loglevel0").checked = true;
							break;
						case 1:
							document.getElementById("loglevel1").checked = true;
							break;
						case 2:
							document.getElementById("loglevel2").checked = true;
							break;
					}

					switch (data.mode1) 
					{
						case 0:
							document.getElementById("ch1_disable").checked = true;
							break;
						case 1:
							document.getElementById("ch1_moist").checked = true;
							break;
						case 2:
							document.getElementById("ch1_time").checked = true;
							break;
					}
					switch (data.mode2) 
					{
						case 0:
							document.getElementById("ch2_disable").checked = true;
							break;
						case 1:
							document.getElementById("ch2_moist").checked = true;
							break;
						case 2:
							document.getElementById("ch2_time").checked = true;
							break;
					}
					switch (data.mode3) 
					{
						case 0:
							document.getElementById("ch3_disable").checked = true;
							break;
						case 1:
							document.getElementById("ch3_moist").checked = true;
							break;
						case 2:
							document.getElementById("ch3_time").checked = true;
							break;
					}
					switch (data.mode4) 
					{
						case 0:
							document.getElementById("ch4_disable").checked = true;
							break;
						case 1:
							document.getElementById("ch4_moist").checked = true;
							break;
						case 2:
							document.getElementById("ch4_time").checked = true;
							break;
					}
					switch (data.mode5) 
					{
						case 0:
							document.getElementById("ch5_disable").checked = true;
							break;
						case 1:
							document.getElementById("ch5_moist").checked = true;
							break;
						case 2:
							document.getElementById("ch5_time").checked = true;
							break;
					}
					switch (data.mode6) 
					{
						case 0:
							document.getElementById("ch6_disable").checked = true;
							break;
						case 1:
							document.getElementById("ch6_moist").checked = true;
							break;
						case 2:
							document.getElementById("ch6_time").checked = true;
							break;
					}
					switch (data.mode7) 
					{
						case 0:
							document.getElementById("ch7_disable").checked = true;
							break;
						case 1:
							document.getElementById("ch7_moist").checked = true;
							break;
						case 2:
							document.getElementById("ch7_time").checked = true;
							break;
					}
					switch (data.mode8) 
					{
						case 0:
							document.getElementById("ch8_disable").checked = true;
							break;
						case 1:
							document.getElementById("ch8_moist").checked = true;
							break;
						case 2:
							document.getElementById("ch8_time").checked = true;
							break;
					}
					switch (data.mode9) 
					{
						case 0:
							document.getElementById("ch9_disable").checked = true;
							break;
						case 1:
							document.getElementById("ch9_moist").checked = true;
							break;
						case 2:
							document.getElementById("ch9_time").checked = true;
							break;
					}
					switch (data.mode10) 
					{
						case 0:
							document.getElementById("ch10_disable").checked = true;
							break;
						case 1:
							document.getElementById("ch10_moist").checked = true;
							break;
						case 2:
							document.getElementById("ch10_time").checked = true;
							break;
					}
					switch (data.mode11) 
					{
						case 0:
							document.getElementById("ch11_disable").checked = true;
							break;
						case 1:
							document.getElementById("ch11_moist").checked = true;
							break;
						case 2:
							document.getElementById("ch11_time").checked = true;
							break;
					}
					switch (data.mode12) 
					{
						case 0:
							document.getElementById("ch12_disable").checked = true;
							break;
						case 1:
							document.getElementById("ch12_moist").checked = true;
							break;
						case 2:
							document.getElementById("ch12_time").checked = true;
							break;
					}

				}
			};

			xhttp.send();
		});
	
		document.getElementById("calibrate").onclick = function () {
			var xhttp = new XMLHttpRequest();
			while(!confirm("Please put the sensor of Channel 1 in dry medium!"));
			xhttp.open("POST", "caldry", true);
			xhttp.send();
			sleep(2);
			while(!confirm("Please put the sensor of Channel 1 in wet medium!"));
			xhttp.open("POST", "calwet", true);
			xhttp.send();
			sleep(2);
			confirm("Calibration done!");
		}
	</script>
</body>
</html>)=====";

const char ABOUT_page[] = R"=====(
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
		<p>Plantomation is a plant watering system designed by Synthron (me) with great help from the "Freie Maker" community on Discord.</p>
    <hr>
    <p>The idea came to be from a friend of mine who wanted to build a "smart flower pot". Initially I was supposed to make the hardware while he does the software, but pretty quickly he opted out for personal reasons.</p>
    <p>After a while I reanimated the project, updated the schematic and made a PCB for it. The Design choice for 4 channels was more of a coincidence and pin-constraint than educated thought.</p>
    <p>After sharing the project on the Discord community "Freie Maker", a few keen people jumped right aboard with me and helped me develop the code, made suggestions for features and especially helped me with the front-end. So thank you all for that!</p>
    <p>All code, documentations and designs can be found at:</p>
    <a href="https://www.github.com/Synthron/Plantomation" style="margin-left: 20px;">GitHub</a>
	</div>
</body>
</html>)=====";