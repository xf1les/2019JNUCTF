<?php
error_reporting(-1);
ini_set('display_errors', 'On');

if($_SERVER['REQUEST_METHOD'] != "POST"){
    echo "unsupported method";
    exit(0);
}

$target_dir = "uploads/";
$uploadOk = 1;

$imageFileType = substr($_FILES["fileToUpload"]["name"], strrpos($_FILES["fileToUpload"]["name"], '.') + 1, strlen($_FILES["fileToUpload"]["name"]));

if ($imageFileType != "jpeg") {
    echo "Sorry, only JPEG is allowed.<br>";
    $uploadOk = 0;
    exit(0);
}

$file_name = md5(time());
$file_name = substr($file_name, 0, 10) . '.jpeg';

$target_file = $target_dir . $file_name;

if (file_exists($target_file)) {
    echo "Sorry, file already exists.<br>";
    $uploadOk = 0;
}
if ($_FILES["fileToUpload"]["size"] > 500000) {
    echo "Sorry, your file is too large.<br>";
    $uploadOk = 0;
}

if ($uploadOk == 0) {
    echo "Sorry, your file was not uploaded.";
} else {
    if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
        echo "./uploads/".$file_name;
    } else {
        echo "Sorry, there was an error uploading your file.";
    }
}
?>
