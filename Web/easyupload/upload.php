<?php
header("Content-Type: text/html;charset=utf-8");
    if(isset($_POST["submit"]))
    {
        
        if($_FILES['file']['type'] !== "image/jpeg" 
            && $_FILES['file']['type'] !== "image/png" 
            && $_FILES['file']['type'] !== "image/gif"){

            exit('文件上传类型错误');
        }
        
        
        if(!@getimagesize($_FILES['file']['tmp_name'])){
            exit("图片文件格式不对!");
        }

        $name = $_FILES['file']['name'];
        echo "文件上传成功！filename：".$name;
        echo "<br>";


        if($name !== 'give_me_flag.php'){
            exit("但要给我一个give_me_flag.php  我才给你flag!");
        }
        

        $content = file_get_contents($_FILES['file']['tmp_name']);
        if(!preg_match('/givemeflag/i', $content)){
            exit("文件里面要有'givemeflag'  我才给你flag!");
        }            
        echo "<br>".'flag{SHjdbe7pIUD02847SDHD}';
        exit();
    }
?>