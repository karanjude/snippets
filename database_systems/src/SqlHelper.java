
public class SqlHelper {

	public String generateAnimalSql(String input) {
		String animalSql = "insert into animals values(%s, '%s', SDO_GEOMETRY(2001,NULL,SDO_POINT_TYPE(%s,%s,NULL),NULL,NULL))";
		
		return String.format(animalSql, input.split(", "));
	}

}
