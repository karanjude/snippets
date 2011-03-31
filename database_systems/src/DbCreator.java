import java.io.IOException;
import java.sql.SQLException;

public class DbCreator {
	public void createDb(QueryExecutior queryExecutior) throws ClassNotFoundException,
			SQLException, IOException {
		dropTables(queryExecutior);
		createTables(queryExecutior);
	}

	private void createTables(QueryExecutior queryExecutior)
			throws IOException, ClassNotFoundException, SQLException {
		SqlReader sqlReader = new SqlReader("src/createdb.sql");
		for (String sql : sqlReader.sql()) {
			System.out.println(sql);
			queryExecutior.ddlQuery(sql);
		}
	}

	private void dropTables(QueryExecutior queryExecutior)
			throws IOException, ClassNotFoundException {
		SqlReader sqlReader = new SqlReader("src/dropdb.sql");
		for (String sql : sqlReader.sql()) {
			System.out.println(sql);
			try {
				queryExecutior.ddlQuery(sql);
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
	}
}
