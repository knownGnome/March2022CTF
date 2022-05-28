from pwn import *

r = remote('cweaccessionsctf.com', '1390')
#r = remote('52.227.157.244', '1340')

#g = "What is the value of 30 + 38?"

#h = g[g.index('f')+2:g.index('?')]

#print(h)

while True:
	s = r.recvline(False)	
	print(s)
	if s.endswith(b' '):
		answer = bytes.fromhex('abf0483b3ddb9cf938b9633aa951d000') #'b8 84 81 0'
		r.sendline(answer)


