def day_1_part_2(rotations):
    start = 50
    actual_password = 0
    for i in rotations:
        i = i.strip()
        if not i:
            continue
        letter = i[0]
        number = int(i[1:])

        if letter == 'R':
            for j in range(number):
                start = (start + 1) % 100
                if start == 0:
                    actual_password += 1

        else:
            for j in range(number):
                start = (start - 1) % 100
                if start == 0:
                    actual_password += 1

    return actual_password

        
lst = """
""".strip().split('\n')

print(day_1_part_2(lst))