def solve_day_1(rotations):
    start = 50
    actual_password = 0
    for i in rotations:
        i = i.strip()
        if not i:
            continue
        first = i[0]
        next = int(i[1:])
        if first == 'L':
            start = (start - next) % 100
        elif first == 'R':
            start = (start + next) % 100
        if start == 0:
            actual_password += 1
    return actual_password

lst = """
""".splitlines()
print(solve_day_1(lst))





