import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.charset.Charset;
import java.util.ArrayList;

public class SqlReader {

	private String sqlFile;

	public SqlReader(String file) {
		this.sqlFile = file;
	}

	public ArrayList<String> sql() throws IOException {
		BufferedReader reader = null;
		String sqlString;
		ArrayList<String> parts = new ArrayList<String>();

		reader = new BufferedReader(new InputStreamReader(getClass()
				.getResourceAsStream(sqlFile)));

		String line;
		StringBuffer string = new StringBuffer();
		try {
			while ((line = reader.readLine()) != null) {
				string.append(line);
			}
			sqlString = string.toString();
		} finally {
			reader.close();
		}
		makeSqlArray(sqlString, parts);
		return parts;
	}

	private void makeSqlArray(String sqlString, ArrayList<String> parts) {
		if (null != sqlString) {
			String[] p = sqlString.split("/");
			for (String s : p) {
				String ss = s.trim();
				if (0 != ss.length()) {
					parts.add(s.trim());
				}
			}
		}
	}

}
