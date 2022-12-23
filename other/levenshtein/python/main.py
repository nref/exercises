def print_bar(width: int):
    for i in range(0, width):
        if i > 0:
            print(f"---", end='')
        else:
            print(f"       ", end='')
    print()


# Print horizontal label
def print_hlabel(s: str, width: int):
    for i in range(0, width):
        if i > 0:
            print(f"  {s[i - 1]}", end='')
        else:
            print(f"     ", end='')
    print()

def print_vlabel(s: str, r: int):
    # Print vertical label
    if r > 0:
        print(f"{s[r - 1]} | ", end='')
    else: 
        print(f"    ", end='')

def print_matrix(matrix, s1: str, s2: str, rr, cc):
    #print(f"matrix({len(matrix)}, {len(matrix[0])}, {rr}, {cc}):")

    print_bar(len(matrix[0]));
    print_hlabel(s1, len(matrix[0]))
    print_bar(len(matrix[0]));

    r : int = 0
    for row in matrix:
        print_vlabel(s2, r)

        # Print table data
        c : int = 0
        for elem in row:

            if r == rr and c == cc:
              print(f"{elem}* ", end='')
            else: 
              print(f"{elem}  ", end='')

            c += 1
        r += 1
        print()

# Edit distance with Wagner-Fischer. Time and space O(N * M)
def levenshtein_dp(s1: str, s2: str) -> int: 

    # init table
    m : int = len(s1)
    n : int = len(s2)

    if m == 0:
        return n

    if n == 0:
        return m

    # + 1 so strings are 1-indexed
    d = [[0 for i in range(m + 1)] for j in range(n + 1)]

    # s1 can made into the empty string by removing each character
    for c in range(0, m + 1):
        d[0][c] = c

    # s2 can be made from the empty string by inserting each character
    for r in range(0, n + 1):
        d[r][0] = r

    for i in range(0, n):
        for j in range(0, m):

            # Not strictly necessary, since we already initialized the table to zeroes, but to follow the definition:
            if min(i, j) == 0:
                d[i][j] = max(i, j)
            else:

                substitution_incr = 0 if s1[i - 1] == s2[j - 1] else 1

                deletion_cost = d[i-1][j] + 1
                insertion_cost = d[i][j-1] + 1
                substitution_cost = d[i-1][j-1] + substitution_incr
                
                d[i][j] = min(deletion_cost, insertion_cost, substitution_cost)
                #print(f"d[{i}][{j}] = min(del, insert, subst) = min({deletion_cost}, {insertion_cost}, {substitution_cost}) = {d[i][j]}")
                # input()

            print_matrix(d, s1, s2, i, j)
    return d[n - 1][m - 1]

# TODO use just O(2N) space
def levenshtein_dp_two_rows(s1: str, s2: str) -> int:
    return 0

def test_levenshtein_dp(s1: str, s2: str, expected: int):
    result : int = levenshtein_dp(s1, s2)
    ok : bool = expected == result
    if (not ok):
        print(f"levenshtein_dp(\"{s1}\", \"{s2}\") -> {result}. expected {expected}")
    assert(ok)

print("Running...")

test_levenshtein_dp("kitten", "sitting", 3)
test_levenshtein_dp("cat", "mats", 2)
test_levenshtein_dp("cat", "cats", 1)
test_levenshtein_dp("cat", "mat", 1)
test_levenshtein_dp("cat", "cat", 0)
test_levenshtein_dp("cat", "", 3)
test_levenshtein_dp("", "cat", 3)
