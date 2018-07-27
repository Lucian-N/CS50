import cs50
import sys

#ASCII constants for UPPERCASE/lowercase strings:
TO_LOWER = 97
TO_UPPER = 65
ALPHABET_SIZE = 26

def main():
    if len(sys.argv) != 2:
        print("Invalid arguments provided")
        exit(1)

    key = int(sys.argv[1])
    print("plaintext: ", end = "")
    cipher_text = cs50.get_string()
    print("ciphertext: ", end = "")
    translated_text = []

    for char in cipher_text:
        if (cipher_text.isalpha() and cipher_text.isupper()):
            translated_text.append(chr(((ord(char) - TO_UPPER + key) % ALPHABET_SIZE) + TO_UPPER))
        elif (cipher_text.isalpha()):
             translated_text.append(chr(((ord(char) - TO_LOWER + key) % ALPHABET_SIZE) + TO_LOWER))
        else:
            translated_text.append(char)
    print ("".join(translated_text))

if __name__ == "__main__":
    main()