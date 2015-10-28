import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Markov2 {
  
  final HashMap<String, MarkovRow> map;
  private String lastWord;
  
  public Markov2(){
    map = new HashMap<String, MarkovRow>();
    lastWord = "";
  }
  
  public String toString(){
    String ret = "";
    for(Map.Entry<String, MarkovRow> m : map.entrySet()){
      ret += m.getValue().ind +" "+ m.getKey() + "\t" + m.getValue() + "\n";
    }
    return ret;
  }
  
  public void addWord(String word){ 
    if(!map.containsKey(word)){
      map.put(word, new MarkovRow(map.size()));
    }
    
    if(map.containsKey(lastWord)){
      if(map.get(lastWord).containsIndex(map.get(word).ind)){
        map.get(lastWord).incWeight(map.get(lastWord).indexOfWI(map.get(word).ind));
      }else{
        map.get(lastWord).addWordIndex(map.get(word).ind);
      }
    }
    lastWord = word;
  }
  
  private class MarkovRow{
    
    public ArrayList<WordIndex> list;
    protected int ind;
    
    public void incWeight(int index){
      list.get(index).incWeight();
    }
    
    public void addWordIndex(int index){
      list.add(new WordIndex(index));
    }
    
    public boolean containsIndex(int index){
      for(WordIndex wi : list){
        if(wi.index == index){
          return true;
        }
      }
      return false;
    }
    
    public int indexOfWI(int ind){
      int i = -1;
      for(i=0; i<list.size(); i++){
        if(list.get(i).index == ind) break;
      }
      return i;
    }
    
    public MarkovRow(int index){
      ind = index;
      list = new ArrayList<WordIndex>();
    }
    
    public String toString(){
      return list.toString();
    }
    
    private class WordIndex{
      private int index;
      private int weight;
      
      public WordIndex(int ind){
        index = ind;
        weight = 1;
      }
      
      public String toString(){
        return index+":"+weight;
      }
      
      public void incWeight(){
        weight++;
      }
    }//WordIndex
    
  }//MarkovRow
  
}//Markov  