fn main() {
	hanoi(4, 1, 3);
}

fn hanoi(disks: i32, from: i32, to: i32) {
	if disks == 1 {
		println!("{} -> {}", from, to);	
	} else {
		let tmp = 6 - from - to;
		hanoi(disks-1, from, tmp);
		println!("{} -> {}", from, to);
		hanoi(disks-1, tmp, to);
	}
}
