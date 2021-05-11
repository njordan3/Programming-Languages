/* Bottles.java
 * Usage: 
 * 
 *  > javac Bottles.java 
 *  > java Bottles 
 *  99 Bottles in Java
 */

public class Bottles 
{
  public static void main(String[] args)
  {
     for (int i= 99; i>= 1; i--) {
        System.out.print(i+" Bottle");
        if ( i > 1 )
            System.out.print("s ");
        System.out.println(" of beer on the wall," + i + " bottle(s) of beer"); 
        System.out.print("Take one down, pass it around,"); 
        System.out.println((i-1)+" bottle(s) of beer on the wall");
      }
   } 
}  // end java99 
