public class TreeSort extends SortingAlg{
  
  public TreeSort() { 
    super("Tree Sort");
  }
  
  @Override
  protected void tsort(){
    BST tree = new BST(list[0]);
    for(int i=1; i<list.length; i++){
      tree.insert(tree.root, list[i]);
    }
    tree.toArray(tree.root);
  }
  
  private class BST{
    
    protected Node root;
    
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
    
    private void toArray(Node n){
      toArray(n, 0);
    }
    
    private int toArray(Node n, int i){
      
      if(n.left != null){
        i = toArray(n.left, i);
      }
      
      list[i++] = n.data;
      
      if(n.right != null){
        i = toArray(n.right, i);
      }
      
      return i;
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
  }
}
