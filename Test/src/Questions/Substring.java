package Questions;

public class Substring {

	public int substring(String search, String in) {
		int index =0 ;
		boolean equal = false;
		for(int i =0;i < in.length();i++){
			if(in.charAt(i) == search.charAt(0)){
				index = 0;
				equal = true;
				for(int j = 1;j < search.length();j++,index++)
					if(search.charAt(j) != in.charAt(i+j)){
						equal = false;
						break;
					}
				if(equal)
					return index;
			}
		}
		return -1;
	}

}
