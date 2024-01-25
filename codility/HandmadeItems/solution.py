# We can create an array where each index tracks client c's waiting time
# Then we can subtract from the input array each hour at the client's index i
# and add that time to all waiting clients
# The sum of the wait times is the answer
def solution(T):
    n = len(T)
    wait_times = [0] * n

    i = 0
    while sum(T) != 0:

        # Skip clients who are no longer waiting
        while T[i] == 0 and i < n:
          i+=1

        # Uncomment for debugging
        #print(i, T, wait_times)
        #input()

        # Increment all clients' wait time
        for c in range(0, n):
            if T[c] != 0:
                wait_times[c] += 1

        # decrement this client work remaining
        if T[i] != 0:
            T[i] -= 1

        # Service next client
        i+=1

        # Repeat now that we have served all clients a turn
        i = i % n

    ans = sum(wait_times)
    return int(ans % 10e9)

def test(arr, want):
  got = solution(list(arr))
  ok = want == got
  msg = "ok" if ok else f"bad, wanted {want}"

  print(f"solution({arr}) -> {got} ({msg})")

test([3,1,2], 13);
test([1,2,3,4], 24);
test([7,7,7], 60);
test([10000], 10000);
