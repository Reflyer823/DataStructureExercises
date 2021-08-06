import random

count = 0
N = 100
M = 3000
print(N, M)
recs = set()
while count < M:
    x = random.randint(1, N - 1)
    y = random.randint(x + 1, N)
    if (x, y) not in recs:
        print(x, y)
        recs.add((x, y))
        count += 1