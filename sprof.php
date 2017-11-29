<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('sprof')) {
	dl('sprof.' . PHP_SHLIB_SUFFIX);
}
$module = 'sprof';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";
$function = 'confirm_' . $module . '_compiled';
if (extension_loaded($module)) {
	$str = $function($module);
} else {
	$str = "Module $module is not compiled into PHP";
}
echo "$str\n";

function busy() {
	for ($i = 0; $i < 1E7; $i++) {
		sin(mt_rand() / mt_getrandmax());
	}
}

$t = microtime(true);
sprof_start();
busy();
echo "signals received: ", sprof_stop(), "\n";
echo microtime(true) - $t, "\n";
?>
