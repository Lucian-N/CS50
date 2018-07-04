import cs50



while True:
    print("Please select the pyramid height: ", end = "" )
    height = cs50.get_int()
    if height >= 0 and height <= 23:
        break

for level in range(height):
    print (" " * (height - level - 1), end = "" )
    print ("#" * (level + 1), end = "" )
    print ("  ", end = "" )
    print ("#" * (level + 1))
