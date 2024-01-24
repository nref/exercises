# Given an array arr of N integers, find the contiguous sub-array with the maximum sum.
# (Also known as Largest Contiguous Sum or Maximum Subarray)
# 
# Example:
# 
# Input:
# 
# N = 5
# 
# Arr[ ] = {1, 2, 3, -2, 5}
# 
# Output:
# 
# 9

# Exploring.
# From the example, possible sub-arrays:
# 1
# 1 2 
# 2 3 
# 1 2 3
# 2 3 -2
# 1 2 3 -2
# 2 3 -2 5
# 1 2 3 -2 5 
#
# It seems to me to be an O(n^2) task
# We don't need to know the sub array, so we don't need n^2 storage. 
# We can just keep the max
#
def max_subarray_slow(A):
  n = len(A)
  maxSum = 0

  for i in range(0, n):
    for j in range(i + 1, n + 1):
      # print(f"{i}, {j}: {A[i:j]} -> {sum(A[i:j])}")
      maxSum = max(maxSum, sum(A[i:j])) # sum makes it actually O(n^3) !!

  return maxSum

# Can we do better than O(n^3) ?
# It seems to me we can tabulate previously computed sums.
# Exploring...
#
#    i 0 1 2 3  4
#  j     
#  0   0 
#  1   1
#  2   3 2
#  3   6 5 3
#  4   4 3 1 -2
#  5   9 8 6  3 5
#
def max_subarray_better(A):
  
  n = len(A) + 1
  memo = [[0 for i in range(n)] for j in range(n)]

  theMax = -9999

  for i in range(0, n):
    for j in range(i + 1, n):
      memo[j][i] = memo[j-1][i] + A[j-1]
    # print("---------------------------------")
    # pretty_print(memo)
    theMax = max(theMax, max(memo[i]))

  return theMax

# That's better!


def pretty_print(A):
  print('\n'.join([''.join([str(cell).rjust(3, " ") for cell in row]) for row in A]))

def solution(A):
  return max_subarray_better(A)

def test_solution(A, want):
  got = solution(A)
  ok = want == got
  msg = "ok" if ok else f"bad, wanted {want}"

  print(f"solution({A}) -> {got} ({msg})")

test_solution([1, 2, 3, -2, 5], 9);
test_solution([-2, 1, -3, 4, -1, 2, 1, -5, 4], 6)
test_solution([-2, -3, 4, -1, -2, 1, 5, -3], 7)
