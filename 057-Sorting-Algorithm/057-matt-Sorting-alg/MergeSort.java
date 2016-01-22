public class MergeSort2 extends SortingAlg {
  
  public MergeSort2(){
    super("Merge Sort 2");
  }
  
  @Override
  protected void tsort(){
    mergeSort2(list);
  }
  
  public void mergeSort2(int[] list){
    int[] temp = new int[list.length];
    mergeSort2(list, 0, list.length, temp);
  }
  
  private void mergeSort2(int[] a, int start, int end, int[] temp){
    if(1 < end - start){
      int mid = start + (end - start)/2;
      
      mergeSort2(a, start, mid, temp);
      mergeSort2(a, mid, end, temp);
      
      merge(a, start, end, temp);
    }
  }
  
  private void merge(int[] a, int start, int end, int[] temp){
    int mid = start + (end - start)/2;
    int currL = start;
    int currR = mid;
    
    for(int currT=start; currT<end; currT++){
      if(currL < mid && (currR >= end || a[currL] < a[currR])){
        temp[currT] = a[currL++];
      }else{
        temp[currT] = a[currR++];
      }
    }
    for(int currT=start; currT<end; currT++){
      a[currT] = temp[currT];
    }
  }
  
}