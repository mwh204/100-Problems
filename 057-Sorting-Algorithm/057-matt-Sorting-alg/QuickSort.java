public class QuickSort extends SortingAlg {
  
  public QuickSort() { 
    super("Quick Sort");
  }
  
  @Override
  protected void tsort(){
    quickSort();
  }
  
  private void quickSort(){
    quickSort(0, list.length-1);
  }
  
  private void quickSort(int left, int right){
    int index = partition(left, right);
    if(left < index-1){
      quickSort(left, index-1);
    }
    if(right > index){
      quickSort(index, right);
    }
  }
  
  private int partition(int left, int right){
    int pivot = list[(left+right)/2];
    
    while(left <= right){
      
      while(list[left] < pivot){
        left++;
      }
      
      while(list[right] > pivot){
        right--;
      }
      
      if(left <= right){
        swap(left, right);
        left++;
        right--;
      }
    }
    return left;
  }

}
