public class SelectSort extends SortingAlg {
  
  public SelectSort(){
    super("Selection Sort");
  }
  
  @Override
  protected void tsort(){
    int posMax;
    for(int i=0; i<list.length; i++){
      posMax = 0;
      for(int j=posMax+1; j<list.length-i; j++){
        if(list[j] > list[posMax]){
          posMax = j;
        }
      }
      swap(posMax, list.length-i-1);
    }
  }
  
}
