import java.util.Scanner;

public class Matt_rpn_calc_055 {
  
  static final int STACK_SIZE = 4;
  static int mem = 0;
      
  public static void main(String[] args) { 
    rpnCalc();
  }
  
  public static void rpnCalc(){
    String s;
    int num;
    int[] stack = new int[STACK_SIZE];
    while(true){
      printStack(stack);
      do{ s = getInput(); }while(s.length() < 1);
      if(isNumeric(s)){
        num = Integer.parseInt(s);
        stack = push(stack, num);
      }else{
        stack = eval(stack, s);
      }
    }
  }
  
  public static int[] eval(int[] stack, String in){
    char c = in.charAt(0);
    switch(c){
      case '+':  /*addition*/
        stack[0] = stack[1] + stack[0];
        break;
      case '-':  /*subtraction*/
        stack[0] = stack[1] - stack[0];
        break;
      case '*':  /*multiplication*/
        stack[0] = stack[1] * stack[0];
        break;
      case '/':  /*integer division*/
        stack[0] = stack[1] / stack[0];
        break;
      case '%':  /*modulus*/
        stack[0] = stack[1] % stack[0];
        break;
      case '^': /*exponentiation*/
        stack[0] = (int)Math.pow(stack[1], stack[0]);
        break;
      case 'p':
      case 'P': /*pop*/
        stack = pop(stack);
        break;
      case 's':
      case 'S': /*swap*/
        int tmp = stack[0];
        stack[0] = stack[1];
        stack[1] = tmp;
        break;
      case 'm':
      case 'M': /*memory save*/
        mem = stack[0];
        System.out.println("Saved "+mem+" to memory");
        break;
      case 'r': 
      case 'R': /*memory recall*/
        stack = push(stack, mem);
        break;
      case 'q':
      case 'Q': /*quit*/
        System.exit(0);
        break;
      default: 
        System.out.println("Unknown operation");
        break;
    }
    return stack;
  }
  
  public static boolean isNumeric(String in){
    boolean a = true;
    char c;
    int i=0;
    if(in.charAt(i) == '-' && in.length() > 1) i = 1;
    for(; i<in.length(); i++){
      c = in.charAt(i);
      a = a && (c >= '0' && c <= '9');
    }
    return a;
  }
  
  public static int[] pop(int[] stack){
    for(int i=1; i<STACK_SIZE; i++){
      stack[i-1] = stack[i];
    }
    stack[STACK_SIZE-1] = 0;
    return stack;
  }
  
  public static int[] push(int[] stack, int val){
    for(int i=STACK_SIZE-1; i>=1; i--){
      stack[i] = stack[i-1];
    }
    stack[0] = val;
    return stack;
  }
  
  public static String getInput(){
    Scanner userInput = new Scanner(System.in);
    String s = userInput.nextLine();
    userInput.close();
    return s;
  }

  public static void printStack(int[] stack){
    for(int i=STACK_SIZE-1; i>=0; i--){
      System.out.println("\t"+stack[i]);
    }
    System.out.println("------------\n");
  }
  
}
