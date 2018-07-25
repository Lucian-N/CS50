import cs50
#Program to check credit card
#number validity and determine
#what type of card the user inputs
# card digits constant
MAX_DIGITS = 10000000000000000
# every other digit sum, 2nd to last digit
other_digit_sum = 0
# digit sum, last digit
normal_digit_sum = 0
# checks  user input for invalid card numbers
print("Please enter your Credit Card number: ", end = "")
card_number = cs50.get_int()
while card_number < 0:
    print("Please enter a valid Credit Card number: ", end = "")
    card_number = cs50.get_int()
#variable to hold card digits in reveresed order
digits = []
alternate_digis= []
iterate_digits = card_number
while iterate_digits >= 1 and iterate_digits < MAX_DIGITS:
    digits.append(iterate_digits % 10)
    #multiplies said digits by 2 and sums up their digits
    alternate_digis.append(((2 * (iterate_digits % 10)) // 10) +
                            (2 * (iterate_digits % 10)) % 10 )
    iterate_digits //= 10
if len(digits) != 0:
    #checks number of digits and sums up every digit starting with the 2nd
    if len(digits) == 16:
        for i in range(len(digits)-2, -1, -2):
            normal_digit_sum += digits[i]
    else:
        for i in range(len(digits)-1, -1, -2):
            normal_digit_sum += digits[i]

    #checks number of digits sums up every other digit starting with the first
    if len(alternate_digis) == 16:
        for i in range(len(alternate_digis) -1, -1, -2):
            other_digit_sum += alternate_digis[i]

    else:
        for i in range(len(alternate_digis) -2, -1, -2):
            other_digit_sum += alternate_digis[i]

    #Digit checksum to ensure card number is valid
    check_digits = (other_digit_sum + normal_digit_sum) % 10
    #Determine card type
    if (check_digits != 0):
        print("INVALID")
    elif (digits[len(digits) - 1] == 4):
        print("VISA")
    elif (digits[len(digits) - 1] == 3) and ((digits[len(digits) - 2] == 4)
                                        or (digits[len(digits) - 2] == 7)):
        print("AMEX")
    elif (digits[len(digits) - 1] == 5) and ((digits[len(digits) - 2] == 1)
                                                   or (digits[len(digits) - 2] == 2)
                                                   or (digits[len(digits) - 2] == 3)
                                                   or (digits[len(digits) - 2] == 4)
                                                   or (digits[len(digits) - 2] == 5)):
        print("MASTERCARD")






