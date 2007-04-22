package Tests;

import junit.framework.TestCase;

public class BitsRequired extends TestCase {
	public void testBitsRequired() throws Exception {
		assertEquals(1,new BitsRequired().bitsRequired(2,3));
		assertEquals(1,new BitsRequired().bitsRequired(1,3));
	}

	private int bitsRequired(int i, int j) {
		int r = i ^ j;
		int a = r;
		int k = 0;
		int b = 0;
		do{
			a = a >> 1;
			if((r & (1 << k)) == (1 << k))
				b++;
			k++;
		}while(a > 0);
		return b;
		
	}
}
