/*
 * Author: Nicholas Jordan
 * Fall 2020
 * CMPS 3500 Programming Languages
 * Lab 4: Lab04.java
 */

import java.io.*;   //import everything having to do with I/O

public class Lab04  //class name must be name of file (Lab04.java)
{
    public static void main(String[] args) throws IOException
    {
        int tosses = 0;
        //handle exceptions for false user inputs
        if (args.length == 1) {
            try {
                tosses = Integer.parseInt(args[0]);
            } catch (NumberFormatException e) {
                tosses = getUserInt("How many tosses do you want to run?");
            }
        } else {
            tosses = getUserInt("How many tosses do you want to run?");
        }
        System.out.println("There will be "+tosses+" tosses:");
        //call Coin.class
        Coin coin = new Coin();
        int heads = 0, tails = 0;
        //flip coin
        for (int i = 1; i <= tosses; i++) {
            coin.toss();
            System.out.println("Toss "+i+": "+coin);
            if (coin.isHeads()) { 
                heads++;
            } else {
                tails++;
            }
        }
        //print results
        System.out.println("Results after "+tosses+" tosses:");
        System.out.println("Heads: "+heads);
        System.out.println("Tails: "+tails);
        
        //call Compute.class
        Compute c = new Compute();
        c.main();
    }

    public static int getUserInt(String prompt) throws IOException
    {
        //create custom input StreamReader object
        InputStreamReader isr = new InputStreamReader(System.in);
        BufferedReader stdin = new BufferedReader(isr);
        
        int input = 0;
        boolean done = false;
        while (!done) {
            System.out.println(prompt);
            try {
                input = Integer.parseInt(stdin.readLine());
                done = true;
            } catch (NumberFormatException e) {
                prompt = "Give me a number please...";
            }
        }
        return input;
    }
}
