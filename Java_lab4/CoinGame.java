//********************************************************************
// CoinGame.java
// Uses Coin class
//********************************************************************

public class CoinGame
{
   //-----------------------------------------------------------------
   //  Toss two coins until one of them comes up heads the requisite
   //  number of times in a row.
   //-----------------------------------------------------------------
   public static void main (String[] args)
   {
      final int GOAL = 3;
      int count1 = 0, count2 = 0;

      // Create two separate coin objects
      Coin coin1 = new Coin();
      Coin coin2 = new Coin();

      while (count1 < GOAL && count2 < GOAL)
      {
         coin1.toss();
         coin2.toss();

         // Print the toss results 
         // the toString method is called by default as the object name
         System.out.print ("Coin 1: " + coin1);
         System.out.println ("   Coin 2: " + coin2);

         // Increment or reset the counters
         count1 = (coin1.isHeads()) ? count1+1 : 0;
         count2 = (coin2.isHeads()) ? count2+1 : 0;
      }

      // Display results 
      System.out.println ("And the Winner is:");
      if (count1 < GOAL)
         System.out.println ("Coin #2.");
      else
         if (count2 < GOAL)
            System.out.println ("Coin #1.");
         else
            System.out.println ("Neither (a tie).");
   }
}
