
public class Matt_count_words_017 {
  
  
  public static void main(String[] args) { 
    String sent = "The quick brown\t fox   jumps over the lazy     brown doge";
    System.out.println("Number of words in \""+sent+"\": "+ countWords(sent));
  }
  
  public static int countWords(String sentence){
    int count = 0;
    sentence = sentence.trim().replaceAll("\\s+", " "); //remove excess spaces
    for(int i=0; i<sentence.length(); i++){
      if(sentence.charAt(i) == ' '){
        count++;
      }
    }
    return count+1;
  }
  
}
