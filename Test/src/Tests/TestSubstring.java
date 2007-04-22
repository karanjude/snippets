package Tests;

import Questions.Substring;
import junit.framework.TestCase;

public class TestSubstring extends TestCase {
	public void testSubstring() throws Exception {
		assertEquals(2, new Substring().substring("and","bband"));
	}
}
