import java.util.Scanner;

public class TempConvert {

	public static void main(String[] args) {
		
		Scanner userInput = new Scanner(System.in);
		System.out.println("Enter the temperature you would like to convert, followed by the corresponding letter.\nExample : 32C");
		String answer = userInput.nextLine();
		Double temp = Double.parseDouble(answer.substring(0,answer.length()-1));;
		
		if (answer.charAt(answer.length()-1) == 'F'){
			System.out.println(answer + " = " + ((temp - 32) * 5/9) + "°C");
		}else if (answer.charAt(answer.length()-1) == 'C'){
			System.out.println(answer + " = " + (temp * 9/5 + 32) + "°F");
		}else{
			System.out.println("Invalid Temperature.");
		}
		
	}

}
