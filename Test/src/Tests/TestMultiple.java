package Tests;

import Questions.Multiple;
import junit.framework.TestCase;

public class TestMultiple extends TestCase {
	public void testMultiple() throws Exception {
		assertEquals(24, new Multiple().nextMultiple(8,18));
	}
}
