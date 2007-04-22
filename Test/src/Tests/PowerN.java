package Tests;

import junit.framework.TestCase;

public class PowerN extends TestCase {
	public void testPowerN() throws Exception {
		assertEquals(16, new PowerN().power( 2, 4));
	}

	private int power(int x, int n) {
		if(n == 0)
			return 1;
		else if(n % 2 == 0){
			return power(x,n/2) * power(x, n/2);
		}
		else
			return x * power(x,n-1);
	}
}
