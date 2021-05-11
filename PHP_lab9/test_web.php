<!--
  filename: test_web.php
  demonstrates PHP mixed with HTML and the use of different data types
  ref: http://us2.php.net/manual/en/language.types.php
  ref: http://us2.php.net/language.types.type-juggling
  ref: http://us3.php.net/manual/en/ref.array.php
-->

<HTML>
<BODY bgcolor="tan" text="navy">
<table border="1"><tr>
   <?php
      echo '<td>Hello</td><td>World</td>';
   ?>
</tr></table>


<?php

/* ---------------------------------------------- */
// Integer/Float
/* ---------------------------------------------- */
$num = 100; 
$pi = 3.14159265;

echo "<H3>PHP DATA TYPES</H3>";

// old c style
printf("%d, %f<br>", $num, $pi);
// or bash style
echo $num.', '.$pi.'<br>';
// or perl style
print "$num, $pi<br>";

echo "<br>"; // just for formating

/* ---------------------------------------------- */
echo "<h3>Strings</H3>";
/* ---------------------------------------------- */
$myString = "Hello Dorld";
echo $myString."<br>";

echo "Incorrect Letter: ".$myString{6}."<br>";
$myString{6} = 'W'; // set a char at a point
echo "Correct: ".$myString."<br>";

echo "<br>"; // just for formating

/* ---------------------------------------------- */
echo "<H3>Associative Arrays</H3>";
/* ---------------------------------------------- */
$myA = array( "apple" => "good", "banana" => "bad");
// add another to array
$myA["orange"] = "ok";       // set/add new element
$myA["carrot"] = "awesome";  // set/add new element
// woops carrot is not a fruit
unset( $myA["carrot"] ); // remove element from array

// use for each to get ALL elements in array
foreach($myA as $key => $value)
{
   printf("%s = %s<br>", $key, $value);
}

echo "Sorted by Key: ";
// sort keys
ksort($myA);
print_r($myA); // quick way to print out a class or array contents
echo "<br>"; // just for formating

echo "<br>"; // just for formating
$myA = array();  // reset array
array_push($myA, "joe"); 
array_push($myA, "bob");
array_push($myA, "billy");

// using typlical c style for loop
$size = count($myA); // save number of elements in the array
for($i = 0; $i < $size; $i++)
{
   printf("%d = %s<br>", $i, $myA[$i]);
}

echo "Sorted by Value: ";
// sort values
sort($myA);
print_r($myA); // quick way to print out a class or array contents

?>

</BODY>
</HTML>
