/********************************************************************/
/*     Demonstrates parameter passing in Java                       */ 
/*     Uses: Dog.java                                               */
/*                                                                  */
/********************************************************************/

import java.io.*;    
import java.util.List;
import java.util.LinkedList;

public class Functions {

   public static void main (String[] args) throws IOException {

      Dog x; // you can do this, but x is not an object yet!
      x = new Dog("no name");  // x is now a Dog object
                               // all objects are allocated from the heap      
      Dog c = new Dog("no name");
      x = c;  // x and b both point to the same Dog
      c.setName("Bowser");
      System.out.println ("x is Bowser: " + x.getName() );    
      x.setName("Fluffy");
      System.out.println ("c is Fluffy: " + c.getName() );    
 
      c.setName("Fido");  
      foo(c);                                       
      System.out.println ("From main Dog c is still Fido: " + c.getName()); 
      foo2(c);                                          
      System.out.println ("From main Dog c is now Dixie: " + c.getName() );  
      foo3(c);                               
      System.out.println ("From main Dog c is still Dixie:" + c.getName());    
      System.out.println ("From main Dog x is also Dixie:" + x.getName());    
   }   // end main

   public static void foo(Dog d) {
      d = new Dog("Feather");              // points local d to a new Dog object
      System.out.println ("From foo Dog d is Feather: " + d.getName() );
   }

   public static void foo2(Dog d) {
      d.setName("Dixie");           // setName changes Dog name in caller
      System.out.println ("From foo2 Dog d is Dixie: " + d.getName() );
   }
   public static void foo3(Dog d) {
      Dog e = new Dog("Spot");
      d = e;          // points local d to a new Dog object  
      System.out.println ("From foo3 Dog d is Spot:" + d.getName() ); 
    }

   public static int fib(int n) {
      if (n == 0) return 0; 
      if (n == 1) return 1; 
      return fib(n-1) + fib(n-2);
   } 
}
/* used in Functions.java  

public class Dog
{
   private String name;

   public Dog ( String s)
   { name = s; }

   public void setName (String s)
   { name = s; }

   public String getName ()
   { return name; }


}
*/
