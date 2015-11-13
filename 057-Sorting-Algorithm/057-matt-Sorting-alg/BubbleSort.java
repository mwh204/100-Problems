public class BubbleSort extends SortingAlg{
  
  public BubbleSort(){
    super("Bubblesort");
  }
  
  @Override
  protected void tsort(){
    for(int i=0; i<NUM_ELEMENTS; i++){
      for(int j=0; j<NUM_ELEMENTS-1; j++){
        if(array[i] < array[j]){
          swap(i, j);
        }
      }
    }
  }
  
}
