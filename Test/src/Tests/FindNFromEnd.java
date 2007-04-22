package Tests;

import sun.awt.image.ImageWatched.Link;
import Questions.LinkList;
import junit.framework.TestCase;

public class FindNFromEnd extends TestCase {
	public void testFindNFromEnd() throws Exception {
		LinkList a = new LinkList();
		a.add(1).add(2).add(3);
		assertEquals(new Integer(3), new FindNFromEnd().findFromEnd(3, a));
		
	}

	private Integer findFromEnd(int n, LinkList list) {
		LinkList node = list.begin();
		n = n -1;
		int k = 1;
		LinkList result = null;
		while(!node.end()){
			if(k==n)
				result = list.begin();
			else if(k > n)
				result = result.next();
			k++;
			node = node.next();
		}
		return new Integer(result.value());
	}
}
