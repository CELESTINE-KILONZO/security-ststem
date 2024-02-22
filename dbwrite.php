<?php

require 'conn.php';
 // Keep this API Key value to be compatible with the ESP32 code provided in the project page. 
// If you change this value, the ESP32 sketch needs to match
$api_key_value = "tPmAT5Ab3j7F9";

$api_key= $sensor = $PM1_0_S1 = $PM2_5_S1 =  $PM10_S1 = $Latitude_S1 = $Longitude_S1 = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
       /* $PM1_0_S1 = test_input($_POST["PM1_0_S1"]);
        $PM2_5_S1 = test_input($_POST["PM2_5_S1"]);*/
        $PM10_S1 = test_input($_POST["signal_strength_S1"]);
        $Latitude_S1 = test_input($_POST["Latitude_S1"]);
        $Longitude_S1 = test_input($_POST["Longitude_S1"]);
        
        // Create connection
        $conn = new mysqli($host, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        $sql1 = "INSERT INTO SensorData_1 (PM1_0_S1, PM2_5_S1, PM10_S1, Latitude_S1, Longitude_S1)
        VALUES ('" . $PM1_0_S1 . "', '" . $PM2_5_S1 . "', '" . $PM10_S1 . "', '" . $Latitude_S1 . "', '" . $Longitude_S1 . "')";
        
        if ($conn->query($sql1) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql1 . "<br>" . $conn->error;
        }

    
        $conn->close();
    }
    else {
        echo "Wrong API Key provided.";
    }

}
else {
    echo "No data posted with HTTP POST.";
}


$api_key= $sensor = $PM1_0_S2 = $PM2_5_S2 =  $PM10_S2 = $Latitude_S2 = $Longitude_S2 = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
        /*$PM1_0_S2 = test_input($_POST["PM1_0_S2"]);
        $PM2_5_S2 = test_input($_POST["PM2_5_S2"]);*/
        $PM10_S2 = test_input($_POST["signal_strength_S2"]);
        $Latitude_S2 = test_input($_POST["Latitude_S2"]);
        $Longitude_S2 = test_input($_POST["Longitude_S2"]);
        
        // Create connection
        $conn = new mysqli($host, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        $sql1 = "INSERT INTO SensorData_2 (PM1_0_S2, PM2_5_S2, PM10_S2, Latitude_S2, Longitude_S2)
        VALUES ('" . $PM1_0_S2 . "', '" . $PM2_5_S2 . "', '" . $PM10_S2 . "', '" . $Latitude_S2 . "', '" . $Longitude_S2 . "')";
        
        if ($conn->query($sql1) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql1 . "<br>" . $conn->error;
        }

    
        $conn->close();
    }
    else {
        echo "Wrong API Key provided.";
    }

}
else {
    echo "No data posted with HTTP POST.";
}

$api_key= $sensor = $PM1_0_S3 = $PM2_5_S3 =  $PM10_S3 = $Latitude_S3 = $Longitude_S3 = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
       /* $PM1_0_S3 = test_input($_POST["PM1_0_S3"]);
        $PM2_5_S3 = test_input($_POST["PM2_5_S3"]);*/
        $PM10_S3 = test_input($_POST["signal_strenth_S3"]);
        $Latitude_S3 = test_input($_POST["Latitude_S3"]);
        $Longitude_S3 = test_input($_POST["Longitude_S3"]);
        
        // Create connection
        $conn = new mysqli($host, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        $sql1 = "INSERT INTO SensorData_3 (PM1_0_S3, PM2_5_S3, PM10_S3, Latitude_S3, Longitude_S3)
        VALUES ('" . $PM1_0_S3 . "', '" . $PM2_5_S3 . "', '" . $PM10_S3 . "', '" . $Latitude_S3 . "', '" . $Longitude_S3 . "')";
        
        if ($conn->query($sql1) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql1 . "<br>" . $conn->error;
        }

    
        $conn->close();
    }
    else {
        echo "Wrong API Key provided.";
    }

}
else {
    echo "No data posted with HTTP POST.";
}


function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}
    // Close MySQL connection
    $conn->close();
?>


