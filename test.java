/* HelloWorld.java
	  */

import java.util.*;

public class test
{
		public static void main(String[] args) {
			Set<List<Integer>> set = new HashSet<>();
			List<Integer> l1 = Arrays.asList(1,2,3);
			List<Integer> l2 = Arrays.asList(1,2,3);
			List<Integer> l3 = Arrays.asList(2,1,3);
			List<Integer> l4 = Arrays.asList(2,3,1);
			List<Integer> l5 = Arrays.asList(5,3,1);
			set.add(l1);
			set.add(l2);
			set.add(l3);
			set.add(l4);
			set.add(l5);


			for (List<Integer> l: set) {
				for (Integer i: l) {
					System.out.print(i);
					System.out.print(' ');
				}
				System.out.println();
			}
			System.out.println("Hello World!");
		}
}
