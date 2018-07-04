import cs50

print("Please enter a valid Credit Card number: ", end = "")
while True:
    card_number = cs50.get_float()
    if card_number >= 0:
        break