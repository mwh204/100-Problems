public class MergeSort extends SortingAlg{
  
  public MergeSort() { 
    super("Merge Sort");
  }
  
  @Override
  protected void tsort(){
    mergeSort(list);
  }
  
  private void mergeSort(int[] array){
    if(array.length < 2){
      return;
    }
    
    int mid = array.length/2;
    int leftSize = mid;
    int rightSize = array.length - mid;
    
    int[] left = new int[leftSize];
    int[] right = new int[rightSize];
    for(int i=0; i<leftSize; i++){
      left[i] = array[i];
    }
    for(int i=mid; i<array.length; i++){
      right[i-mid] = array[i];
    }
    mergeSort(left);
    mergeSort(right);
    merge(left, right, array);
  }
  
  private void merge(int[] left, int[] right, int[] result){
    int i=0, j=0, k=0;
    while(i<left.length && j < right.length){
      if(left[i] <= right[j]){
        result[k++] = left[i++];
      }else{
        result[k++] = right[j++];
      }
    }
    while(i < left.length){
      result[k++] = left[i++];
    }
    while(j < right.length){
      result[k++] = right[j++];
    }
  }
  
}
