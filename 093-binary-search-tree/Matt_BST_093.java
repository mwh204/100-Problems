public class Matt_BST_093{
  
  public static void main(String[] args) { 
    
    int[] asd = {3, 4, 2, 5, 4, 6, 7};
    BST tree = new BST(asd[0]);
    
    for(int i = 1; i<asd.length; i++){
      tree.insert(tree.root, asd[i]);
    }
    tree.printInc();
    tree.printTree();
    
    tree.balance();
    
    tree.printInc();
    tree.printTree();
  }
  
  private static class BST{
    
    private Node root;
    
    public BST(int element){
      root = new Node(element);
    }
    
    private Node insert(Node n, int e){
      if(n == null){
        return (n = new Node(e));
      }
      if(e < n.data){
        n.left = insert(n.left, e);
      }else{
        n.right = insert(n.right, e);
      }
      return n;
    }
    
    private void balance(){
      balanceTree(root);
    }
    
    private void reverse(){
      reverse(root);
    }
    
    private boolean isBalanced(){
      return isBalanced(root);
    }
    
    private int maxDepth(Node n){
      if(n == null){
        return 0;
      }
      return 1 + Math.max(maxDepth(n.left), maxDepth(n.right));
    }
    
    private int numNodes(Node n){
      int count = 0;
      if(n != null){
        count = 1 + numNodes(n.left) + numNodes(n.right);
      }
      return count;
    }
    
    private Node search(int k){
      Node x = root;
      while(x != null && k != x.data){
        if(k < x.data){
          x = x.left;
        }else{
          x = x.right;
        }
      }
      return x;
    }
    
    private int minimum(Node x){
      while(x.left != null){
        x = x.left;
      }
      return x.data;
    }
    
    private int maximum(Node x){
      while(x.right != null){
        x = x.right;
      }
      return x.data;
    }
    
    private void printInc(){
      System.out.print("[");
      printInc(root, 0);
      System.out.println("]");
    }
    
    private boolean isBalanced(Node n){
      return n == null || 
        isBalanced(n.left) &&
        isBalanced(n.right) &&
        Math.abs(maxDepth(n.left) - maxDepth(n.right)) <= 1;
    }
    
    private int printInc(Node n, int i){
      
      if(n.left != null){
        i = printInc(n.left, i);
      }
      
      System.out.print(n.data+", ");
      
      if(n.right != null){
        i = printInc(n.right, i);
      }
      
      return i;
    }
    
    private boolean leftRotate(Node n){
      if(n == null || n.right == null) return false;
      
      Node newNode = n.right;
      n.right = newNode.right;
      newNode.right = newNode.left;
      newNode.left = n.left;
      n.left = newNode;
      
      int tmp = n.data;
      n.data = newNode.data;
      newNode.data = tmp;
      return true;
    }
    
    private boolean rightRotate(Node n){
      if(n == null || n.left == null) return false;
      
      Node newNode = n.left;
      n.left = newNode.left;
      newNode.left = newNode.right;
      newNode.right = n.right;
      n.right = newNode;
      
      int tmp = n.data;
      n.data = newNode.data;
      newNode.data = tmp;
      return true;
    }
    
    private void balanceTree(Node root){
      Node p;
      int nodeCount;
      
      for(p=root, nodeCount=0; p != null; p=p.right, ++nodeCount){
        while(rightRotate(p));
      }
      for(int i=nodeCount/2; i>0; i /= 2){
        int k;
        for(p=root,  k=0; k<i; ++k, p=p.right){
          leftRotate(p);
        }
      }
    }
    
    private void reverse(Node n){
      
      Node tmp = n.left;
      n.left = n.right;
      n.right = tmp;
      
      if(n.left != null) reverse(n.left);
      if(n.right != null) reverse(n.right);
    }
    
    private Node[] toArray(){
      Node[] a = new Node[numNodes(root)];
      toArray(root, 0, a);
      return a;
    }
    
    private int toArray(Node n, int i, Node[] a){
      
      if(n.left != null){
        i = toArray(n.left, i, a);
      }
      
      a[i++] = n;
      
      if(n.right != null){
        i = toArray(n.right, i, a);
      }
      
      return i;
    }
    
    private void printTree(){
      final int maxLevel = maxDepth(root);
      Node[] nodes = {root};
      if(maxLevel < 7)
        printTree(nodes, 1, maxLevel);
    }
    
    private class Node{
      
      public int data;
      public Node left, right;
      
      public Node(int element){
        this(element, null, null);
      }
      
      public Node(int element, Node leftNode, Node rightNode){
        data = element;
        left = leftNode;
        right = rightNode;
      }
    }
    
    private void printTree(Node[] nodes, int level, int maxLevel){
      if(allNull(nodes) || level > maxLevel){
        return;
      }
      
      int floor = maxLevel - level;
      int edgeLines = (int) Math.pow(2, (Math.max(floor - 1, 0)));
      int firstSpaces = (int) Math.pow(2, floor) - 1;
      int betweenSpaces = (int) Math.pow(2, floor + 1) - 1;
      int index = 0;
      
      Node[] newNodes = new Node[nodes.length * 2];
      
      printSpaces(firstSpaces);
      
      for(Node n : nodes){
        if(n != null){
          System.out.print(n.data);
          newNodes[index++] = n.left;
          newNodes[index++] = n.right;
        }else{
          printSpaces(1);
          newNodes[index++] = null;
          newNodes[index++] = null;
        }
        printSpaces(betweenSpaces);
      }
      
      System.out.println();
      
      for(int i=1; i<=edgeLines; i++){
        for(int j=0; j<nodes.length; j++){
          
          printSpaces(firstSpaces - i);
          
          if(nodes[j] == null){
            printSpaces(edgeLines + edgeLines + i + 1);
            continue;
          }
          
          if(nodes[j].left != null){
            System.out.print("/");
          }else{
            printSpaces(1);
          }
          
          printSpaces(i + i - 1);
          
          if(nodes[j].right != null){
            System.out.print("\\");
          }else{
            printSpaces(1);
          }
          
          printSpaces(edgeLines + edgeLines - i);
        }
        System.out.println();
      }
      printTree(newNodes, level + 1, maxLevel);
    }
    
    private void printSpaces(int n){
      for(int i=0; i<n; i++){
        System.out.print(" ");
      }
    }
    
    private boolean allNull(Node[] nodes){
      for(Node n : nodes){
        if(n != null){
          return false;
        }
      }
      return true;
    }
  }
  
  
}
