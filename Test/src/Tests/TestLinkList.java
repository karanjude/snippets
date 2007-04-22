package Tests;

import Questions.LinkList;
import junit.framework.TestCase;

public class TestLinkList extends TestCase {
	public void testLinkedList() throws Exception {
		LinkList expected = new LinkList();
		expected.add(1).add(2).add(3);
		
		LinkList actual = new LinkList();
		actual.add(1).add(2).add(3);
		
		assertEquals(expected, actual);
	}

	public void testReverse() throws Exception {
		//LinkList expected = new LinkList();
		//expected.add(1).add(2);
		
		LinkList actual = new LinkList();
		actual.add(1);
		
		System.out.println(actual.reverse());
		
		//assertEquals(expected, actual.reverse());
		
	}
	
}
