
public class Matt_Count_Vowels_016 {
  
  
  public static void main(String[] args) { 
    String s = "The quick brown fox jumps over the lazy dog";
    System.out.println("There are " + numVowels(s) + " vowels in the phrase \"" + s + "\"");
  }
  
  static int numVowels(String input){
    int vowels = 0;
    for(int i=0; i<input.length(); i++){
      switch(input.charAt(i)){
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u': vowels++;
        break;
        default: break;
      }
    }
    return vowels;
  }
  
}
