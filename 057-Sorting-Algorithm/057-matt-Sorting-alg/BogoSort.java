public class BogoSort extends SortingAlg{
  
  public BogoSort(){
    super("Bogo Sort");
  }
  
  @Override
  protected void tsort(){
    while(!isSorted()){
      shuffle();
    }
  }
  
}
