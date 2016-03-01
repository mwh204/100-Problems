
public class Matt_markov_067 {
  
  public static void main(String[] args) { 
    Markov mk = new Markov();
    sentenceToMarkov(mk, "I said and but he said I said but but he was wrong and I said so");
    System.out.println(mk);
  }
  
  public static void sentenceToMarkov(Markov mk, String sentence){
    sentence = sentence.trim().replaceAll(" +", " "); //remove excess spaces
    String[] expl = sentence.split(" ");
    for(String s : expl){
      mk.addWord(s);
    }
  }
  
}
