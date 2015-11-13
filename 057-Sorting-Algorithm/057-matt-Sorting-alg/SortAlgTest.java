public class SortAlgTest {
  
  public static void main(String[] args) { 
    SortingAlg x;
    
    x = new BubbleSort();
    x.sort();
    
    x = new SelectSort();
    x.sort();
    
    x = new InsertSort();
    x.sort();
  }
  
}
