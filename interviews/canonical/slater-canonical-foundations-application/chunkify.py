# Write a function to group characters from an input string into fixed
# length chunks, with a given fill value, e.g.
# chunkify(‘ABCDEFG’, 3, ‘x’) -> [‘ABC’, ‘DEF’, Gxx’]
def chunkify(s, n, fill='x'):
    chunks = []
    i = 0
    count = len(s)
    while i < count:
        chunks.append(s[i:i+n])
        i+=n;
    chunks[-1] += fill*(i-count)
    return chunks;

def test_chunkify(s,  n, expected):

    result = chunkify(s, n)
    ok = expected == result
    print(f'{"PASS " if ok else "FAIL"} chunkify({s}, {n}) => {result}')
    assert(ok)

test_chunkify('ABCDEFG', 3, ['ABC', 'DEF', 'Gxx'])
test_chunkify('ABCDEFG1234567~', 7, ['ABCDEFG', '1234567', '~xxxxxx'])
test_chunkify('A', 5, ['Axxxx'])
