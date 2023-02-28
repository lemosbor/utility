from itertools import product

комбинации=[''.join(x) for x in product('абвгдеёжзийклмнопрстуфхцчшщъыьэюя_', repeat=3)]


with open("komb", "w") as file:
    file.write(str(комбинации))
