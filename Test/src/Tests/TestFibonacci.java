package Tests;

import Questions.CoolFiboNacci;
import junit.framework.TestCase;

public class TestFibonacci extends TestCase {
	public void testFibonacci() throws Exception {
		assertEquals(0, new CoolFiboNacci().fiboNacci(0));
		assertEquals(1, new CoolFiboNacci().fiboNacci(1));
		assertEquals(1, new CoolFiboNacci().fiboNacci(2));
		assertEquals(2, new CoolFiboNacci().fiboNacci(3));
		assertEquals(3, new CoolFiboNacci().fiboNacci(4));
	}
}
