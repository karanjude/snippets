package Questions;

public class LinkList {

	public static final LinkList NIL = new LinkList(null, null);
	private LinkList list;
	private Integer val;

	public LinkList() {
		this.list = NIL;
	}

	private LinkList(Integer value, LinkList oldList) {
		val = value;
		list = oldList;
	}

	public LinkList(LinkList reversed2) {
		this.list = reversed2;
	}

	public LinkList add(int i) {
		this.list = new LinkList(i, list);
		return this;
	}

	public boolean end() {
		return this.list == NIL;
	}

	@Override
	public boolean equals(Object obj) {
		if (obj == null)
			return false;
		if (obj == this)
			return true;
		if (obj instanceof LinkList) {
			LinkList other = ((LinkList) obj).list;
			LinkList actual = this.list;
			return actual.val.equals(other.val)
					&& actual.list.equals(other.list);
		}
		return false;
	}

	public LinkList begin() {
		return this.list;
	}

	public LinkList next() {
		return this.list;
	}

	@Override
	public String toString() {
		StringBuilder s = new StringBuilder();
		s.append(" ");
		LinkList actual = this.list;
		if (actual != NIL) {
			s.append(actual.val + actual.toString());
		}
		return s.toString();
	}

	public LinkList reverse() {
		if (this.list == NIL)
			return new LinkList(this);
		else {
			LinkList rest = this.list;
			LinkList reversed = rest.reverse();
			this.list = reversed.list;
			reversed.list = this;
			return reversed;
		}
	}

	public int value() {
		return val;
	}

	public LinkList insert(Integer i) {
		LinkList node = this.list;
		boolean inserted = false;
		while(!node.end()){
			if((node.value() > i)  &&  (i > node.next().value()) ){
				node.list = new LinkList(i,node.list);
				inserted = true;break;
			}else if((node.value() < i)  &&  (i < node.next().value()) ){
				node.list = new LinkList(i,node.list);
				inserted = true;break;
			}
			node = node.next();
		}
		if(!inserted){
			if(i < node.value())
				node.list = new LinkList(i,node.list);
			else
				this.list = new LinkList(i,this.list);
		}
		return this;
	}

}
