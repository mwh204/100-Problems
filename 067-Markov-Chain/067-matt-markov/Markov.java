import java.util.ArrayList;

public class Markov {
  
  final ArrayList<MarkovRow> rows;
  private String lastWord;
  
  public Markov(){
    rows = new ArrayList<MarkovRow>();
    lastWord = "";
  }
  
  public String toString(){
    String ret = "";
    for(int i=0; i<rows.size(); i++){
      ret += rows.get(i) + "\n";
    }
    return ret;
  }
  
  private void appendZeroToAll(){
    for(MarkovRow m : rows){
      while(m.nextState.size() < rows.size()){
        m.nextState.add(0);
      }
    }
  }
  
  private int getIndex(String word){
    int ind = -1;
    for(int i=0; i<rows.size(); i++){
      if(word.equals(rows.get(i).state)){
        ind = i;
      }
    }
    return ind;
  }
  
  public void addWord(String word){
    int ind = getIndex(word);
    
    if(ind == -1){//new word
      rows.add(new MarkovRow(word));
      appendZeroToAll();
    }
    
    if((ind=getIndex(lastWord)) >= 0){
      int i = getIndex(lastWord);
      rows.get(i).nextState.set(getIndex(word), rows.get(i).nextState.get(getIndex(word)) + 1 );
    }
    lastWord = word;
  }
  
  private class MarkovRow{
    public String state;
    public final ArrayList<Integer> nextState;
    
    public MarkovRow(String word){
      state = word;
      nextState = new ArrayList<Integer>();
    }
    
    public String toString(){
      return state + "\t" + nextState.toString();
    }
  }//MarkovRow
  
}//Markov  