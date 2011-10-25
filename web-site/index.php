<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<link href="stylesheets/style1.css" rel="stylesheet" type="text/css" charset="utf-8" />
	<title>Metriseis</title>
</head>

<body>
<div id="wrapper">
	<div id="header"></div>
    <div id="nav">
    	<a href="index.php">Home</a><a href="#">Settings</a>
    </div>
	<div id="Content">
		<div align="center">
			<form name="data_choose" method="get" action="index.php"/>
				<table>
					<th>Select data to view</th>
					<tr><td>Temperature</td><td><input type="checkbox" name="check_temp" id="check_temp"/></td></tr>
					<tr><td>Wind</td><td><input type="checkbox" name="check_wind" id="check_wind"/></td></tr>
					<tr><td>Humidity</td><td><input type="checkbox" name="check_hum" id="check_hum"/></td></tr>
				</table>
				<input type="submit" id="accept" name="accept" value="Next"/>
			</form>  
<?
	include 'connect.php';

	if (($_GET['check_temp']=='on') && !isset($_GET['check_wind']) && !isset($_GET['check_hum'])){

		echo "<center><table border=1>";
		echo "<tr><th>ID</th><th>Temperature</th><th>Date</th></tr>";

		$query="select id, value0, date from Measurements";
		$result=mysql_query($query);

		while ($row = mysql_fetch_array($result)){
			echo "<tr><td>";
			echo $row['id'];
			echo "</td><td>";
			echo $row['value0'];
			echo "</td><td>";
			echo $row['date'];
			echo "</td></tr>";
		}
		echo "</table></center>";
		
	}elseif (($_GET['check_wind']=='on') && !isset($_GET['check_temp']) && !isset($_GET['check_hum'])){

		echo "<center><table border=1>";
		echo "<tr><th>ID</th><th>Wind</th><th>Date</th></tr>";

		$query="select id, value1, date from Measurements";
		$result=mysql_query($query);

		while ($row = mysql_fetch_array($result)){
			echo "<tr><td>";
			echo $row['id'];
			echo "</td><td>";
			echo $row['value1'];
			echo "</td><td>";
			echo $row['date'];
			echo "</td></tr>";
		}
		echo "</table></center>";
		
	}elseif (($_GET['check_hum']=='on') && !isset($_GET['check_temp']) && !isset($_GET['check_wind'])){

		echo "<center><table border=1>";
		echo "<tr><th>ID</th><th>Humidity</th><th>Date</th></tr>";

		$query="select id, value2, date from Measurements";
		$result=mysql_query($query);

		while ($row = mysql_fetch_array($result)){
			echo "<tr><td>";
			echo $row['id'];
			echo "</td><td>";
			echo $row['value2'];
			echo "</td><td>";
			echo $row['date'];
			echo "</td></tr>";
		}
		echo "</table></center>";

	}elseif (($_GET['check_temp']=='on') && ($_GET['check_wind']=='on') && !isset($_GET['check_hum'])){
	
		echo "<center><table border=1>";
		echo "<tr><th>ID</th><th>Temperature</th><th>Wind</th><th>Date</th></tr>";
		
		$query="select id, value0, value1, date from Measurements";
		$result=mysql_query($query);

		while ($row = mysql_fetch_array($result)){
			echo "<tr><td>";
			echo $row['id'];
			echo "</td><td>";
			echo $row['value0'];
			echo "</td><td>";
			echo $row['value1'];
			echo "</td><td>";
			echo $row['date'];
			echo "</td></tr>";
		}		 
		echo "</table></center>";

	}elseif (($_GET['check_temp']=='on') && ($_GET['check_hum']=='on') && !isset($_GET['check_wind'])){
			
		echo "<center><table border=1>";
		echo "<tr><th>ID</th><th>Temperature</th><th>Humidity</th><th>Date</th></tr>";
		
		$query="select id, value0, value2, date from Measurements";
		$result=mysql_query($query);

		while ($row = mysql_fetch_array($result)){
			echo "<tr><td>";
			echo $row['id'];
			echo "</td><td>";
			echo $row['value0'];
			echo "</td><td>";
			echo $row['value2'];
			echo "</td><td>";
			echo $row['date'];
			echo "</td></tr>";
		}		 
		echo "</table></center>";

	}elseif (($_GET['check_wind']=='on') && ($_GET['check_hum']=='on') && !isset($_GET['check_temp'])){
	
		echo "<center><table border=1>";
		echo "<tr><th>ID</th><th>Wind</th><th>Humidity</th><th>Date</th></tr>";
		
		$query="select id, value1, value2, date from Measurements";
		$result=mysql_query($query);

		while ($row = mysql_fetch_array($result)){
			echo "<tr><td>";
			echo $row['id'];
			echo "</td><td>";
			echo $row['value1'];
			echo "</td><td>";
			echo $row['value2'];
			echo "</td><td>";
			echo $row['date'];
			echo "</td></tr>";
		}		 
		echo "</table></center>";
		 
	}elseif (($_GET['check_wind']=='on') && ($_GET['check_hum']=='on') && ($_GET['check_temp']=='on')){
	
		echo "<center><table border=1>";
		echo "<tr><th>ID</th><th>Temperature</th><th>Windυ</th><th>Humidity</th><th>Date</th></tr>";
		
		$query="select id, value0, value1, value2, date from Measurements";
		$result=mysql_query($query);
		
		while ($row = mysql_fetch_array($result)){
			echo "<tr><td>";
			echo $row['id'];
			echo "</td><td>";
			echo $row['value0'];
			echo "</td><td>";
			echo $row['value1'];
			echo "</td><td>";
			echo $row['value2'];
			echo "</td><td>";
			echo $row['date'];
			echo "</td></tr>";
		}		 
		echo "</table></center>";
	}
?>
		</div>
    </div>
	<div id="footer">
		<p align="center">Andrianakis Charalampos -  Tsompanakis Konstantinos</p>
    </div>
</div>
</body>
</html>
