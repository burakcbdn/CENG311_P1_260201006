from random import randrange

fileData = ""; # string to be written to file

integerAmount = 2**27 # amount to generate integers

while (integerAmount > 0):
    number = randrange(integerAmount)
    fileData += str(number) + " "
    integerAmount -= 1

# create file read the data and close the file
with open("data.txt", "w") as f:
    f.write(fileData)

