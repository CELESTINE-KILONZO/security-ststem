<?php
// host = localhost because database hosted on the same server where PHP files are hosted
//everything prefixed with $ is a PHP variable
    $host = "localhost"; 
    $dbname = "hyperese_tracker";    // Database name
    $username = "hyperese";                    // Database username
    $password = "CP@%Eergy%%%%354@";                        // Database password
    $locations=array(); 

    // Establish connection to MySQL database, using the inbuilt MySQLi library.
    $conn = new mysqli($host, $username, $password, $dbname);
    // Check if connection established successfully
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    } else {
        //echo "SENSING_DEVICE_ONE_OUTPUTS ";
        }

        