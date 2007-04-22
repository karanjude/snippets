package Tests;

import com.sun.xml.internal.bind.v2.runtime.IllegalAnnotationsException.Builder;

import junit.framework.TestCase;

public class Connectivity extends TestCase {
	private int[][] m;

	public Connectivity(int[][] m) {
		this.m = m;
		build(0,0);
	}
	
	public Connectivity(String s){
		super(s);
	}


	private void build(int v,int y) {
		int n = m.length;
		for(int k = 0;k < n;k++){
			for(int i = 0;i < n;i++ ){
				for(int j = 0;j < n;j++){
					if(m[i][j] == 0 && (i!= j)){
						if((m[i][k] + m[k][j]) == 1)
							m[i][j] = 1;
					}
				}
			}
		}
	}

	public void testConnectivity() throws Exception {
		int[][] m = new int[][]{
				{0,1,0},
				{1,0,1},
				{1,1,0}
		};
		assertEquals(true, new Connectivity(m).isConnected());
	}

	private boolean isConnected() {
		for(int i = 0;i < m.length;i++){
			for(int j=0;j < m[0].length;j++){
				if(i != j && m[i][j] == 0)
					return false;
			}
		}
		return true;
	}
}
