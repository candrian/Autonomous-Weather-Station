The data send with GET requests which is not the best and securest way but its an easy way to test and run your hardware to make a fast preview of it. This app is a very simple php-mysql web site for data storing received from GET requests.

To install the web site you need:
1)Web server (apache)
2)Mysql server
3)Php server

Installing:
1) Insert into connect.php file your mysql username and password.
2) Install the database from the measurements.sql (restore).
3) Upload all the files to a web server with the above requirements.

You can find all the appropriate files in the web-site folder. 

index.php is the main page where you can see the stored data.
receive.php is the page where you send the data to be stored.
connect.php is the file which has the login information to connect to the database.
measurements.sql is the database backup file.
images/ includes the site images
stylesheets/ includes the css code files.

Hardware used: PIC16F877A & SIM300/900 GSM Module
More info: http://www.candrian.gr