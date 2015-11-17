
public class InsertSort extends SortingAlg {
  
  public InsertSort(){
    super("Insertion Sort");
  }
  
  @Override
  protected void tsort(){
    int i, j, element;
    for(i=0; i<NUM_ELEMENTS; i++){
      element = list[i];
      for(j=i; j>0 && list[j-1]>element; j--){
        list[j] = list[j-1];
      }
      list[j] = element;
    }
  }
}
