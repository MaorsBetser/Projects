# Value of Quarter, Dime Nickel and Penny
coins = [25, 10, 5, 1]
numCoins = [0, 0 ,0 ,0]

while True:
    cashPayed = float(input("How much did you pay?: "))
    if cashPayed > 0:
        break
cashPayed = cashPayed * 100 # to avoid using float

#How to increment diffrent variables? inside the same statemnt
for i in range(len(coins)):
    if cashPayed >= coins[i]:
        cashPayed = cashPayed - coins[i]
        numCoins[i] += 1

    elif cashPayed < coins[i]:
        i += 1

print(f"Quarters : {numCoins[0]}, Dimes :{numCoins[1]}, Nickels : {numCoins[2]}, Pennies :{numCoins[3]}")






