package Questions;

public class NonMajorDiagonalExchange {

	public int[][] exchange(int[][] actual) {
		int m = actual.length;
		int n = actual[0].length;
		for(int i = 0;i <= m/2;i++){
				int a = actual[i][n-i-1];
				actual[i][n-i-1] =  actual[m-i-1][i];
				actual[m-i-1][i] = a;
		}
		return actual;
	}
	

}
