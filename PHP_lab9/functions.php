<?php
// filename: functions.php
// demonstrates PHP functions and classes

// all arrays (indexed or associative) are stored as associative arrays
$array1 = array("a"=>1, "b"=>2, "c"=>3, "d"=>4, "e"=>5);
$array2 = array(6, 7, 8, 9, 10, 11, 12);

print "index0: $array2[0]\n";

// -------------------------------------------- //
// Using Functions
function odd($var) {
   return($var % 2 == 1);
}

function even($var) {
   return($var % 2 == 0);
}

// array_filter() is a PHP function that passes each value in the array to a 
// user-defined boolean function and returns an array with the true values 
// in this example, "odd" is the name of the local boolean function
$a_filer1 = array_filter($array1, "odd");
$a_filer2 = array_filter($array2, "even");

echo "Func Odd: ";       
print_r($a_filer1);   // displays data structure in human readable form
echo "<br>\n";

echo "Func Even: ";
print_r($a_filer2);
echo "<br>\n";
// -------------------------------------------- //

echo "<br>\n";

// -------------------------------------------- //
// In a class
$myA = new myClass($array1, $array2);

class myClass {
   function myClass($a1, $a2) {
      // "odd" is the name of the class function only 
      // because it is in an array with the this object
      $a_filer1 = array_filter($a1, array(&$this, "odd") );
      $a_filer2 = array_filter($a2, array(&$this, "even") );
    
      echo "Class Odd: ";       
      print_r($a_filer1);
      echo "<br>\n";
      
      echo "Class Even: ";
      print_r($a_filer2);
      echo "<br>\n";
   }
   
   function odd($var) {
      return($var % 2 == 1);
   }
   
   function even($var) {
      return($var % 2 == 0);
   }
}
// -------------------------------------------- //
// demonstrate scope 

$num = 5;
function Test( $first, $second) {
   $num = 10;
   echo "Inside Test: $num <br>\n"; {
       $num = 15;
       echo "Inside Block: $num<br>\n";
   }
}

echo "Outside Test: $num<br> \n";
Test($num,"hello");
echo "calling even(hello)";
even("hello");

?>
