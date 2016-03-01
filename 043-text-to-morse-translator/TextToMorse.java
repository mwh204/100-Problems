import java.io.*;
import java.util.Scanner;

public class EncryptionTesting {

	public static void main(String[] args) throws FileNotFoundException {
		
		String fileName1 = "morsecode.txt";
		String fileName2 = "characters.txt";
		String fileName3 = "text.txt";
		Scanner input1 = new Scanner(new File(fileName1));
		Scanner input2 = new Scanner(new File(fileName2));
		Scanner input3 = new Scanner(new File(fileName3));

		String[] characters = new String[59];
		String[] morsecode = new String[59];
		char current;
		
		Scanner userInput = new Scanner(System.in);
		String text = "";
		String output = "";
		
		while (input3.hasNextLine()){
			text = text + input3.nextLine().toUpperCase() + "¶";
		}

		for (int i=0;i<59;i++){
			morsecode[i] = input1.nextLine();
			characters[i] = input2.nextLine();
		}
			
		for (int i=0;i<text.length();i++){
			for (int j=0;j<characters.length;j++){
				if (text.charAt(i) == '¶'){
					System.out.println(output);
					output = "";
					break;
				}
				if (text.charAt(i) == ' '){
					output = output + "/ ";
					break;
				}
				if (text.charAt(i) == characters[j].charAt(0)){
					output = output + morsecode[j] + " ";
				}
				
			}
		}
		
		System.out.println(output);
		
	}

}
