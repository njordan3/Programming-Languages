<?php
$myA = new A();   // instantiate object A
$myB = new B();   // instantiate object B 

// calling function
LateInTheGame();

echo "A->DoSometing()<br>";
$myA->DoSomething();

echo "B->DoSometing()<br>";
$myB->DoSomething();

function LateInTheGame()
{
   echo "Functions can be called before declared....<br>";
}

class A
{
   var $mydata = 0;
   
   function A() // class constructor has the same name as the class
   {
      // notice "this" keyword
      // by default php uses local variables so
      // you HAVE to include "this" in order to set/get mydata
      $this->mydata = 12;
      echo "Construct A<br>";
   }
   
   function DoSomething()
   {
      echo "Should do something here, can't remember now.<br>";
   }
}

// A is the base class for B
class B extends A
{
   function B()
   {
      echo "Construct B<br>";
      echo "mydata = ".$this->mydata."<br>";
   }
   
   // function overloading
   function DoSomething()
   {
      $this->DoSomethingElse();
   }
   
   function DoSomethingElse()
   {
      echo "Now I remember, take out the trash<br>";
   }
}
?>
