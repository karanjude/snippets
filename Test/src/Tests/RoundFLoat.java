package Tests;

import junit.framework.TestCase;

public class RoundFLoat extends TestCase {
	public void testRoundFloat() throws Exception {
		assertEquals(Math.round(3.4), new RoundFLoat().round((float) 3.4));
		assertEquals(Math.round(3.4444), new RoundFLoat().round((float) 3.4444));
		assertEquals(Math.round(3.55), new RoundFLoat().round((float) 3.55));
	}

	private int round(float d) {
		return (int)(d + .5);
	}
}
