import java.util.ArrayList;
import java.util.HashMap;
import java.util.*;

public class Markov2 {
  
  final HashMap<String, Integer> map;
  final List<MarkovRow> next;
  private String lastWord;
  
  public Markov2(){
    map = new HashMap<String, Integer>();
    next = new ArrayList<MarkovRow>();
    lastWord = "";
  }
  
  public String toString(){
    String ret = "";
    for(Map.Entry<String, Integer> m : map.entrySet()){
      ret +=  m.getValue() +" "+ m.getKey() + "\t" + next.get((Integer)m.getValue()) + "\n";
    }
    return ret;
  }
  
  public void addWord(String word){ 
    if(!map.containsKey(word)){
      map.put(word, map.size());
      next.add(new MarkovRow());
    }
    if(map.containsKey(lastWord)){
      next.get(map.get(lastWord)).next.add(map.get(word));
    }
    lastWord = word;
  }
  private class MarkovRow{
    public ArrayList<Integer> next;
    
    public MarkovRow(){
      next = new ArrayList<Integer>();
    }
    
    public String toString(){
      return next.toString();
    }
  }
}//Markov  