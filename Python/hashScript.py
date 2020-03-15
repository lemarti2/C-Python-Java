import hashlib 

message = input('what is the message: ').encode()
print('SHA1:')
print()
print(hashlib.sha1(message).hexdigest())
print()
print('MD5:')
print()
print(hashlib.md5(message).hexdigest())
