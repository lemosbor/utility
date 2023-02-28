from itertools import product

комбинации=[''.join(x) for x in product('абв', repeat=2)]

print(комбинации)
