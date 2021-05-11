/* FormatWriteFileApp.java */

import java.io.*;
import java.util.Formatter;

/**
  * Demonstrate the java.util.Formatter capabilities for
  * formatting primitive types and sending them to a file.
**/
public class FormatWriteFileApp
{
  public static void main (String arg[]) {
    Formatter formatter = null;
    File file = null;

    // Get the file from the argument line.
    if (arg.length > 0) file = new File (arg[0]);
    // Else use a default file name.
    if (file == null) {
      System.out.println ("Default: textOutput.txt");
      file = new File ("textOutput.txt");
    }

    // Send formatted output to the file.
    try {
      formatter = new Formatter (file);
    }
    catch  (FileNotFoundException e) {
      // File not found exception thrown since this is a new
      // file name. However, Formatter will create the new file.
    }

    formatter.format ("Text output with Formatter. %n");
    formatter.format ("Primitives converted to strings: %n");

    boolean a_boolean =  false;
    byte    a_byte    =  114;
    short   a_short   =  1211;
    int     an_int    =  1234567;
    long    a_long    =  987654321;
    float   a_float   =  983.6f;
    double  a_double  = -4.297e-15;

    formatter.format ("boolean = %9b %n",   a_boolean);
    formatter.format ("byte    = %9d %n",   a_byte);
    formatter.format ("short   = %9d %n",   a_short);
    formatter.format ("int     = %9d %n",   an_int);
    formatter.format ("long    = %9d %n",   a_long);
    formatter.format ("float   = %9.3f %n", a_float);
    formatter.format ("double  = %9.2e %n", a_double);

    // Need to flush the data out of the buffer.
    formatter.flush ();
    formatter.close ();

  } // main

} // class FormatWriteFileApp
