package Tests;
import Questions.HexaDecimalFormat;
import junit.framework.TestCase;


public class TestToHexaDecimal extends TestCase {
	public void testHexaDeciaml() throws Exception {
		assertEquals("FF", new HexaDecimalFormat().toHexaDeciamal(255));
		assertEquals("100", new HexaDecimalFormat().toHexaDeciamal(256));
	}
}
