<?php

require "class.php";

if (isset($_POST["submit"])) {
    $filename = $_POST["name"];

    if (stripos($filename, "phar://") === 0)
        die("unsupported stream wrapper: phar://");

    if (stripos($filename, "compress.bzip2://") === 0)
        die("unsupported stream wrapper: compress.bzip2://");

    if(is_dir($filename) or substr(strtoupper($filename), -4) != "JPEG")
        die($filename." is not a jpeg file");

    var_dump(getimagesize($filename));

}
?>
