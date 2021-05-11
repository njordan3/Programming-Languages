//  RanNums.java
//  Purpose: to import and use the the Random class.
//********************************************************************

import java.util.Random;

public class RanNums
{
   public static void main (String[] args)
   {
      Random generator = new Random();
      int num1;
      float num2;
      
      // random integers 
      num1 = generator.nextInt();
      System.out.println ("int: " + num1);

      num1 = generator.nextInt(10);
      System.out.println ("[0-9]: " + num1);

      num1 = generator.nextInt(10) + 1;
      System.out.println ("[1-10] " + num1);

      num1 = generator.nextInt(10) - 5;
      System.out.println ("[-5-5] " + num1);

      // random real numbers
      num2 = generator.nextFloat();
      System.out.println ("real [0-1]: " + num2);

      num2 = generator.nextFloat() * 5;  // 0.0 to 4.9999
      num1 = (int) num2 + 1;
      System.out.println ("[1-5]: " + num1);
   }
}

