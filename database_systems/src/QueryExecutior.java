import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class QueryExecutior {
	Connection conn;

	public QueryExecutior() throws ClassNotFoundException, SQLException {
		Class.forName("oracle.jdbc.driver.OracleDriver");

		conn = DriverManager.getConnection(
				"jdbc:oracle:thin:@//localhost:1521/XE", "jude", "jude");

	}

	public void close() {
		try {
			conn.close();
		} catch (Exception ignore) {
		}
	}

	public void ddlQuery(String sql) throws ClassNotFoundException,
			SQLException {

		Statement stmt = conn.createStatement();
		try {
			int rset = stmt.executeUpdate(sql);
		} finally {
			try {
				stmt.close();
			} catch (Exception ignore) {
			}
		}
	}

	public void insertQuery(String sql) throws ClassNotFoundException,
			SQLException {
		ddlQuery(sql);
	}

}
