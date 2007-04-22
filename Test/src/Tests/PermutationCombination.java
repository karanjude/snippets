package Tests;

import junit.framework.TestCase;

public class PermutationCombination extends TestCase {
	public void testPermuation() throws Exception {
		new PermutationCombination().printPermutation(3);
		System.out.println();
		new PermutationCombination().printCombination(3,3);
	}

	private void printCombination(int n,int r) {
		int[] s = new int[r];
		for(int i = 0;i < r;i++)
			s[i] = i+1;
		print(s);
		System.out.println();
		int rr = r-1;
		for(int i = 2;i<= ncr(n,r);i++){
			int m = rr;
			int max_val = n;
			while(m>0 && s[m]==max_val){
				m=m-1;
				max_val = max_val-1;
			}
			s[m]=s[m]+1;
			for(int j = m+1;j<r;j++)
				s[j] = s[j-1]+1;
			print(s);
			System.out.println();
		}
	}

	
	
	private int ncr(int n, int r) {
		int num = fact(n) * fact(r);
		int de = fact(n-r);	
		return num/de;
	}

	private void printPermutation(int n) {
		int[] s = new int[n];
		for(int i = 0;i < n;i++)
			s[i] = i+1;
		print(s);
		System.out.println();
		int nn = n-1;
		for(int i = 2;i <= fact(n);i++){
			
			int m = nn-1;
			while(!(s[m]<s[m+1]))
				m = m-1;
			int k = nn;
			while(!(s[k]>s[m]))
				k = k-1;
			int c = s[m];s[m]=s[k];s[k]=c;
			int p = m+1;
			int q = nn;
			while(p<q){
				int d = s[p];s[p]=s[q];s[q]=d;
				p = p+1;
				q = q-1;
			}
			print(s);
			System.out.println();
		}
	}
	
	

	private int fact(int n) {
		int f = 1;
		for(int i=n; i>0;i--)
			f *= i;
		return f;
	}

	private void print(int[] arr) {
		for (int i : arr) {
			System.out.print(i);
		}
	}
	
	
}
