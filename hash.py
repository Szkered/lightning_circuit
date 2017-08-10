from functools import reduce
import hashlib

r1 = [180, 34, 250, 166, 200, 177, 240, 137, 204, 219, 178, 17, 34, 14, 66, 65, 203, 6, 191, 16, 141, 210, 73, 136, 65, 136, 152, 60, 117, 24, 101, 18]

h1 = [169, 231, 96, 189, 221, 234, 240, 85, 213, 187, 236, 114, 100, 185, 130, 86, 231, 29, 123, 196, 57, 225, 159, 216, 34, 190, 123, 97, 14, 57, 180, 120]

h = hashlib.sha256()

int_list_to_bytes = lambda int_list: reduce(lambda x,y: x+y,
                                            map(lambda x: x.to_bytes(1, 'big'), int_list))
print('r1', int_list_to_bytes(r1))
print('h1', int_list_to_bytes(h1))

h.update(r1)

print('sha3(r1)', h.digest())

