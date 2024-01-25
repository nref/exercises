# Paste the prompt and examples here.

def solution(arr):
  return 0

def test(arr, want):
  got = solution(arr)
  ok = want == got
  msg = "ok" if ok else "bad"

  print(f"solution({arr}) -> {got} ({msg})")

test([4, 1, 3, 9, 7], 0);
