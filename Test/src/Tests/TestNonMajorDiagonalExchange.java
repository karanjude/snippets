package Tests;

import Questions.NonMajorDiagonalExchange;
import junit.framework.TestCase;

public class TestNonMajorDiagonalExchange extends TestCase {
	public void testNonMajorDiagonalExchange() throws Exception {
		int[][] expected = new int[][]{
				{0,1,6},
				{3,4,5},
				{2,7,8}
		};
		
		int[][] actual = new int[][]{
				{0,1,2},
				{3,4,5},
				{6,7,8}
		};
		assertEquals(expected, new NonMajorDiagonalExchange().exchange(actual));
	}
}
