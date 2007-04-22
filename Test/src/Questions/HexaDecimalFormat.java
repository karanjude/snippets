package Questions;

public class HexaDecimalFormat {
	public String toHexaDeciamal(int number){
		int n = number;
		StringBuilder ans = new StringBuilder();
		do{
			char r = tohex(n % 16);
			ans.append(r);
			n = n / 16;
		}while(n > 0);
		return ans.reverse().toString();
	}

	private char tohex(int i) {
		if(i >= 10 && i < 16)
			return (char) ('A' + (i-10));
		return (char) ('0' + i);
	}
}
