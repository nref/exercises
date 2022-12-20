def is_odd(i) -> bool:
    return i % 2 != 0

def is_even(i) -> bool:
    return i % 2 == 0

def greater_than_five(i) -> bool:
    return i > 5

# Returns a func which returns the inverse of the given boolean function 
def inverse(func, *args) -> bool:
    def inv(args) -> bool:
      return func(args) == False
    return inv

# Given an input sequence and a predicate, return two lists, one where the elements
# of the sequence are false for the predicate and one where they are true, e.g.
# partition(range(10), pred=is_odd) -> [0, 2, 4, 6, 8], [1, 3, 5, 7, 9]
def partition(seq, pred):
    # This makes two runs over the list; we could make one run with a manual loop
    return (list(filter(inverse(pred), seq)), list(filter(pred, seq)))

def test_partition(seq, pred, expected):

    result = partition(seq, pred)
    ok = len(expected) == len(result)
    ok &= expected[0] == result[0]
    ok &= expected[1] == result[1]

    print(f'{"PASS " if ok else "FAIL"} partition({seq}, {pred}) => {result}')
    assert(ok)

test_partition(range(10), is_odd, ([0,2,4,6,8],[1,3,5,7,9]))
test_partition(range(10), is_even, ([1,3,5,7,9],[0,2,4,6,8]))
test_partition(range(10), greater_than_five, ([0,1,2,3,4,5],[6,7,8,9]))
