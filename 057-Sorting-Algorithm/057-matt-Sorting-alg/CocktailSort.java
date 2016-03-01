
public class CocktailSort extends SortingAlg {
  
  public CocktailSort() { 
    super("Cocktail Sort");
  }
  
  @Override
  protected void tsort(){
    
    boolean swapped = true;
    
    for(int count=0; swapped; count++){
      
      swapped = false;
      for(int i=count; i<list.length-count-1; i++){
        if(list[i] > list[i+1]){
          swap(i, i+1);
          swapped = true;
        }
      }
      
      if(!swapped){
        break;
      }

      for(int i=list.length-count-1; i>count; i--){
        if(list[i] < list[i-1]){
          swap(i, i-1);
          swapped = true;
        }
      }    
    }
  } 

}
