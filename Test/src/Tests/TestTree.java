package Tests;

import Questions.BinarySearchTree;
import junit.framework.TestCase;

public class TestTree extends TestCase {
	public void testTree() throws Exception {
		int[] values = {3,2,1,4,5};
		BinarySearchTree tree = new BinarySearchTree(values,true);
		tree.print();
		System.out.println(" ");
		System.out.println(tree.depth());
		System.out.println(tree.sum());
	}
}
