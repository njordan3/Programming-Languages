/*
 * Author: Nicholas Jordan
 * Fall 2020
 * CMPS 3500 Programming Languages
 * Lab 4: Compute.java
 */

import java.io.*;
import java.util.ArrayList;
import java.util.Formatter;

public class Compute
{
    public static void main() throws IOException
    {
        FileReader fr = new FileReader("lab04.txt");
        BufferedReader file = new BufferedReader(fr, 4096 /*buffer size*/);

        ArrayList<String> lines = new ArrayList<String>();  //temporary dynamic string array
        
        //load the temporary array
        String line = file.readLine();
        while (line != null) {
            lines.add(line);
            line = file.readLine();
        }
        //we assume 4 columns, but we cannot assume how many rows there will be
        String[][] data = new String[4][lines.size()];
        int[] mean = new int[4];

        for (int i = 0; i < lines.size(); i++) {
            //trim and parse line elements into an array
            String[] line_array = lines.get(i).trim().split("\\s+");
            //transfer parsed array to our 2D array
            for (int j = 0; j < 4; j++) {
                data[j][i] = line_array[j];
            }
        }

        mean = calculateMean(data);
        
        writeDataToFile("out.file", data, mean);
    }
    private static int[] calculateMean(String[][] data)
    {
        int[] mean = new int[4];
        int col_length = data[0].length;
        for (int i = 0; i < 4; i++) {
            int sum = 0;
            for (int j = 0; j < col_length; j++) {
                sum += Integer.parseInt(data[i][j]);
            }
            mean[i] = sum / col_length;
        }
        return mean;
    }
    private static void writeDataToFile(String file_name, String[][] data, int[] mean)
    {
        //format the entire string first
        String format = "%12s"; //right justify 12 width
        
        //Title
        String output = "Name: Nicholas Jordan CMPS 3500 Lab04\n";
        //Headers
        for (int i = 0; i < 4; i++) {
            output += String.format(format, "Exam"+(i+1));
        }
        output += "\n";
        for (int i = 0; i < 4; i++) {
            output += String.format(format, "=====");
        }
        //Body
        output += "\n";
        for (int i = 0; i < data[0].length; i++) {
            for (int j = 0; j < 4; j++) {
                output += String.format(format, data[j][i]);
            }
            output += "\n";
        }
        //Footer
        for (int i = 0; i < 4; i++) {
            output += String.format(format, "=====");
        }
        output += "\n";
        output += "Mean:";
        format = "%7s"; //adjust format for 'Mean:'
        for (int i = 0; i < 4; i++) {
            output += String.format(format, mean[i]);
            format = "%12s"; //adjust format to before 'Mean:'
        }
        output += "\n";
        
        //write the string to the file
        File file = new File(file_name);
        Formatter formatter = null;
        try {
            formatter = new Formatter(file);
        } catch(FileNotFoundException e) {
            // File not found exception thrown since this is a new
            // file name. However, Formatter will create the new file.
        }
        formatter.format(output);   //write to file
        formatter.flush();          //flush data out of the buffer
        formatter.close();
    }
}
