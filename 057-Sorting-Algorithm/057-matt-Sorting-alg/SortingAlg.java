import java.util.Arrays;
import java.util.concurrent.ThreadLocalRandom;

public class SortingAlg {
  
  public final int NUM_ELEMENTS = 3;
  protected int[] array;
  public String name = "none";
  
  public SortingAlg(String s){
    this();
    name = s;
  }
  
  public SortingAlg(){
    array = makeRandomArray();
  }
  
  public void sort(){
    long startTime = System.currentTimeMillis();
    tsort();
    long endTime = System.currentTimeMillis();
    System.out.println("Sorting "+ NUM_ELEMENTS+" elements using "+ name +" took "+(endTime-startTime)+" ms");
  }
  
  public String toString(){
    return Arrays.toString(array);
  }
  
  protected void tsort(){
    System.out.println("asd");
  }
  
  protected void swap(int p1, int p2){
    int temp = array[p1];
    array[p1] = array[p2];
    array[p2] = temp;
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
      sorted = array[i] > array[i-1];
    }
    return sorted;
  }
  
  private int randRange(int min, int max){
    return ThreadLocalRandom.current().nextInt(min, max);
  }
  
  private int[] makeRandomArray(){
    int[] array = new int[NUM_ELEMENTS];
    for(int i=0; i<NUM_ELEMENTS; i++){
      array[i] = randRange(0, Integer.MAX_VALUE-1);
    }
    return array;
  }
  
}
