import junit.framework.TestCase;

public class SqlHelperTest extends TestCase {
	public void testInsertSql() throws Exception {
		String input = "001, tiger, 10, 20";
		SqlHelper sqlHelper = new SqlHelper();
		String animalsql = sqlHelper.generateAnimalSql(input);
		
		String expected = "insert into animals values(001, 'tiger', SDO_GEOMETRY(2001,NULL,SDO_POINT_TYPE(10,20,NULL),NULL,NULL));";
		assertEquals(expected, animalsql);
	}
}
