from enum import Enum

class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3


    def __str__(self):
        return str(self.name.lower())

def distances(a, b):
    """Calculate edit distance from a to b"""
    end_range_a = len(a) + 1
    end_range_b = len(b) + 1

	# Array to store words declaration
    word = [[(0, None) for x in range(end_range_b)] for y in range(end_range_a)]

	# Initialize first row and column of Array
    for i in range(1, end_range_a):
        word[i][0] = (i, Operation.DELETED)

    for j in range(1, end_range_b):
        word[0][j] = (j, Operation.INSERTED)

    # Initialize rest of array using min cost
    for i in range(1, end_range_a):
        for j in range(1, end_range_b):
            deletion = (word[i - 1][j])[0]
            insertion = (word[i][j - 1])[0]
            substitution = (word[i - 1][j - 1])[0]

            deletion += 1
            insertion += 1
            substitution += 1
            # If substitution is the minimal cost action
            # Determine if substituted character is the same
            if (a[i - 1] == b[j - 1]):
                substitution -= 1
            if (deletion < insertion and deletion < substitution):
                word[i][j] = (deletion, Operation.DELETED)
            elif (insertion < deletion and insertion < substitution):
                word[i][j] = (insertion, Operation.INSERTED)
            else:
                word[i][j] = (substitution, Operation.SUBSTITUTED)

    # Returns tuple of minimal cost to perform transformation
    # and last operation used
    return word
