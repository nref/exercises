def print_matrix(matrix, s1: str, s2: str, rr, cc):
    print(f"matrix({len(matrix)}, {len(matrix[0])}, {rr}, {cc}):")

    for i in range(0, len(matrix[0])):
        print(f"  {s1[i]}", end='')
    print()

    r : int = 0
    for row in matrix:
        print(f"{s2[r]} ", end='')

        c : int = 0
        for elem in row:

            if r == rr and c == cc:
              print(f"{elem}* ", end='')
            else: 
              print(f"{elem}  ", end='')

            c += 1
        r += 1
        print()

# Wagner-Fischer
#   c  a  t
# m 1  1  1
# a 1  1  1
# t 1  2  1
# s 1  2  2
def levenshtein_dp(s1: str, s2: str) -> int: 

    # init table
    m : int = len(s1)
    n : int = len(s2)
    d = [[0 for i in range(m)] for j in range(n)]

    # s1 can made into the empty string by removing each character
    for i in range(0, m):
        d[0][i] = i

    # s2 can be made from the empty string by inserting each character
    for i in range(0, n):
        d[i][0] = i

    for i in range(1, n):
        for j in range(1, m):
            print_matrix(d, s1, s2, i, j)

            if s2[i] == s1[j]:
                substitution_incr = 0
            else:
                substitution_incr = 1

            deletion_cost = d[i-1][j] + 1
            insertion_cost = d[i][j-1] + 1
            substitution_cost = d[i-1][j-1] + substitution_incr
            
            d[i][j] = min(deletion_cost, insertion_cost, substitution_cost)
            print(f"d[{i}][{j}] = min({deletion_cost}, {insertion_cost}, {substitution_cost}) = {d[i][j]}")

    return d[n - 1][m - 1]

def levenshtein_dp_two_rows(s1: str, s2: str) -> int:
    return 0

print("Running...")

def test_levenshtein_dp(s1: str, s2: str, expected: int):
    result : int = levenshtein_dp(s1, s2)
    ok : bool = expected == result
    if (not ok):
        print(f"levenshtein_dp(\"{s1}\", \"{s2}\") -> {result}. expected {expected}")
    assert(ok)

test_levenshtein_dp("cat", "mats", 2)
test_levenshtein_dp("cat", "cats", 1)
test_levenshtein_dp("cat", "mat", 1)
test_levenshtein_dp("cat", "cat", 0)
test_levenshtein_dp("kitten", "sitting", 3)
