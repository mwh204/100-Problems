public class HeapSort extends SortingAlg{
  
  public HeapSort() { 
    super("Heap Sort");
  }
  
  @Override
  protected void tsort(){
    heapify(list, list.length);
    for(int i=list.length-1; i>0; i--){
      swap(0, i);
      siftDown(list, 0, i-1);
    }
  }
  
  private void heapify(int[] a, int count){
    for(int i=(count-2)/2; i>=0; i--){
      siftDown(a, i, count-1);
    }
  }
  
  private void siftDown(int[] a, int start, int end){
    int child, root = start;
    while( (child = (root*2)+1) <= end){
      if(child+1 <= end && a[child] < a[child+1]){
        child++;
      }
      if(a[root] < a[child]){
        swap(root, child);
        root = child;
      }else{
        return;
      }
    }
  }
  
}
