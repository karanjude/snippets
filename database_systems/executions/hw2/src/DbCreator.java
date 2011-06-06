import java.io.File;
import java.io.IOException;
import java.net.URISyntaxException;
import java.sql.SQLException;

public class DbCreator {
	public void createDb(QueryExecutior queryExecutior)
			throws ClassNotFoundException, SQLException, IOException,
			URISyntaxException {
		dropTables(queryExecutior);
		createTables(queryExecutior);
	}

	private void createTables(QueryExecutior queryExecutior)
			throws IOException, ClassNotFoundException, SQLException,
			URISyntaxException {
		SqlReader sqlReader = new SqlReader("sql/createdb.sql");
		for (String sql : sqlReader.sql()) {
			System.out.println(sql);
			queryExecutior.ddlQuery(sql);
		}
	}

	private void dropTables(QueryExecutior queryExecutior) throws IOException,
			ClassNotFoundException, URISyntaxException {
		SqlReader sqlReader = new SqlReader("sql/dropdb.sql");
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
