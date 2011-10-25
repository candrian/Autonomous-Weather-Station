<?
/* Connect to database */
/* To connect change DBusername with database username
 and DBpassword with database password */

$connctuser="DBusername";
$connctpassword="DBpassword";
$connctdatabase="gsm";
$conncthost="localhost";

mysql_connect($conncthost,$connctuser,$connctpassword) or die ("Unable to connect to mysql");
@mysql_select_db($connctdatabase) or die ("Unable to select database");
mysql_query("SET NAMES latin1");
?>

