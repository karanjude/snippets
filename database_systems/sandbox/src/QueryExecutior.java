import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class QueryExecutior {
	Connection conn;

	public QueryExecutior(ConnectionInfo connectionInfo)
			throws ClassNotFoundException, SQLException {
		Class.forName("oracle.jdbc.driver.OracleDriver");

		conn = DriverManager.getConnection("jdbc:oracle:thin:@//"
				+ connectionInfo.host + ":" + connectionInfo.port + "/"
				+ connectionInfo.dbname, connectionInfo.username,
				connectionInfo.password);

	}

	public void close() {
		try {
			conn.close();
		} catch (Exception ignore) {
		}
	}

	public void ddlQuery(String sql) throws ClassNotFoundException,
			SQLException {

		System.out.println(sql);

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

	public ResultSet selectQuery(String sql) throws SQLException {
		// System.out.println(sql);
		ResultSet result;

		Statement stmt = conn.createStatement();
		result = stmt.executeQuery(sql);
		return result;
	}

}
