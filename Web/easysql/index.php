<?php
header("Content-Type: text/html;charset=utf-8");
highlight_file('sql.txt');
echo '<br><br>';

if(isset($_POST['id'])){

	waf($_POST['id']);

	$con = mysql_connect("localhost","root","rootpassword");
	if (!$con)
	  {
	  die('Could not connect: ' . mysql_error());
	  }

	mysql_select_db("ctf", $con);

	$result = mysql_query("SELECT * FROM users where id='" . $_POST['id'] ."'");

	$row = mysql_fetch_array($result);
	
	echo "用户名: " . $row['username'];
	echo "<br />";
	echo "密码: " . $row['password'];
	

	mysql_close($con);
}

function waf($str)
{
	$filter = ' |outfile|readfile|;|load_file|\"|sleep|delete|insert|update|database|user|information_schema';
	if(preg_match('/'. $filter .'/i', $str)){
		exit('hacker!');
	}
}

?>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
</head>
<h1>用户信息查询</h1>
<span>我才不会告诉你可以用select flag from flag看到flag呢！</span>
<form action="index.php" method="post">
  <p>id: <input type="text" name="id" /></p>
  <input type="submit" value="Submit" />
</form>
</html>
