import java.util.Scanner;

public class ReverseString {

	public static void main(String[] args) {
		
		Scanner userInput = new Scanner(System.in);
		System.out.println("Type anything.");
		String input = userInput.nextLine();
		String output = ("");
		
		for (int i=0;i<input.length();i++){
			output = input.substring(i,i+1) + output;
		}
		
		System.out.println(output);
	}

}
