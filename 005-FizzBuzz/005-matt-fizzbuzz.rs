fn main() {
	for i in 1..101 {
		fizzbuzz(i);
	}
}

fn fizzbuzz(x: i32) {
	match (x % 3, x % 5) {
		(0, 0) => println!("fizzbuzz"),
		(_, 0) => println!("buzz"),
		(0, _) => println!("fizz"),
		_  => println!("{}", x),
	}
}
