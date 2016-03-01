import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class TextGen2 {
  
  final int SENT_MIN_LEN = 5;
  final int SENT_MAX_LEN = 15;

  public static Markov2 mk;
  
  public TextGen2(String filename){
    mk = new Markov2();
    makeDictionary(filename);
  }
  
  public String generateSentence(){
    String sent = "", next = "zyzyzx";
    int len = SENT_MIN_LEN + (int)(Math.random() * (SENT_MAX_LEN - SENT_MIN_LEN + 1));
    for(int i=0; i<len; i++){
      next = mk.nextWord(next);
      sent += next + " ";
    }
    return sent;
  }
  
  private void makeDictionary(String filename){
    BufferedReader reader;
    String line;
    try{
      reader = new BufferedReader(new FileReader(filename));
      
      line = reader.readLine();
      while(line != null){
        sentenceToMarkov(line);
        line = reader.readLine();
      }
      
      reader.close();
    }catch (IOException ioe){
      System.out.println(ioe.getMessage());
    }
    System.out.println("Finished making dictionary");
  }
  
  private void sentenceToMarkov(String sentence){
    sentence = sentence.trim().replaceAll("\\s+", " "); //remove excess spaces
    String[] expl = sentence.split(" ");
    for(String s : expl){
      mk.addWordf(s);
    }
  }
  
}
