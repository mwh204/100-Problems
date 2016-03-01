import java.util.Arrays;

public class JavaSort extends SortingAlg{
  
  public JavaSort(){
    super("java.util.Arrays.sort()");
  }
  
  @Override
  protected void tsort(){
    Arrays.sort(list);
  }
  
}
