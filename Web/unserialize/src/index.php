<?php
error_reporting(0);
include('flag.php');
if($_GET['source'] == 1){
	highlight_file("sssssource.txt");
}

class Getflag{
	protected $value=0;

	public function __destruct(){
		echo $this->value;
		if($this->value==1)
			show_flag();
		else
			die('nonono');
	}

}
$ans=$_GET['ans'];
$ans=str_replace('Getflag', '', $ans);
unserialize($ans);

if(isset($_GET['A']) && isset($_GET['B'])){
	$md51=md5($_GET['A']);
	$md52=md5($_GET['B']);
	if($md51 == $md52){
		show_source(__FILE__);
	}
}



?>













































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































<!-- ?source=1 -->