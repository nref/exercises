# Time: O(M*N) where M is # of rows, N is # of columns
# Space: O(M*N)
def solution(grid):
    r : int = len(grid)
    c : int = len(grid[0])

    breadcrumbs = [[0 for j in range(0, c)] for i in range(0, r)]
    return solution_recurse(grid, breadcrumbs, 0, 0, 0)

def print_grid(grid, row: int, col: int):

    for r in range(0, len(grid)):
        for c in range(0, len(grid[r])):
            if r == row and c == col:
                print(f'{grid[r][c]}* ', end='')
            else:
                print(f'{grid[r][c]}  ', end='')
        print()

def can_go_down(grid, r, c):
    return r < len(grid) -1 and grid[r+1][c] == 0

def can_go_right(grid, r, c):
    return c < len(grid[0]) - 1 and grid[r][c+1] == 0

def solution_recurse(grid, breadcrumbs, r: int, c: int, branch_count: int):
    print(f'solution_recurse({grid}, {breadcrumbs} {r}, {c}, {branch_count})')
    print_grid(grid, r, c)

    # If we're at the goal
    if r == len(grid) - 1 and c == len(grid[0]) - 1:
        return branch_count + 1

    # If we've been here before
    if breadcrumbs[r][c] == 1:
        return branch_count

    breadcrumbs[r][c] = 1

    # If we can't go down or right, this is a dead-end.
    if not can_go_down(grid, r, c) and not can_go_right(grid, r, c):
        return 0

    # If we can only go right
    if not can_go_down(grid, r, c) and can_go_right(grid, r, c):
        return solution_recurse(grid, breadcrumbs, r, c+1, branch_count)

    # If we can only go down
    if can_go_down(grid, r, c) and not can_go_right(grid, r, c):
        return solution_recurse(grid, breadcrumbs, r+1, c, branch_count)
    
    # If we can go down or right
    if can_go_down(grid, r, c) and can_go_right(grid, r, c):
        return solution_recurse(grid, breadcrumbs, r+1, c, branch_count) \
             + solution_recurse(grid, breadcrumbs, r, c+1, branch_count)


def test_solution(grid, expected: int):
    result: int = solution(grid)

    if expected != result:
        print(f'Expected {expected}, got {result}. Grid: {grid}')
        assert(False)

grid1 = [[0,0,0],[0,1,0],[0,0,0]]
grid2 = [[0,1],[0,0]]
grid3 = [[0,1,0,0], \
         [0,0,0,0], \
         [1,0,0,0]]
grid4 = [[0,1,0,0], \
         [1,0,0,0], \
         [0,0,0,0]]

test_solution(grid1, 2)
test_solution(grid2, 1)
test_solution(grid3, 2)
test_solution(grid4, 0)

