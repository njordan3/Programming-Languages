<?php
  // scriptname: combined.php
  // demonstrate how to post to the same file 
  // if you find this confusing - use the two file version

if (! empty($_POST))
{
  $formOK = true;
  $name = $_POST['name'];
  $room = $_POST['room'];
  $message = $_POST['message'];

  if ( empty($name) || empty($room) ) {
     $formOK = false; 
     echo "<font color=red>You forgot something.</font><br>";
  }
  if ($formOK) {
     echo "<b>Menu ordered by</b>: $name<br>";
     echo "<b>Deliver to Room:</b>: $room<br>";
     echo "<b>Special instructions</b>: $message <br>";
  } 
}
?>

<html>
<head>
<title> a simple form </title>

<style type="text/css">

  label, textarea, select
  {
     display: block; width: 180px; float: left; margin-bottom: 10px;
  }
  label 
  { 
     text-align: right; width: 95px; padding-right: 20px; font-weight:bold;          font-size:83%;
  }
  br 
  {
     clear: left;
  }
  #subbut 
  {
     width:100px; margin-top:10px; border:thin solid black; position:relative; 
     left:115px; font-size:70%;
  }
  .req 
  {
    color:#a00;
  }
  #note 
  {
     width:180px; color:#a00; margin-left:115px; font-size:83%;
  }
</style>
</head>


<body>
<h1>Breakfast Menu</h1>

<FORM method="post" action="combined.php">
<div>

<label for="name"><span class="req">*</span> 

Name:</label> <INPUT type="text" name="name" id="name"><br/>

<label for="room"><span class="req">*</span> 

Room No:</label> <INPUT type="text" name="room" id="room"><br/>

<div id="note">*Required entries</div>

<p>
<label for="entree"> Pick an entree:</label>

Omelette      <INPUT type="radio" name="entree" value="Omlette"> 
Eggs Benedict <INPUT type="radio" name="entree" value="Eggs Benedict"> 
Pancakes      <INPUT type="radio" name="entree" value="Pancakes"> 
Oatmeal       <INPUT type="radio" name="entree" value="Oatmeal">
</p>
<p>
<label for="message"> Special Instructions:</label>
<TEXTAREA name="message" id="message" rows="5" cols="35">
</textarea>
</p>

</div>

<br/>
<p>
<input id="subbut" type="submit" value="Submit FORM">
<INPUT ID="subbut" TYPE="reset" VALUE="Clear FORM">
</p>

</form>
</body>
</html>
