package projecteuler;
import java.util.ArrayList;

import junit.framework.*;

public class Problem1Test extends TestCase {

    public void test1() {
	Problem1 p = new Problem1();
	System.out.print("Sum of divisors of 3 and 5: ");
	System.out.println(p.getSumofMultiples(1,999,new ArrayList<Integer>(){{ add(3); add(5);}}));
    }
}