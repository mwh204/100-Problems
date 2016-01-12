import java.util.Arrays;
import java.util.concurrent.ThreadLocalRandom;

public class SortingAlg {
  
  protected int[] list;
  protected boolean sorted;
  protected String name = "none";
  
  public final int NUM_ELEMENTS = 100000;
  private final int MIN_VALUE = 0;
  private final int MAX_VALUE = Integer.MAX_VALUE-1;
  private final int NUM_NEARLY = (int)(0.25*NUM_ELEMENTS);
  private final int NUM_UNIQUE = (int)(0.2*NUM_ELEMENTS);
  
  protected SortingAlg(String s){
    this();
    name = s;
  }
  
  private SortingAlg(){
    makeRandomArray();
    sorted = false;
  }
  
  public String toString(){
    String r = "";
    if(list.length < 30){
      r = Arrays.toString(list);
    }
    return r;
  }
  
  public void sort(){
    long startTime = System.currentTimeMillis();
    tsort();
    long endTime = System.currentTimeMillis();
    long elapsed = endTime-startTime;
    System.out.println("Sorting "+ NUM_ELEMENTS+" elements using "+ name +" took "+elapsed+" ms ("+(elapsed/1000)/60+"m"+(elapsed/1000)+"s)");
    System.out.println("The array is correctly sorted: " + ((sorted = isSorted())? "true" : "FALSE ***************"));
    //System.out.println(this+"\n");
  }
  
  public void allSort(){
    
    System.out.println("\nRandom Array:");
    makeRandomArray();
    sort();
    
    System.out.println("\nReverse Array:");
    if(!sorted) Arrays.sort(list);
    reverse();
    sort();
    
    System.out.println("\nNearly Sorted Array:");
    if(!sorted) Arrays.sort(list);
    nearly();
    sort();
    
    System.out.println("\nFew Unique Array:");
    if(!sorted) Arrays.sort(list);
    few_unique();
    sort();
    System.out.print("\n\n==========================================\n\n");
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
    for(int i=0; i<=list.length-2; i++){
      int j = randRange(i, list.length);
      swap(i, j);
    }
  }
  
  private void makeRandomArray(){
    list = new int[NUM_ELEMENTS];
    for(int i=0; i<list.length; i++){
      list[i] = randRange(MIN_VALUE, MAX_VALUE);
    }
  }
  
  protected void reverse(){
    for(int i=0; i<list.length/2; i++){
      swap(i, list.length-i-1);
    }
  }
  
  protected void nearly(){
    int j = 1;
    for(int i = 0; i<NUM_NEARLY; i++){
      j = j * (randRange(50, 179)) % list.length;
      swap(j, randRange(0, list.length));
    }
  }
  
  protected void few_unique(){
    int[] u = new int[NUM_UNIQUE];
    for(int i=0; i<u.length; i++){
      u[i] = randRange(MIN_VALUE, MAX_VALUE);
    }
    for(int i=0; i<list.length; i++){
      list[i] = u[i % u.length];
    }
    shuffle();
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
  
}
