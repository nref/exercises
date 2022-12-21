def is_permutation_sorted(s1: str, s2: str) -> bool:
    l1 = list(s1)
    l2 = list(s2)

    l1.sort()
    l2.sort()

    return "".join(l1) == "".join(l2)

def is_permutation_dict(s1: str, s2: str) -> bool:
    d1 = dict([(c, 0) for c in s1])
    d2 = dict([(c, 0) for c in s2])

    for c in s1:
        d1[c] += 1;

    for c in s2:
        d2[c] += 1;

    return d1 == d2
    
print("Running...")
assert(is_permutation_sorted("racecar", "racecar"))
assert(is_permutation_sorted("racecar", "racecra"))
assert(is_permutation_sorted("racecar", "racecar"))

assert(is_permutation_dict("racecar", "racecra"))
assert(not is_permutation_dict("racecar", "racecrZ"))
assert(not is_permutation_dict("racecar", "racecrZ"))
