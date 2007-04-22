package Tests;

import junit.framework.TestCase;

public class DivideNumberBy3 extends TestCase {
	public void testDivideNumberBy3() throws Exception {
		assertEquals(3, new DivideNumberBy3().divideBy3(9));
		assertEquals(2, new DivideNumberBy3().divideBy3(6));
		assertEquals(9, new DivideNumberBy3().divideBy3(27));
	}

	private int divideBy3(int i) {
		int ans = 0;
		do{
			i = i - 3;
			ans++;
		}while(i > 0);
		return ans;
	}
}
