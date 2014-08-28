<?php

	$contents = file_get_contents("www.cnblogs.com/~run/articles/2371078.html");
	perg_match_all("//", $contents, $arr);
	print_r($arr);
?>
