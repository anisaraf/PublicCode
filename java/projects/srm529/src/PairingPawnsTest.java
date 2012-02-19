package codeherb.topcoder;
import java.util.ArrayList;

import junit.framework.*;
import static org.junit.Assert.assertEquals;

public class PairingPawnsTest extends TestCase {

    PairingPawns p = new PairingPawns();
    public void test1() {
	assertEquals(1,p.savedPawnCount(new int[] {0,2}));
    }

    public void test2() {
	assertEquals(3921,p.savedPawnCount(new int[] {1000,2000,3000,4000,5000,6000,7000,8000}));
    }

}

