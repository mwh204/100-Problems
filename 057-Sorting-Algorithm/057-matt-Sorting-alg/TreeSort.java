public class TreeSort extends SortingAlg{
  
  public TreeSort() { 
    super("Tree Sort");
  }
  
  @Override
  protected void tsort(){
    BST tree = new BST(list[0]);
    int a = 0;
    for(int i : list){
      tree.insert(tree.root, i);
    }
    while(a<list.length){
      list[a++] = tree.iterate(tree.root);
    }
  }
  
  private class BST{
    
    protected Node root;
    
    public BST(int element){
      root = new Node(element);
    }
    
    private Node insert(Node n, int e){
      if(n == null){
        return new Node(e);
      }
      if(e <  n.data){
        n.left = insert(n.left, e);
      }else{
        n.right = insert(n.right, e);
      }
      return n;
    }
    
    public int iterate(Node n){
      int r = 0;
      if(n != null){
        iterate(n.left);
        r = n.data;
        iterate(n.right);
      }
      return r;
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
