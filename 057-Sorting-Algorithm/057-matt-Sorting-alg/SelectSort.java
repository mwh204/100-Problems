public class SelectSort extends SortingAlg {
  
  public SelectSort(){
    super("Selection Sort");
  }
  
  @Override
  protected void tsort(){
    int posMax;
    for(int i=0; i<NUM_ELEMENTS; i++){
      posMax = 0;
      for(int j=posMax+1; j<NUM_ELEMENTS-i; j++){
        if(list[j] > list[posMax]){
          posMax = j;
        }
      }
      swap(posMax, NUM_ELEMENTS-i-1);
    }
  }
  
}
