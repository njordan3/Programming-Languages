// This code will test if you are running Java 1.5
// This will will only run under Java 1.5

import java.util.*;

public class BoxUnbox {

   public static void main( String[] args) {

	Map<String, Integer> m = new TreeMap<String, Integer>();

	for (String word : args) { // The new For loop in Java 1.5
		Integer freq = m.get(word);
		// In the following line, int 1 (not an Integer type object
		// is boxed into an Integer Object in Java 1.5.
		m.put( word, freq == null ? 1 : freq +1 );
	}

	System.out.print(m);
   }
}
