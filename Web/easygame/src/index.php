<?php
error_reporting(0);
include "ffffffflll1111lag.php";

function GetIP(){
if(!empty($_SERVER["HTTP_CLIENT_IP"]))
    $ip = $_SERVER["HTTP_CLIENT_IP"];
else if(!empty($_SERVER["HTTP_X_FORWARDED_FOR"]))
    $ip = $_SERVER["HTTP_X_FORWARDED_FOR"];
else if(!empty($_SERVER["REMOTE_ADDR"]))
    $ip = $_SERVER["REMOTE_ADDR"];
else
    $ip = "0.0.0.0";
return $ip;
}

if($_GET['Xp0int'] !== 'JNU'){
	die("GET me Xp0int with values:JNU");
}

if($_POST['Xp0int'] !== 'JNUJNU'){
	die("Then post me Xp0int with values:JNUJNU");
}

$GetIPs = GetIP();
if ($GetIPs !== "127.0.0.1" ){
	die("You are not admin!");
}else{
	show_flag();
}