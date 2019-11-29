<html>
<body>
<head>
<meta charset="UTF-8">
<title>登录</title>
</head>
<p>这里是管理员登录入口</p>
<form method="POST" action="">
    Username: <input type="text" name="username"> <br>
    Password: <input type="password" name="password"> <br>
    <button type="submit">Submit</button>
</form>
<!-- /source.txt -->
</body>
</html
<?php


$flag = "flag{G_du93ksy639_sjd}";
$secret = "sGucne9iD0"; // 10 characters long

if(!isset($_POST["username"]) || !isset($_POST["password"])){
	exit();
}
$username = $_POST["username"];
$password = $_POST["password"];
 
if (!empty($_COOKIE["check"])) {


    if (urldecode($username) === "admin" && urldecode($password) != "admin") {
        if ($_COOKIE["check"] === md5($secret . urldecode($username . $password))) {
            echo "Login successful.\n";
            die ("The flag is ". $flag);
        }
        else {
            die ("Wrong Cookies. Get out!");
        }
    }
    else {
        die ("Admins only");
    }
}
 
setcookie("ahash", md5($secret . urldecode("admin" . "admin")), time() + (60 * 60 * 24 * 7));


