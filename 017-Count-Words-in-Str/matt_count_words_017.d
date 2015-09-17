import std.stdio;

void main(){
	string str;
	write("Enter a Sentence or Paragraph: ");
	readf("%s\n", &str);
	writeln("Number of Words: ", countWords(str));
}

int countWords(string inputStr){
	uint numWords = 0;
	foreach(c; inputStr){
		if(c==' '){
			numWords++;
		}
	}
	return numWords+1;
}
