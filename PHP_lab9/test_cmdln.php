#!/usr/bin/php
<?php

// filename: test_cmdln.php  
// demonstrate basic PHP syntax through a command line script
// note: php was not designed to work from the command line


// argv is just like C's
var_dump( $argv );

// simple echo(print) to screen
echo "Hello World\n";
// print with escapes 
print "Hello \"New\" World\n<p>";

// all variables prefaced with $
// '$' does not imply a type - can be scalar, array, or hash
// PHP uses dynamic duck typing
$num = 100; 
$pi = 3.14159265;
$arr = array();
$arr[0] = 1;
// print C style printf
printf("Hello %s\n\n", 'World');

if ($num > 50) {
   // old c style
   printf("%d, %f\n", $num, $pi);
}
elseif ($pi < 5.0){
  // or bash style
  echo $num.', '.$pi."\n";
}
else {
   // or perl style
   print "$num, $pi\n";
}
$myString = "Hello Dorld";
echo $myString."\n";

echo "Incorrect Letter: ".$myString{6}."\n";
$myString{6} = 'W'; // set a char at a point
echo "Correct: ".$myString."\n";

// do some array manipulations

$myA = array( "apple" => "good", "banana" => "bad");
// add another to array
$myA["orange"] = "ok";       // set/add new element
$myA["carrot"] = "awesome";  // set/add new element
// whoops carrot is not a fruit
unset( $myA["carrot"] );     // remove element from array

// use for each to get ALL elements in array
foreach($myA as $key => $value)
{
   printf("%s = %s\n", $key, $value);
}

echo "Sorted by Key: ";
// sort keys
ksort($myA);
print_r($myA);   // quick way to print out a class or array contents
echo "\n\n";       // just for formating

$myA = array();  // reset to standard array type
array_push($myA, "joe"); 
array_push($myA, "bob");
array_push($myA, "billy");

// using typical C style for loop
$size = count($myA); // save number of elements in the array
for($i = 0; $i < $size; $i++)
{
   printf("%d = %s\n", $i, $myA[$i]);
}

echo "Sorted by Value: ";
// sort values
sort($myA);
print_r($myA); // quick way to print out a class or array contents


// demonstrate file IO
echo "Current Directory: ".getcwd()."\n";
$filename = "data.txt";

echo "Opening File ($filename)\n";
$fd = fopen($filename, "r");
if(!$fd) {
   echo 'Could not open file $filename\n';
   exit();
}

echo "\nRead in file data\n";
$char = fgetc($fd);
$str = $char;
while($char !== false)
{
   $char = fgetc($fd);
   $str .= $char;
}

// this reads 1024 bytes at a time into str
// $str = '';
// while(!feof($fd)) {
//     $str .= fread($fd, 1024);
// }

echo "Writing file data:\n";
echo $str."\n";

echo "Encrypted ROT13\n";
$str = str_rot13($str); // rotate chars pos by 13
echo "$str\n";
fclose($fd);

$filename = "donna.txt";
$fd = fopen($filename, "w");
if(!$fd) {
   echo 'Could not open file $filename for writing\n';
   exit();
}

// write to a file
if(fwrite($fd, $str) === false) {
    echo "Cannot write to file ($filename)\n";
    exit();
}

echo "Success, wrote ($str) to file ($filename)\n";
fclose($fd);

function odd($var)
{
   return($var % 2 == 1);
}

$result = odd("HI");
echo "ODD: $result\n";

// display php engine configuration
// phpinfo();

?>
