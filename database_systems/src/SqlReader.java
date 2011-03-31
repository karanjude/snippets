import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.charset.Charset;
import java.util.ArrayList;

public class SqlReader {

	private File sqlFile;

	public SqlReader(String file) {
		this.sqlFile = new File(file);
	}

	public ArrayList<String> sql() throws IOException {
		FileInputStream stream = null;
		String sqlString;
		ArrayList<String> parts = new ArrayList<String>();

		stream = new FileInputStream(sqlFile);

		try {
			FileChannel fc = stream.getChannel();
			MappedByteBuffer bb = fc.map(FileChannel.MapMode.READ_ONLY, 0, fc
					.size());
			sqlString = Charset.defaultCharset().decode(bb).toString();
		} finally {
			stream.close();
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
