<?php
$prize_arr = array(
	'0' => array('id'=>1,'min'=>151,'max'=>209,'prize'=>'一等奖','v'=>1,'flag'=>'flag{You_are_really_the_European_emperor!!!}'),
	'1' => array('id'=>2,'min'=>91,'max'=>149,'prize'=>'二等奖','v'=>9,'flag'=>'Wow! 很接近了，但是还是没有!'),
	'2' => array('id'=>3,'min'=>array(1,331),'max'=>array(29,359),'prize'=>'三等奖','v'=>50,'flag'=>'好不容易抽个三等奖，还是没有flag，嘿嘿!'),
	'3' => array('id'=>4,'min'=>271,'max'=>329,'prize'=>'四等奖','v'=>100,'flag'=>'你看看你，看看你，成天就想要flag!'),
	'4' => array('id'=>5,'min'=>array(31,211),'max'=>array(89,269),'prize'=>'谢谢参与','v'=>200,'flag'=>'奖都没拿到就想要flag?')
);

function getRand($proArr) {
	$result = '';

	//概率数组的总概率精度
	$proSum = array_sum($proArr);

	//概率数组循环
	foreach ($proArr as $key => $proCur) {
		$randNum = mt_rand(1, $proSum);
		if ($randNum <= $proCur) {
			$result = $key;
			break;
		} else {
			$proSum -= $proCur;
		}
	}
	unset ($proArr);

	return $result;
}

foreach ($prize_arr as $key => $val) {
	$arr[$val['id']] = $val['v'];
}

$rid = getRand($arr); //根据概率获取奖项id

$res = $prize_arr[$rid-1]; //中奖项
$min = $res['min'];
$max = $res['max'];
if($res['id']==3 || $res['id']==5){ //三等奖或没奖
	$i = mt_rand(0,1);
	$result['angle'] = mt_rand($min[$i],$max[$i]);
}else{
	$result['angle'] = mt_rand($min,$max); //随机生成一个角度
}
$result['prize'] = $res['prize'];
$result['flag'] = $res['flag'];


echo json_encode($result);