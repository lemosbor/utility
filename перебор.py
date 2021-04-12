from itertools import permutations

комбинации=[''.join(x) for x in permutations('абв')]

набор = {"аб":1, "ба":2}

#https://www.geeksforgeeks.org/python-map-function/

#print(' '.join(map(lambda x: ''.join(x), permutations('abc'))))


numbers1 = [1, 2, 3]
numbers2 = [4, 5, 6]

result = map(lambda x, y: x + y, numbers1, numbers2)

print(list(result))

 

for i in комбинации[2]:

                print(i)

print(набор["ба"])