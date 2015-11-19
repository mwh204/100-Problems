import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Markov2 {
  
  private final HashMap<String, MarkovRow> map;
  private String lastWord;
  
  public Markov2(){
    map = new HashMap<String, MarkovRow>();
    lastWord = "";
  }
  
  public String toString(){
    String ret = "";
    for(Map.Entry<String, MarkovRow> m : map.entrySet()){
      ret += m.getValue().ind +"\t" + m.getKey() + "\t" + m.getValue() + "\n";
    }
    return ret;
  }
  
  public void addWord(String word){ 
    if(!map.containsKey(word)){
      map.put(word, new MarkovRow(map.size(), word));
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
  
  public void addWordf(String word){
    addWord(word.toLowerCase().replaceAll("[^a-z\\s'-]", ""));
  }
  
  public String nextWord(String prev){
    String next = "";
    double rand = Math.random();
    double prob;
    
    if(map.containsKey(prev) && map.get(prev).list.size() > 0){
      prob = getProbability(prev);
      for(int i=0; i<map.get(prev).list.size(); i++){
        if(rand < prob){
          return getWord(map.get(prev).list.get(i).index);
        }
        rand -= prob;
      }
    }else{
      next = getWord((int)(Math.random()*map.size()));
    }
    return next;
  }
  
  private double getProbability(String word){
    return (double)map.get(word).list.get( map.get(word).indexOfWI(map.get(word).ind) ).weight / map.get(word).list.size();
  }
  
  public int indexOf(String word){
    int i = -1, j=0;
    for(Map.Entry<String, MarkovRow> m : map.entrySet()){
      j = m.getValue().ind;
      if(m.getKey().equals(word)){
        i=j;
        break;
      }
    }
    return i;
  }
  
  public String getWord(int index){
    String ret = "";
    for(Map.Entry<String, MarkovRow> m : map.entrySet()){
      if(m.getValue().ind == index){
        ret = m.getValue().word;
        break;
      }
    }
    return ret;
  }
  
  private class MarkovRow{
    
    private ArrayList<WordIndex> list;
    protected int ind;
    protected String word;
    
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
      int i;
      for(i=0; i<list.size(); i++){
        if(list.get(i).index == ind) break;
      }
      return i-1>0? i-1:0;
    }
    
    public MarkovRow(int index, String s){
      ind = index;
      word = s;
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