import java.util.Arrays;
import java.util.concurrent.ThreadLocalRandom;

public class SortingAlg {
  
  protected int[] list;
  public final int NUM_ELEMENTS = 25000;
  private final int MIN_VALUE = 0;
  private final int MAX_VALUE = Integer.MAX_VALUE-1;
  protected String name = "none";
  
  protected SortingAlg(String s){
    this();
    name = s;
  }
  
  private SortingAlg(){
    list = makeRandomArray();
  }
  
  public void sort(){
    long startTime = System.currentTimeMillis();
    tsort();
    long endTime = System.currentTimeMillis();
    System.out.println("Sorting "+ NUM_ELEMENTS+" elements using "+ name +" took "+(endTime-startTime)+" ms");
    System.out.println("The array is correctly sorted: " + isSorted());
    //System.out.println(this);
  }
  
  public String toString(){
    return Arrays.toString(list);
  }
  
  protected void tsort(){
    System.out.println("No sorting algorithm chosen (This Method should be overridden)");
  }
  
  protected void swap(int p1, int p2){
    int temp = list[p1];
    list[p1] = list[p2];
    list[p2] = temp;
  }
  
  protected void shuffle(){
    for(int i=NUM_ELEMENTS-1; i>0; i--){
      int j = randRange(0, i);
      swap(i, j);
    }
  }
  
  protected boolean isSorted(){
    boolean sorted = true;
    for(int i=1; sorted && i<NUM_ELEMENTS; i++){
      sorted = list[i] >= list[i-1];
    }
    return sorted;
  }
  
  private int randRange(int min, int max){
    return ThreadLocalRandom.current().nextInt(min, max);
  }
  
  private int[] makeRandomArray(){
    int[] array = new int[NUM_ELEMENTS];
    for(int i=0; i<NUM_ELEMENTS; i++){
      array[i] = randRange(MIN_VALUE, MAX_VALUE);
    }
    return array;
  }
  
}
