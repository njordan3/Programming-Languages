<?php

  // error_reporting(E_ALL);
  // ini_set('display_errors','1'); 
  //import form information
  echo "<pre>";
  print_r ($_POST);
  echo "</pre>";
  $name = $_POST['name'];
  $room = $_POST['room'];
  $message = $_POST['message'];
  $types=$_POST['types'];
  $entree=$_POST['entree'];
  $message=stripslashes($message);
  
  // simple form validation
  //if no name entered and no room entered print an error  
  if (empty($name) && empty($room)){
     print "You must include your name and room";
  } 
  //if no name entered send print an error  
  elseif (empty($name)){
     print "You must enter your name.<br>";
  } 
  //if no room entered send print an error  
  elseif (empty($room)){
     print "You must enter your room number. <br>";
  } 
  //if the form has both required fields print  
  else {
     // php uses dynamic duck typing
     $room = (int)$room;
     print "<b>Menu ordered by $name in room $room:</b><br>";

     // convert selection values into a string
     $ctypes = ""; 
     for ( $i=0; $i < count($types); $i++ ){
         $ctypes=  $ctypes . "\n$types[$i]";
     } 
 
     // print menu 
     print "<p><b>Special instructions</b>: <br>";
     print "$message<br></p><p><b>Selections:</b><br>$ctypes</p>";
     print "<p><b>Entree</b>: <br> $entree <br></p>"; 
  } 

?>
