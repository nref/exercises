# Search an Element in Sorted and Rotated Array
# 
# Given a sorted and rotated array A of N distinct elements which is rotated at some point, and given an element K, find the index of the given element K in the array A.
# 
# Example:
# 
# Input:
# 
# N = 9
# 
# A[] = {5, 6, 7, 8, 9, 10, 1, 2, 3}
# 
# K = 10
# 
# Output: 5
# 
# Explanation: 10 is found at index 5.

# Clarifying questions I would ask in an interview:
# - Is there always exactly one rotation?

# Strategy:
# Find the pivot point, i.e. point where i+1 > i. 
#   We could do an O(n) linear search, but better to do an O(lg n) binary search.
# Given the pivot point, unpivot the array.
# Then do a binary search for K 
# Complexity: O(lg n)
#
# A simpler, less efficient strategy not chosen here, 
# would be just to sort the array, ignoring the pivot information

def find_pivot(arr):
  l = 0
  r = len(arr) - 1

  while l < r:
    m = int((l + r) / 2)
    if arr[m] > arr[r]:
      l = m + 1
    else:
      r = m

  return l

# split the array at the given index. return the (left, right) arrays
def split(i, arr):
  left = arr[:i]
  right = arr[i:]
  return (left, right)

def search(K, arr):
  l = 0
  r = len(arr) - 1

  while l <= r:
    m = int((l + r) / 2)
    if arr[m] < K:
      l = m + 1
    elif arr[m] > K:
      r = m - 1
    else:
      return m

  return -1

def solution(K, arr):
  i = find_pivot(arr)
  (left, right) = split(i, arr) # TODO unpivot in place
  theSplit = right + left
  idx = search(K, theSplit)

  if idx < len(right):
    return idx + len(left)
  return idx - len(right)

def test_find_pivot(arr, want):
  got = find_pivot(arr)
  ok = want == got
  msg = "ok" if ok else f"bad, wanted {want}"

  print(f"test_find_pivot({arr}) -> {got} ({msg})")

def test_split(i, arr, want):
  got = split(i, arr)
  ok = want == got
  msg = "ok" if ok else f"bad, wanted {want}"

  print(f"test_split({arr}) -> {got} ({msg})")

def test_search(K, arr, want):
  got = search(K, arr)
  ok = want == got
  msg = "ok" if ok else f"bad, wanted {want}"

  print(f"test_search({K}, {arr}) -> {got} ({msg})")

def test_solution(K, arr, want):
  got = solution(K, arr)
  ok = want == got
  msg = "ok" if ok else f"bad, wanted {want}"

  print(f"test_solution({K}, {arr}) -> {got} ({msg})")

print("---")

# Unit tests
test_search(6, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 6)
test_split(6, [5, 6, 7, 8, 9, 10, 1, 2, 3], ([5, 6, 7, 8, 9, 10], [1, 2, 3]))
test_find_pivot([5, 6, 7, 8, 9, 10, 1, 2, 3], 6)

# Integration test
test_solution(1, [5, 6, 7, 8, 9, 10, 1, 2, 3], 6);
test_solution(2, [5, 6, 7, 8, 9, 10, 1, 2, 3], 7);
test_solution(3, [5, 6, 7, 8, 9, 10, 1, 2, 3], 8);
test_solution(5, [5, 6, 7, 8, 9, 10, 1, 2, 3], 0);
test_solution(10, [5, 6, 7, 8, 9, 10, 1, 2, 3], 5);
