# Strategy: Sort the array since the holes are ordered
# There will always be a board on the leftmost hole (A[0]) and another on the rightmost hole (A[N-1])
# Start at A[0] and grow rightward, start at A[N-1] and grow leftward. Current length is L
# For each L, check that A[0] + L and A[N] - L cover all holes
# Covered means scan left to right and find the first index K where A[K] - A[0] <= L
#    and A[N-1] - A[K] <= L
# Complexity: O(n lg n) + O(n*(n/2)) = ~O(n^2)

def covered(A, L):
  n = len(A)
  half_n = max(1, int(n/2))

  for K in range(1, half_n + 1):
    l = A[K] - A[0]
    r = A[n-1] - A[K+1]
    is_covered = l <= L and r <= L
    #print("  ", L, K, l, r, is_covered)

    if is_covered:
      return True
  return False

def solution(A):
  A.sort()
  n = len(A)
  # Distance from leftmost to rightmost hole
  span = A[n-1] - A[0]
  half_span = max(1, int(span/2))

  if span < 2:
    return 1

  for L in range(1, half_span + 1):
    if covered(A, L):
      return L

  return -1

def test(A, want):
  got = solution(A)
  ok = want == got
  msg = "ok" if ok else f"bad, wanted {want}"

  print(f"solution({A}) -> {got} ({msg})")

test([9], 1);
test([11,20,15], 4);
test([15,20,9,11], 5);
test([0,44,32,30,42,18,34,16,35], 18);
