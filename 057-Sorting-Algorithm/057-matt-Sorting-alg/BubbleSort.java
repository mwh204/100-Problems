public class BubbleSort extends SortingAlg{
  
  public BubbleSort(){
    super("Bubblesort");
  }
  
  @Override
  protected void tsort(){
    int last, stop = list.length-1;
    
    for(int i=0; i<list.length-1 && stop >= 0; i++){
      last = -1;
      for(int j=0; j<stop; j++){
        if(list[j] > list[j+1]){
          last = j;
          swap(j+1, j);
        }
      }
      stop = last;
    }
  }
  
}
