
public class Matt_Count_Vowels_016 {
  
  
  public static void main(String[] args) { 
    String s = "ThE quick brown fox jumps over the lazy dOge";
    System.out.println("There are " + numVowels(s) + " vowels in the phrase \"" + s + "\"");
  }
  
  static int numVowels(String input){
    int vowels = 0;
    for(int i=0; i<input.length(); i++){
      switch(input.charAt(i)){
        case 'a': case 'A':
        case 'e': case 'E':
        case 'i': case 'I':
        case 'o': case 'O':
        case 'u': case 'U':
          vowels++;
        break;
        default: break;
      }
    }
    return vowels;
  }
  
}
