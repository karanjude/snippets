package Questions;
import java.util.Hashtable;



public class CoolFiboNacci {

	Hashtable<Integer,Integer> t = new Hashtable<Integer,Integer>(); 
	
	public int fiboNacci(int n ){
		if(t.containsKey(new Integer(n)))
			return t.get(new Integer(n));
		int ans;
		if(n == 0)
			return 0; 
		else if(n == 1)
			return 1;
		else{
			 ans = fiboNacci(n-2) + fiboNacci(n-1);
			t.put(new Integer(n), ans);
		}
		return ans;
	}
}
