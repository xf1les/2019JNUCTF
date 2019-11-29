<?php

highlight_file('source.txt');
echo "<br><br>";

$flag = 'flag{GSH1ydsbnYtshkjhs}';
$msg_giveme = 'Give me the flag!';
$msg_getout = 'No this. Get out!';
if(!isset($_GET['flag']) && !isset($_POST['flag'])){
	exit($msg_giveme);
}

if($_POST['flag'] === 'flag' || $_GET['flag'] === 'flag'){
	exit($msg_getout);
}

foreach ($_POST as $key => $value) {
	$$key = $value;
}

foreach ($_GET as $key => $value) {
	$$key = $$value;
}

echo 'the flag is : ' . $flag;

