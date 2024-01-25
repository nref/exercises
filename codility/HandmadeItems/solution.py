# We can create an array where each index tracks client c's waiting time
# Then we can subtract from the input array each hour at the client's index i
# and add that time to all waiting clients
# The sum of the wait times is the answer
def solution_slow(T):
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

# the above solution is O(N^2) because of the sum, inner while, and inner for.
# goals: remove the sum, inner while, and inner for
#   we can replace the sum with an initial sum of waiting clients and decrement
#   then we can replace the inner while with array lookups and a continue
#   the inner for can be replaced with a counter of all wait times. 
#     for that we keep track of how many clients are done
# Result: O(N)
def solution_fast(T):
    n = len(T)
    c = -1 # currently serviced client. Start at -1 because we increment at the top of the loop 
    c_waiting = n # how many clients are still waiting 
    total_wait = 0 # total wait time of all clients
    work_done = [0] * n # hours worked for each client

    # Loop until all work is done
    while c_waiting > 0:

        # Uncomment for debugging
        #print(c, c_waiting, total_wait, work_done, T)

        # Service next client 
        c += 1

        # Wrap around when all clients have been served a turn
        c = c % n

        # Skip finished clients
        if client_done(c, work_done, T):
            continue

        # Increment all waiting clients' wait time
        total_wait += c_waiting

        # Service this client
        work_done[c] += 1

        if client_done(c, work_done, T):
            c_waiting -= 1

    return total_wait % 10e9

def client_done(c, work_done, T):
    return work_done[c] == T[c]

def test(arr, want):
  got = solution_fast(list(arr))
  ok = want == got
  msg = "ok" if ok else f"bad, wanted {want}"

  print(f"solution({arr}) -> {got} ({msg})")

test([3,1,2], 13);
test([1,2,3,4], 24);
test([7,7,7], 60);
test([10000], 10000);
