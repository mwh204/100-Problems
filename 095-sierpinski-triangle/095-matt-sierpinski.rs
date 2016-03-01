fn main() {
	sierpinski(4);
}

fn sierpinski(level: u32) {
	let lim = 2u32.pow(level);	
	for y in (0..lim).rev() {
		for _ in 0..y {
			print!(" ");
		}
		for x in 0..lim-y {
			if x & y == 0 {
				print!("* ");
			} else {
				print!("  ");
			}
		}
		println!("");
	}
}
