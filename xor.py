#!/usr/bin/python3

import sys

def xor_crypt_string(data, key):
    i = 0
    for c in data:
        print(chr(ord(c) ^ ord(key[i])), end="")
        ++i
        if i == len(key):
            i = 0

fd = open(sys.argv[1])
secret_data = fd.read()
print(xor_crypt_string(secret_data, key="aZ"))
