package projecteuler;
import java.util.ArrayList;

import junit.framework.*;

public class Problem2Test extends TestCase {

    public void testProblem2() {
	Problem2 p = new Problem2();
	System.out.print("Sum of even fibs less than 4mil: ");
	System.out.println(p.addEvenFib(4000000));
    }
}