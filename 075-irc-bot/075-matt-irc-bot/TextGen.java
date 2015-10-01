/*Text generation using pseudo markov chains*/

import java.io.File;
import java.io.IOException;
import java.util.ArrayList; 
import java.util.Scanner;

public class TextGen {
  
  static final int NUM_ITEMS_ARRAY = 51;  
  static final int INITIAL_ITEMS_ARRAYLIST = 50; //default is 10
  
  final int SENT_MIN_LEN = 5;
  final int SENT_MAX_LEN = 15;

  private final String EOL = "QQEOLQQ";
  
  
  final ArrayList<String[]> dict;
  final ArrayList<String> words;
  
    public TextGen(String filename){
    dict = new ArrayList<String[]>(INITIAL_ITEMS_ARRAYLIST);
    words = new ArrayList<String>(INITIAL_ITEMS_ARRAYLIST); 
    
   try{
      makeDictionary(dict, words, filename);
   } catch(IOException e){
     System.out.println("IO error");
   }
   
  }
  
  /*
   public static void main(String[] args) { 
   
   final ArrayList<String[]> dict = new ArrayList<String[]>(INITIAL_ITEMS_ARRAYLIST);
   final ArrayList<String> words = new ArrayList<String>(INITIAL_ITEMS_ARRAYLIST); 
   
   int exit = 0;
   String s = "";
   
   try{
   makeDictionary(dict, words);
   } catch(IOException e){
   System.out.println("IO error");
   }
   
   try{
   do{
   exit = System.in.read();
   do{
   s = generateSentence(dict, words);
   }while(countWords(s) < SENT_MIN_LEN);
   System.out.println(s);
   }while(exit == 10);
   } catch(Exception e){
   System.out.println("Unable to read");
   }
   
   /* 
   dumpArrayList(dict);
   
   }//main
   */  
  
  public String generateSentence(ArrayList<String[]> dict, ArrayList<String> words){
    int i;
    String currentWord = words.get(randInt(0, words.size()));
    String nextWord = "";
    String sentence = "";
    for(int j=0; j<=SENT_MAX_LEN; j++){
      if(currentWord.equals(EOL)) break;
      i = words.indexOf(currentWord);
      do{
        nextWord = dict.get(i)[randInt(1, numEle(dict, i))-1];
      }while(currentWord.equals(nextWord) && !nextWord.equals(EOL));
      sentence += currentWord + " ";
      currentWord = nextWord;
      
    }//for
    return sentence;
  }//generateSentence
  
  public void makeDictionary(ArrayList<String[]> dict, ArrayList<String> words, String filename) throws IOException {
    String a = "";
    String b = "";
    String line = "";
    int i = 0;
    int index = 0;
    
    Scanner inFile1 = new Scanner(new File(filename));
    
    
    while (inFile1.hasNextLine()) {
      do{
        line = inFile1.nextLine();
      }while(line.trim().isEmpty()); //line = inFile1.nextLine();
      Scanner lineScan = new Scanner(line);
      a = lineScan.next().toLowerCase();
      while(lineScan.hasNext()){
        b = lineScan.next().toLowerCase();
        i = words.indexOf(a);
        if( i == -1){ //new word
          words.add(a);
          dict.add(new String[NUM_ITEMS_ARRAY]);
          dict.get(index)[0] = a; 
          if(numEle(dict, index)-1 < NUM_ITEMS_ARRAY){
            dict.get(index)[numEle(dict, index)] = b;
          } else{
            dict.get(index)[randInt(1, NUM_ITEMS_ARRAY-1)] = b;
          }
          index++;
        } else { //same word
          if(numEle(dict, index)-1 < NUM_ITEMS_ARRAY){
            dict.get(i)[numEle(dict, i)] = b; 
          } else {
            dict.get(i)[randInt(1, NUM_ITEMS_ARRAY-1)] = b;
          }
        }
        a = b;
      }//while(line) 
      //System.out.println(a);
      
      i = words.indexOf(a);
      if( i == -1){ //new word
        words.add(a);
        dict.add(new String[NUM_ITEMS_ARRAY]);
        dict.get(index)[0] = a; 
        if(numEle(dict, index)-1 < NUM_ITEMS_ARRAY){
          dict.get(index)[numEle(dict, index)] = EOL;
        } else{
          dict.get(index)[randInt(1, NUM_ITEMS_ARRAY-1)] = EOL;
        }
        index++;
      } else { //same word
        if(numEle(dict, index)-1 < NUM_ITEMS_ARRAY){
          dict.get(i)[numEle(dict, i)] = EOL; 
        } else {
          dict.get(i)[randInt(1, NUM_ITEMS_ARRAY-1)] = EOL;
        }
      }
      
      lineScan.close();
    }//while(file)
    inFile1.close();
    System.out.println("TextGen: Finished analyzing text");
  }//makeDictionary
  
  public int countWords(String sentence){
    int count = 0;
    sentence =  sentence.trim().replaceAll(" +", " ");
    for(int i=0; i<sentence.length(); i++){
      if(sentence.charAt(i) == ' '){
        count++;
      }
    }
    return count+1;
  }
  
  public int randInt(int min, int max){
    return (int)(Math.random() * ((max-min)+1) + min);
  }//randInt
  
  public int numEle(ArrayList<String[]> list, int index){
    int i = 1;
    if(index>=list.size()) index = list.size()-1;
    while(i<NUM_ITEMS_ARRAY && list.get(index)[i] != null){ 
      i++;
    }
    return i>=NUM_ITEMS_ARRAY? NUM_ITEMS_ARRAY-1 : i;
  }//numEle
  
  public void dumpArrayList(ArrayList<String[]> list){
    for(int i=0; i<list.size(); i++){
      for(int j=0; j<numEle(list, i); j++){
        System.out.print(list.get(i)[j]+" ");
      }
      System.out.println();
    }
  }//dumpArrayList
  
}