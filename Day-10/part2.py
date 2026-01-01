import sys
from math import inf

def parse_line(line: str):
    parts = line.split()
    lights_raw = parts[0]
    configs_raw = parts[1:-1]
    joltage_raw = parts[-1]
    configs = [
        [int(x) for x in config_raw[1:-1].split(",")] if config_raw[1:-1] else []
        for config_raw in configs_raw
    ]
    joltages = (
        tuple(int(x) for x in joltage_raw[1:-1].split(",")) if joltage_raw[1:-1] else ()
    )
    return lights_raw, configs, joltages


def solve_machine(configs, joltages):
    n = len(joltages)
    m = len(configs) + 1
    matrix = [[0 for _ in range(m)] for _ in range(n)]
    upper_bounds = [inf] * len(configs)
    for i in range(len(configs)):
        if not configs[i]:
            upper_bounds[i] = 0
            continue
        ub = inf
        for j in configs[i]:
            ub = min(ub, joltages[j])
        upper_bounds[i] = ub
    for j in range(m - 1):
        for i in configs[j]:
            matrix[i][j] = 1
    for i in range(n):
        matrix[i][-1] = joltages[i]
    var_count = m - 1
    M = [[float(matrix[i][j]) for j in range(m)] for i in range(n)]
    pivot_cols = []
    row = 0
    EPS = 1e-9
    for col in range(var_count):
        pivot = None
        best = 0.0
        for r in range(row, n):
            v = abs(M[r][col])
            if v > best + EPS:
                best = v
                pivot = r
        if pivot is None:
            continue

        M[row], M[pivot] = M[pivot], M[row]

        pv = M[row][col]
        for j in range(col, m):
            M[row][j] /= pv

        for r in range(n):
            if r == row:
                continue
            factor = M[r][col]
            if abs(factor) < EPS:
                continue
            for j in range(col, m):
                M[r][j] -= factor * M[row][j]

        pivot_cols.append(col)
        row += 1
        if row == n:
            break

    free_cols = [c for c in range(var_count) if c not in pivot_cols]
    pivot_row_for_col = {pivot_cols[i]: i for i in range(len(pivot_cols))}

    best = inf
    x = [0] * var_count

    def dfs(free_idx, cur_sum):
        nonlocal best
        if cur_sum >= best:
            return
        if free_idx == len(free_cols):
            total = cur_sum

            for col in pivot_cols:
                r = pivot_row_for_col[col]
                rhs = M[r][var_count]
                for j in range(var_count):
                    if j == col:
                        continue
                    rhs -= M[r][j] * x[j]

                val = rhs
                val_rounded = round(val)
                if abs(val - val_rounded) > EPS:
                    return
                v = int(val_rounded)
                if v < 0:
                    return
                ub = upper_bounds[col]
                if ub != inf and v > ub:
                    return

                x[col] = v
                total += v
                if total >= best:
                    return

            if total < best:
                best = total
            return
        col = free_cols[free_idx]
        ub = upper_bounds[col]
        if ub == inf:
            ub = max(joltages) if joltages else 0
        for v in range(0, ub + 1):
            x[col] = v
            dfs(free_idx + 1, cur_sum + v)

    dfs(0, 0)
    return best


def main():
    total = 0
    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue
        _, configs, joltages = parse_line(line)
        presses = solve_machine(configs, joltages)
        total += presses
    print(total)


if __name__ == "__main__":
    main()
