# Given an array A of integers, find the length of the longest sub-sequence so that elements in the sub-sequence are consecutive integers. The consecutive numbers can be in any order.
#
# Example:
#
# Input: N = 7, A[ ] = {1, 9, 3, 10, 4, 20, 2}
# 
# Output: 4
# 
# Explanation: The subsequence 1, 3, 4, 2 is the longest subsequence of consecutive elements.

# Questions I would ask in an interview:
# 1. Are the entries in A unique?
# 2. Can the entries be negative?

# Algorithm:
# - O(n) put A into a dictionary/set
# - O(n) convert back to array
# - O(n lg n) sort by key
# - O(n) linearly scan, counting consecutive sequence length
# ```
#   let n : int = 1
#   let nMax : int = 0
#   start at index i == 0
#   if arr[i+1] == arr[i] + 1:
#     n += 1
#     nMax = max(n, nMax)
#   else:
#     n = 0
#   i++
#   return nMax
#```

def sort_and_dedupe(A : list):
  unique = set(A)
  sorted = list(unique)
  sorted.sort()
  return sorted

def scan(l):
  n = 1
  nMax = 0

  for i in range(0, len(l) - 1):
    if l[i+1] == l[i] + 1:
      n+= 1
      nMax = max(n, nMax)
    else:
        n = 0
  return nMax

def solution(A):
  l = sort_and_dedupe(A)
  return scan(l)

def test_sort_and_dedupe(A, want):
  got = sort_and_dedupe(A)
  ok = want == got
  msg = "ok" if ok else f"bad, wanted {want}"

  print(f"sort_and_dedupe({A}) -> {got} ({msg})")

def test_solution(A, want):
  got = solution(A)
  ok = want == got
  msg = "ok" if ok else f"bad, wanted {want}"

  print(f"solution({A}) -> {got} ({msg})")

test_sort_and_dedupe([4, 1, 1, 3, 9, 7], [1, 3, 4, 7, 9]);
test_solution([1, 9, 3, 10, 4, 20, 2], 4);
test_solution([7, 5, 4, 3, 2, 1, 0, -1], 7);
