public class ShellSort extends SortingAlg {
  
  final int GAP = 3;
  
  public ShellSort() { 
    super("Shell sort");
  }
  
  @Override
  protected void tsort(){
    int h = 1;
    while(h < list.length){
      h = (GAP*h) + 1;
    }
    while(h > 0){
      for(int i=h; i<list.length; i++){
        for(int j=i; j>=h && list[j] < list[j-h]; j -= h){
          swap(j, j-h);
        }
      }
      h = h/GAP;
    }
  }
  
}
