package Questions;

public class BinarySearchTree {
	
	private final Node NIL = new Node(-1,null,null);
	private Node root;
	private int[] values; 
	private int i = 0;
	
	public BinarySearchTree(int [] values,boolean BST){
		this.values = values;
		int n = values.length;
		this.root = createBST(new Node(values[i++],NIL,NIL),n-1);
	}

	private int depth(Node root,int dd){
		if(root == NIL)
			return dd-1;
		else{
			int ld = depth(root.left,dd+1);
			int rd = depth(root.right,dd+1);
			int d = Math.max(ld,rd);
			return d;
		}
	}
	
	private Node createBST(Node root,int n){
		if( n == 0){
			if(root != NIL)
				return root;
			return NIL;
		}else{
			int value = root.value;
			int tvalue = values[i++];
			if(tvalue < value)
				root.left = createBST(new Node(tvalue,NIL,NIL),n-1);
			else
				root.right = createBST(new Node(tvalue,NIL,NIL),n-1);
		}
		return root;
	}
	
	private Node create(int n){
		if(n == 0)
			return NIL;
		else {
			int nl = n/2;
			int nr = n-nl-1;
			Node node = new Node(values[i++],create(nl),create(nr));
			this.root = node;
		}
		return this.root;
	}
	
	public void print(){
		print(this.root);
	}
	
	private void print(Node node) {
		if(node != NIL){
			print(node.left);
			System.out.print(" " + node.value);
			print(node.right);
		}
	}

	class Node{
		public Node(int value, Node left, Node right) {
			this.value = value;
			this.left = left;
			this.right = right;
		}
		
		@Override
		public boolean equals(Object obj) {
			if(obj == null) return false;
			if(this == obj) return true;
			else if(obj instanceof Node){
				Node other = (Node) obj;
				return other.value == value && other.left.equals(left) && other.right.equals(right);
			}
			return false;
		}



		int value ;
		Node left;
		Node right;
	}

	public int depth() {
		return depth(this.root,0);
	}

	public int  sum() {
		return sum(this.root,0);
	}

	private int sum(Node root,int total) {
		if(root == NIL)
			return total;
		else{
			int ld = sum(root.left,total+root.value);
			int rd = depth(root.right,total+root.value);
			int d = Math.max(ld,rd);
			return d;
		}
	}
}
