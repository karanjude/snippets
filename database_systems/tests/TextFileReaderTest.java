import java.util.ArrayList;

import junit.framework.TestCase;

public class TextFileReaderTest extends TestCase {
	public void testAnimalReadScript() throws Exception {
		TextFileReader textReader = new TextFileReader("animals.txt");
		ArrayList<String> parts = textReader.sql();

		assertEquals(100, parts.size());
		SqlHelper sqlHelper = new SqlHelper();

		for (String sql : parts) {
			System.out.println(sqlHelper.generateAnimalSql(sql.trim()));
		}
	}

	public void testConnectionInfo() throws Exception {
		TextFileReader textReader = new TextFileReader("config.txt");
		ConnectionInfo info = textReader.connectionInfo();
		assertEquals("localhost", info.host);
		assertEquals("1521", info.port);
		assertEquals("XE", info.dbname);
		assertEquals("jude", info.username);
		assertEquals("jude", info.password);
	}
}
