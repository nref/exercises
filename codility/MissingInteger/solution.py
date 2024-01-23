# Convert A to a set. 
# Then iterate n from 1 to 1_000_000 and return n if it's not in set(A)
# Runtime: 0(n)
def solution(A):
  theSet = set(A);
  for elem in range(1, 1_000_000):
    if elem not in theSet:
      return elem
  return 0

def test(want, input):
  got = solution(input)
  ok = want == got
  msg = "ok" if ok else "bad"

  print(f"{input} -> {got} ({msg})")

test(5, [1,3,6,4,1,2]);
test(4, [1,2,3]);
test(1, [-1,-3]);
test(100_000, [i for i in range(1, 100_000)]);
