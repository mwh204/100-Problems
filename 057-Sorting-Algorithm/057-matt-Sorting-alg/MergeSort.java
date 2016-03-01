public class MergeSort extends SortingAlg {
  
  public MergeSort(){
    super("Merge Sort");
  }
  
  @Override
  protected void tsort(){
    //mergeSort(list);
    iMerge(list);
  }
  
  public void mergeSort2(int[] list){
    int[] temp = new int[list.length];
    mergeSort(list, 0, list.length, temp);
  }
  
  private void mergeSort(int[] a, int start, int end, int[] temp){
    if(1 < end - start){
      int mid = start + (end - start)/2;
      
      mergeSort(a, start, mid, temp);
      mergeSort(a, mid, end, temp);
      
      merge(a, start, mid, end, temp);
    }
  }
  
  private void merge(int[] a, int start, int mid, int end, int[] temp){
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
  
  public void iMerge(int[] list){
    int[] temp = new int[list.length];
    
    for(int i=1; i<list.length; i *= 2){     
      for(int j=0; j<list.length; j += i*2){
        //System.out.println("merge("+j+", "+(j+i)+", "+Math.min(j+i*2, list.length)+")");
        merge(list, j, j + i, Math.min(j+i*2, list.length), temp);
      }
      //System.out.println();
    }
  }
  
}