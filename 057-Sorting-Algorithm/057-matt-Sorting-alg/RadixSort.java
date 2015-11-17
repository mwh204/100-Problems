public class RadixSort extends SortingAlg {
  
  public RadixSort(){
    super("Radix Sort");
  }
  
  @Override
  protected void tsort(){
    for(int shift = Integer.SIZE-1; shift >= 0; shift--){
      
      int[] tmp = new int[list.length];
      int j = 0;
      
      for(int i = 0; i<list.length; i++){
        boolean move = (list[i] << shift) >= 0;
        
        if(shift == 0 ? !move : move){
          tmp[j] = list[i];
          j++;
        }else{
          list[i-j] = list[i];
        }
      }
      
      for(int i=j; i<tmp.length; i++){
        tmp[i] = list[i-j];
      }
      
      list = tmp;
    }
  }
  
  
}
