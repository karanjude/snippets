package Tests;
import Questions.SecondLargest;
import junit.framework.TestCase;


public class TestSecondLargest extends TestCase {
	public void testSecondLargest() throws Exception {
		assertEquals(2, new SecondLargest().find(new int[]{1,2,3}));
		assertEquals(3, new SecondLargest().find(new int[]{1,2,3,4}));
	}
}
