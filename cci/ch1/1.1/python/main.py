# O(n*n) but uses no additional space/ structures
def is_unique_slow(s: str) -> bool:
    slen = len(s)
    for i in range(0, slen):
        for j in range(0, slen):
            if i == j:
                continue;
            if s[i] == s[j]:
                return False;
    return True;

def is_unique_sorted(s: str) -> bool:
    s_sorted = list(s)
    s_sorted.sort()
    slen = len(s);
    for i in range(0, slen-1):
        if s_sorted[i] == s_sorted[i+1]:
            return False;
    return True;

def is_unique_dict(s: str) -> bool:
    d = dict()
    for c in s:
        if c in d:
            return False;
        d[c] = c;
    return True;

print("Running...")
assert(is_unique_slow("qwer1234"))
assert(not is_unique_slow("qwer123q"))

assert(is_unique_sorted("qwer1234"))
assert(not is_unique_sorted("qwer123q"))

assert(is_unique_dict("qwer1234"))
assert(not is_unique_dict("qwer123q"))
