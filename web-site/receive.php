<?
/* Here the data received with GET requests are saved to  the database */
/* You can also save values at value1 and value2. At this example
 i just wanted to test the hardware so i used only value0 */

if (isset($_GET['value0'])){
	include 'connect.php';
	$query="insert into Measurements (value0) values ('".$_GET['value0']."')";
	if (mysql_query("$query")){
		echo "<center>Data Received</center>";
	}else{
		echo "<center>Error</center>";
	}

}else{
	echo "<center>No Data</center>";
}
