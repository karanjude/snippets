import java.util.ArrayList;

import junit.framework.TestCase;

public class TextFileReaderTest extends TestCase {
	public void testAnimalReadScript() throws Exception {
		TextFileReader textReader = new TextFileReader("src/animal.txt");
		ArrayList<String> parts = textReader.sql();

		assertEquals(100, parts.size());
		SqlHelper sqlHelper = new SqlHelper();
		
		for (String sql : parts) {
			System.out.println(sqlHelper.generateAnimalSql(sql.trim()));
		}
	}

}
