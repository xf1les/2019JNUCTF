<?php
header("Content-Type: text/html;charset=utf-8");
    if(isset($_POST["submit"]))
    {
    	if($_FILES['file']['type'] !== "image/jpeg" 
            && $_FILES['file']['type'] !== "image/png"
            && $_FILES['file']['type'] !== "image/gif" )
        {
            echo $_FILES['file']['type'];
            exit('文件上传类型错误');
    	}
        $name = $_FILES['file']['name'];
        echo "文件上传成功！filename：".$name;
        echo "<br>";
        if($name === 'give_me_flag.php'){
            echo "<br>".'flag{w311_D0ne!}';
            exit();
        }
        echo "但要给我一个give_me_flag.php  我才给你flag!";

        
        
    }
?>