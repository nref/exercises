# Given an Integer N and a list arr, sort the array using the bubble sort algorithm.
# 
# Example:
# 
# Input:
# 
# N = 5
# arr[] = {4, 1, 3, 9, 7}
# 
# Output:
# 1 3 4 7 9

def maybeSwap(i, j, arr):
  if arr[i] > arr[j]:
    swap(i, j, arr)

def swap(i, j, arr):
  tmp = arr[i]
  arr[i] = arr[j]
  arr[j] = tmp

def bubble(i, N, arr):
  swapped = False
  for j in range(i, N):
    maybeSwap(i, j, arr);
    swapped = True
  return swapped

def solution(N, arr):
  for i in range(0, N):
    swapped = bubble(i, N, arr)
    if not swapped:
      break

  return arr

def test(N, arr, want):
  got = solution(N, arr)
  ok = want == got
  msg = "ok" if ok else "bad"

  print(f"{N}, {arr} -> {got} ({msg})")

test(5, [4, 1, 3, 9, 7], [1, 3, 4, 7, 9]);
test(6, [4, 3, 2, 1, -1, -2], [-2, -1, 1, 2, 3, 4]);
