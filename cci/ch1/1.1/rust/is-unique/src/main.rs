fn is_unique_slow(s: &str) -> bool {
    for (i, c1) in s.chars().enumerate() {
        for (j, c2) in s.chars().enumerate() {
            if i == j {
                continue;
            }
            if c1 == c2 {
                return false;
            }
        }
    }
    true
}

fn main() {
    println!("Running...");

    assert!(is_unique_slow("qwer1234"));
    assert!(!is_unique_slow("qwer1234"));
}
