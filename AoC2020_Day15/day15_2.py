#MAX_LENGTH = 30000000
MAX_LENGTH = 2020
#MAX_LENGTH = 10

finput = open("./testinput.txt", "r")

# count commas
comma_count = 0
with open("./testinput.txt", "r") as f:
    comma_count = f.read().count(',')

readfile = finput.read().strip()
init_nums = readfile.split(",")

agedict = {}
cur_inx = 0
num = 0

for inx, num in enumerate(init_nums):
    agedict[int(num)] = (inx+1, inx+1)
    cur_inx = inx+1

agedict[int(num)] = agedict[int(num)][1:]+(-1,)

for i in range(1, MAX_LENGTH-comma_count):
    if int(num) in agedict:
        if agedict[int(num)][1] == -1:
            agedict[int(num)] = (agedict[int(num)][0], agedict[int(num)][0])
            num = 0
        else:
            cur_inx += 1
            agedict[int(num)] = (cur_inx, agedict[int(num)][0])
            num = agedict[int(num)][0] - agedict[int(num)][1]
    else:
        cur_inx += 1
        agedict[int(num)] = (cur_inx, cur_inx)
        num = 0
print(num)


"""
d[1] = (d[1][1], d[1][0]) swap values in tuples
d[0] = d[0][1:]+(-1,) make -1 the second value of tuple
0, 3, 6
num = 0
cur_inx = 0
agedict[num] = (cur, prev)
***initial read-in***
agedict[0] = (1, 1)
agedict[3] = (2, 2)
agedict[6] = (3, -1)
num = 6
cur_inx = 6

check agedict[6] is present:
    yes, so check if prev == -1:
        yes, it's the first time seeing it, so prev := cur
        num set to 0

agedict[0] = (1, 1)
agedict[3] = (2, 2)
agedict[6] = (3, 3)

check agedict[0] is present:
    yes, so check if prev == -1:
        no, it's not the first time seeing it, so
        (prev) := (curr) 1 := 1
        (curr) := 4
        cur_inx = 4
        next num is 4-1 = 3.

agedict[0] = (4, 1)
agedict[3] = (2, 2)
agedict[6] = (3, 3)

check agedict[3] is present:
    yes, so check if prev == -1:
        no, it's not the first time seeing it, so
        (prev) := (curr) -> 2 := 2
        (curr) := 5
        cur_inx = 5
        next num is 5-2 = 3

agedict[0] = (4, 1)
agedict[3] = (5, 2)
agedict[6] = (3, 3)

check agedict[3] is present:
    yes, so check if prev == -1:
        no, it's not the first time seeing it, so
        (prev) := (curr) -> 2 := 5
        (curr) := 6
        cur_inx = 6
        next num is 6-5 = 1

agedict[0] = (4, 1)
agedict[3] = (6, 5)
agedict[6] = (3, 3)

check agedict[1] is present:
    no, so set agedict[1] = (7, 7)
    cur_inx = 8
    next num is 0

agedict[0] = (4, 1)
agedict[3] = (6, 5)
agedict[6] = (3, 3)
agedict[1] = (7, 7)

check agedict[0] is present:
    yes, so check if prev == -1:
        no, it's not the first time seeing it, so
        (prev) := (curr) -> 1 := 4
        (curr) := 8
        cur_inx = 9
        next num is 8-4 = 4

agedict[0] = (8, 4)
agedict[3] = (6, 5)
agedict[6] = (3, 3)
agedict[1] = (7, 7)

check agedict[4] is present:
    no, so set agedict[1] = (9, 9)
    cur_inx = 10
    next num is 0

agedict[0] = (8, 4)
agedict[3] = (6, 5)
agedict[6] = (3, 3)
agedict[1] = (7, 7)
agedict[4] = (9, 9)

check agedict[0] is present:
    yes, so check if prev == -1:
        no, it's not the first time seeing it, so
        (prev) := (curr) -> 4 := 8
        (curr) := 10
        cur_inx = 11
        next num is 10-8 = 2
"""
