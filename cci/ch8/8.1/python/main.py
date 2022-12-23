total_recursive_calls: int = 0

# Naive recursion, time O(3^n), max stack depth N
# Recursion tree for n = 4:
#
#               | ------ 4 -- |
#               3        2    1
#             2 1 0     1 0  0
#            1  0      0
#           0
def triple_step_recursive(n: int, depth: int) -> int:
    global total_recursive_calls
    total_recursive_calls += 1

    #print(f"{'  '*depth}triple_step_recursive({n}, {depth})")

    # Define base case as 0 steps to go to cull bottom of tree
    if n <= 0:
        return 0

    sum: int = 0

    if n == 3 or n == 2 or n == 1:
        sum = 1;

    if n == 1:
       return sum

    next_depth: int = depth + 1
    return sum + triple_step_recursive(n - 1, next_depth) \
               + triple_step_recursive(n - 2, next_depth) \
               + triple_step_recursive(n - 3, next_depth)

# dp solution. time O(N), space O(N)
def triple_step_dp(n: int) -> int:
    memo = [0]*n
    memo[0] = 1

    for i in range(1, n):
        if i == 2 or i == 1:
           memo[i] = 1

        memo[i] += memo[i - 1]
        memo[i] += memo[i - 2] if i > 1 else 0 
        memo[i] += memo[i - 3] if i > 2 else 0

    return memo[n - 1]

def test_triple_step_recursive(n: int, expected: int):
    global total_recursive_calls
    total_recursive_calls = 0
    result: int = triple_step_recursive(n, 1)
    print(f"triple_step_recursive({n}) total calls: {total_recursive_calls}")
    
    ok: bool = result == expected
    if not ok:
        print(f"triple_step_recursive({n}) returned {result}, expected {expected}")
        assert(False)

def test_triple_step(n: int, expected: int):
    result: int = triple_step_dp(n)

    ok: bool = result == expected
    if not ok:
        print(f"triple_step({n}) returned {result}, expected {expected}")
        assert(False)

print("Running...")

test_triple_step_recursive(1, 1)
test_triple_step_recursive(2, 2)
test_triple_step_recursive(3, 4)
test_triple_step_recursive(4, 7)

test_triple_step(1, 1)
test_triple_step(2, 2)
test_triple_step(3, 4)
test_triple_step(4, 7)
