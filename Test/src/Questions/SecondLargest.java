package Questions;
import java.util.Arrays;


public class SecondLargest {
	
	public int find(int[] numbers){
		int big = Math.max(numbers[0],numbers[1]);
		int sbig = Math.min(numbers[0],numbers[1]);
		for (int i = 2; i < numbers.length; i++) {
			if(numbers[i] > big){
				sbig = big;
				big = numbers[i];
			}
		}
		return sbig;
	}
}
