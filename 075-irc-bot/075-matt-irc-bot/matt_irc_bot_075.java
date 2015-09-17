import java.io.File;
import java.io.IOException;
import java.util.ArrayList; 
import java.util.List;
import java.util.Scanner;

public class matt_irc_bot_075 {
  
  static final int NUM_ITEMS_ARRAY = 50;  
  static final int INITIAL_ITEMS_ARRAYLIST = 50; //default is 10
  
  static final int SENT_MIN_LEN = 5;
  static final int SENT_MAX_LEN = 15;
  
  static final String FILENAME = "v.txt";
  static final String EOL = "QQEOLQQ";
  
  public static void main(String[] args) { 
    
    final ArrayList<String[]> dict = new ArrayList<String[]>(INITIAL_ITEMS_ARRAYLIST);
    final ArrayList<String> words = new ArrayList<String>(INITIAL_ITEMS_ARRAYLIST); 
    
    int exit = 0;
    
    try{
      makeDictionary(dict, words);
    } catch(IOException e){
      System.out.println("IO error");
    }
    
    try{
      do{
        exit = System.in.read();
        System.out.println(generateSentence(dict, words));
      }while(exit == 10);
    } catch(Exception e){
      System.out.println("Unable to read");
    }
    
    /* 
     dumpArrayList(dict);
     //*/
  }//main
  
  static String generateSentence(ArrayList<String[]> dict, ArrayList<String> words){
    int i;
    String currentWord = words.get(randInt(0, words.size()));
    String nextWord = "";
    String sentence = "";
    for(int j=0; j<=SENT_MAX_LEN; j++){
      if(currentWord.equals(EOL)) break;
      i = words.indexOf(currentWord);
      if(j<SENT_MIN_LEN){
        do{
          nextWord = dict.get(i)[randInt(1, numEle(dict, i))-1];
        }while(currentWord.equals(nextWord) && !nextWord.equals(EOL));
      }else{
        do{
          nextWord = dict.get(i)[randInt(1, numEle(dict, i))-1];
        }while(currentWord.equals(nextWord));
      }
      sentence += currentWord + " ";
      currentWord = nextWord;
      
    }
    return sentence;
  }//generateSentence
  
  static void makeDictionary(ArrayList<String[]> dict, ArrayList<String> words) throws IOException {
    String a = "";
    String b = "";
    String line = "";
    int i = 0;
    int index = 0;
    
    Scanner inFile1 = new Scanner(new File(FILENAME));
    
    
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
      System.out.println("Finished analyzing text");
    }//makeDictionary
    
    
    
    static int randInt(int min, int max){
      return (int)(Math.random() * ((max-min)+1) + min);
    }
    
    static int numEle(ArrayList<String[]> list, int index){
      int i = 1;
      if(index>=list.size()) index = list.size()-1;
      while(i<NUM_ITEMS_ARRAY && list.get(index)[i] != null){ 
        i++;
      }
      return i>=NUM_ITEMS_ARRAY? NUM_ITEMS_ARRAY-1 : i;
    }//numEle
    
    static void dumpArrayList(ArrayList<String[]> list){
      for(int i=0; i<list.size(); i++){
        for(int j=0; j<numEle(list, i); j++){
          System.out.print(list.get(i)[j]+" ");
        }
        System.out.println();
      }
    }//dumpArrayList
    
  }