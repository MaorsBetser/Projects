while True:
    height  = int(input("What is the Height : "))
    if height >= 1:
        break

for i in range(height + 1):
    print(" " * (height - i), end = "")
    print("#" * i, end = "")
    print(" ", end = "")
    print("#" * i, end = "")
    print("" * (height - i), )
 

