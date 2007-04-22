package Tests;

import Questions.LinkList;
import junit.framework.TestCase;

public class InsertInSortedList extends TestCase {
	public void testInsertInSortedList() throws Exception {
		LinkList expected = new LinkList();
		expected.add(1).add(2).add(3).add(4);
		
		LinkList actual = new LinkList();
		actual.add(1).add(2).add(4);
		System.out.println(	actual.insert(new Integer(3)));
	
		LinkList actual1 = new LinkList();
		actual1.add(1).add(3).add(4);
		System.out.println(	actual1.insert(new Integer(2)));
		
		LinkList actual2 = new LinkList();
		actual2.add(2).add(3).add(4);
		System.out.println(	actual2.insert(new Integer(1)));
		
		LinkList actual3 = new LinkList();
		actual3.add(1).add(2).add(3);
		System.out.println(	actual3.insert(new Integer(4)));
		
		
		
	}
}
