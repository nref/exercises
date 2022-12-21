def print_table(matrix):
    print(f"matrix({len(matrix)}, {len(matrix[0])}):")

    for row in matrix:
        for elem in row:
            print(f"  {elem} ", end='')
        print()

def levenshtein_dp(s1: str, s2: str) -> int: 
    m : int = len(s1)
    n : int = len(s2)
    d = [[0 for n in range(m)] for n in range(n)]
    print_table(d)

    for i in range(1, m):
        pass

    return 0

def levenshtein_dp_two_rows(s1: str, s2: str) -> int:
    return 0

print("Running...")

def test_levenshtein_dp(s1: str, s2: str, expected: int):
    result : int = levenshtein_dp(s1, s2)
    ok : bool = expected == result
    if (not ok):
        print(f"levenshtein_dp(\"{s1}\", \"{s2}\") -> {result}. expected {expected}")
    assert(ok)

test_levenshtein_dp("cat", "cat", 0)
test_levenshtein_dp("cat", "mat", 1)
test_levenshtein_dp("cat", "cats", 1)
test_levenshtein_dp("cat", "mats", 2)
test_levenshtein_dp("kitten", "sitting", 3)
