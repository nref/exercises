use std::collections::HashMap;

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

fn is_unique_sorted(s: &str) -> bool {
    let mut chars: Vec<char> = s.chars().collect();
    chars.sort();

    // dbg!(&mut chars);

    for i in 0..s.len() - 1 {
        if chars[i] == chars[i + 1] {
            return false;
        }
    }
    true
}

fn is_unique_hashmap(s: &str) -> bool {
    let mut map = HashMap::<char, i32>::new();

    for c in s.chars() {
        if map.contains_key(&c) {
            return false;
        }

        map.insert(c, 1);
    }
    true
}

fn main() {
    println!("Running...");

    assert!(is_unique_slow("qwer1234"));
    assert!(!is_unique_slow("qwer123q"));

    assert!(is_unique_sorted("qwer1234"));
    assert!(!is_unique_sorted("qwer123q"));

    assert!(is_unique_hashmap("qwer1234"));
    assert!(!is_unique_hashmap("qwer123q"));
}
