package projecteuler;
import java.util.ArrayList;

import junit.framework.*;

public class Problem3Test extends TestCase {

    public void test1() {
	Problem3 p = new Problem3();
	System.out.print("Largest prime factor: ");
	System.out.println(p.largestPrimeFactor(600851475143));
    }
}