<html>
<title>&lt;CS 350 &gt;</title>
<body>
<table border=1 cellpadding=2 cellspacing=0>
<tr>
   <td>Name:</td><td>&lt;samantha spade&gt;</td>
</tr><tr>
   <td>Date:</td><td>&lt;mar 2, 2006&gt;</td>
</tr><tr>
   <td>Course:</td><td>cs350: Programming Languages</td>
</tr><tr>
   <td>Content:</td><td>PHP Parser</td>
</tr>
</table>
<hr>
<pre>
<?php
   require('xml_reader_class.php'); // require both includes and evaluates file
   
   $xmlR = new myXMLReader();      // create a new myXMLReader() object 
   
   echo "Loading XML File...\n"; 
   $xmlR->Load('data.xml');         // -> dereferences xmlR ; calls Load
   
   echo "Parsing XML file...\n";
   $xmlR->ParseLoop();
   
   echo "List: \n";
   $xmlR->PrintList();
   
   echo "\nDone!\n";
?>
</pre>
<hr>
</body>
</html>
