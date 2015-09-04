import std.stdio, std.math;

void main(){
	int[] d = [0,2,1,5,6,1,23,6,7,1];
	writeln("The largest number is at position:", posOfLargestNum(d));
}

uint posOfLargestNum(int[] arr){
	int i,j,max;
	for(i=0;i<arr.length; i++){
		if(arr[i]>max){
			j=i;
			max = arr[i];
		}
	}
	return j;
}
