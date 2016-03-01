public class matt_reverse_string_015 {
  
  
  public static void main(String[] args) { 
    System.out.println(reverseStr("ayy lmao"));
  }
  
  public static String reverseStr(String in){
    String out = "";
    for(int i=in.length()-1; i>=0; i--){
      out += in.charAt(i);
    }
    return out;
  }
  
}
