package Questions;

public class AtoI {
	public int atoi(String a){
		int n = 0;
		for(int i = 0;i < a.length();i++){
			n = n * 10 + (a.charAt(i) - '0');
		}
		return n;
	}
}
