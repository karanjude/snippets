import java.io.File;
import java.util.ArrayList;

import junit.framework.TestCase;

public class SqlReaderTest extends TestCase {
	public void testCreateDbScript() throws Exception {
		SqlReader sqlReader = new SqlReader("src/createdb.sql");
		ArrayList<String> parts = sqlReader.sql();

		assertEquals(3, parts.size());

		for (String sql : parts) {
			System.out.println(sql.trim());
		}
	}

	public void testDropDbScript() throws Exception {
		SqlReader sqlReader = new SqlReader("src/dropdb.sql");
		ArrayList<String> parts = sqlReader.sql();
		
		System.out.println(parts.size());
		assertEquals(3, parts.size());

		for (String sql : parts) {
			System.out.println(sql.trim());
		}
	}

}
