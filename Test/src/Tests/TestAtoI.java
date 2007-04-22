package Tests;

import Questions.AtoI;
import junit.framework.TestCase;

public class TestAtoI extends TestCase {
	public void testAtoI() throws Exception {
		assertEquals(121, new AtoI().atoi("121"));
	}
}
