public static void printByLevel(BinNode<Integer> t, int curr_lvl, int wanted_lvl){
	if(curr_lvl == wanted_lvl){
		System.out.println(t.getValue());
	}else{
		if(t.getLeft() != null){
			printByLevel(t.getLeft(), curr_lvl+1, wanted_lvl);
		}
		if(node.getRight()!= null){
			printByLevel(t.getRight(), curr_lvl+1, wanted_lvl);
		}
	}
}
public static void stackPreOrder(BinNode<Integer> t){
	Stack<BinNode<Integer>> s = new Stack<BinNode<Integer>>();
	s.push(t);
	BinNode<Integer> temp = new BinNode<Integer>();
	while(!s.isEmpty()){
		temp = s.pop();
		System.out.println(temp.getValue());
		if(temp.getRight()!= null){
			s.push(temp.getRight());
		}
		if(temp.getLeft() != null){
			s.push(temp.getLeft());
		}
	}
}
public static stack<Node<Integer>> fillMissingInQueue(Stack<Queue<Integer>> SQ){
	/*using tempSL because if i put the nodes straight into SL
		the order will be reversed*/
	stack<Node<Integer>> tempSL = new stack<Node<Integer>>();
	
	stack<Node<Integer>> SL = new stack<Node<Integer>>();
	
	Stack<Queue<Integer>> tempSQ = new Stack<Queue<Integer>>();
	
	while(!SQ.isempty()){
		Queue<Integer> temp = SQ.push()
		tempSL.push(missingInQueue(temp));
		tempSQ.push(temp);
	}
	while(!tempSQ.isEmpty()){
		SQ.push(tempSQ.remove());
	}
	while(!tempSL.isEmpty()){
		SL.push(tempSL.remove());
	}
	return SL;
}


public static Node<Integer> missingInQueue(Queue<Integer> q){
	Queue<Integer> temp = new Queue<Integer>();
	Node<Integer> first_node;
	Node<Integer> current_node;
	int last = q.remove();
	temp.insert(last);
	while(!q.isempty()){
		int current = q.remove();
		int i = current;
		temp.insert(current);
		while(--i > last ){
			if(first_node == null){
				first_node = new Node<Integer>(i);
				current_node = first_node;
			}else{
				current_node.setNext(new Node<Integer>(i));
				current_node = current_node.getNext();
			}
		}
		last = current;
	}
	while(!temp.isEmpty()){
		q.insert(temp.remove);
	}
	return first_node;
} 

public static Queue levelScanToQueue(BinNode<Integer> t){
	Queue<BinNode<Integer>> q = new Queue<BinNode<Integer>>();
	Queue<Integer> res = new Queue<Integer>();
	temp.insert(t);
	BinNode<Integer> temp;

	while(!temp.isEmpty()){
		temp = q.remove();
		res.insert(temp.getValue());
		if(temp.getLeft()!= null){
			q.insert(temp.getLeft());
		}
		if(temp.getRight() != null){
			q.insert(temp.getRight());
		}
	}
}


public static boolean isSortedByLevel(BinNode<Integer> t){
	return isQueueSorted(levelScanToQueue(t));
}

public static boolean isQueueSorted(Queue<Integer> q){
	Queue<Inetger> temp = new Queue<Integer>();
	int last = q.remove();
	int curr;
	temp.insert(last);
	while(!q.isEmpty()){
		curr = q.remove();
		if(curr<last){/* curr>=last is sorted*/
			spillQueue(q , temp);
			spillQueue(temp, q);
			
			return false;
		}
		temp.insert(curr);
		last = curr;
	}
	spillQueue(temp, q);
	return true;
}
public static <T> void spillQueue(Queue<T> full, Queue<T> empty){
	while(!full.isEmpty){
				empty.insert(q.remove());
		}
}