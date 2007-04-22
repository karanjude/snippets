package Questions;

public class Multiple {
	public int nextMultiple(int n ,int higerThan ){
		int i = 1;
		while(true){
			int multiple = (n << i-1) + n;
			System.out.println(multiple);
			if(multiple > higerThan)
				return multiple;
			i++;
		}
	}
}
