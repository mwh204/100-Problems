fn main() {
	for i in 0..93 {
		println!("{}:\t{}", i, fibonacci(i));
	}
}

fn fibonacci(mut x: u32) -> u64 {
	let mut a: u64 = 1;
	let mut b: u64 = 0;
	let mut p: u64 = 0;
	let mut q: u64 = 1;

	while x > 0 {
		if x%2 == 0 {
			let pp: u64 = p*p + q*q;
			q = 2*p*q + q * q;
			p = pp;
			x /= 2;
		} else {
			let ap: u64 = b*q + a*q + a*p;
			b = b*p + a*q;
			a = ap;
			x -= 1;
		}
	}
	b
}
