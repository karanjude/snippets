package Tests;

import junit.framework.TestCase;

public class Hex2Int extends TestCase {
	public void testHex2Int() throws Exception {
		assertEquals(255,new Hex2Int().toInteger("FF"));
		assertEquals(254,new Hex2Int().toInteger("FE"));
		assertEquals(253,new Hex2Int().toInteger("FD"));
	}

	private int toInteger(String s) {
		int n = 0;
		int m;
		for(int i = 0;i < s.length();i++){
			char c = s.charAt(i);
			if(c >= 'A' && c <= 'F')
				m = 10 + (c-'A');
			else
				m = c-'0';
			n = n * 16 + m;
		}
		return n;
	}
}
