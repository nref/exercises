# O(N) storage, O(N) time
def fibonacci_list(n : int) -> int:
    fibs = []
    fibs.append(0);
    fibs.append(1);

    for i in range(2, n + 1):
        fibs.append(fibs[i - 1] + fibs[i - 2])

    return fibs[n]

# O(1) storage, O(N) time
def fibonacci_single(n : int) -> int:
    x : int = 0
    y : int = 1
    fib : int = x if n == 0 else y

    for i in range(1, n):
       fib = x + y 
       x = y
       y = fib

    return fib

expected = {
    0 : 0,
    1 : 1,
    2 : 1,
    3 : 2,
    4 : 3,
    5 : 5,
    6 : 8,
    7 : 13,
    8 : 21,
    9 : 34,
    10 : 55,
}

print("Running...")

for n, fib in expected.items():
    assert(fibonacci_list(n) == fib)
    assert(fibonacci_single(n) == fib)
