public class BogoSort extends SortingAlg{
  
  public BogoSort(){
    super("BogoSort");
  }
  
  @Override
  protected void tsort(){
    while(!isSorted()){
      shuffle();
    }
  }
  
}
