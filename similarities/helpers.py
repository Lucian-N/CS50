from enum import Enum

class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3
    NONE = -1

    def __str__(self):
        return str(self.name.lower())

def distances(a, b):
    """Calculate edit distance from a to b"""
    list_a = list(a)
    list_b = list(b)
    end_range_a = len(a)
    end_range_b = len(b)
    operation = Operation.NONE

	# Array to store words declaration
    word = [[0 for x in range(len(b)+1)] for y in range(len(a) + 1)]
	#Instantiate pos 0,0 as 0
    word[0][0] = 0

	# Initialize first row and column of Array
    for i in range(1, end_range_a + 1):
        word[i][0] = word[i-1][0] + 1

    for j in range(1, end_range_b + 1):
        word[0][j] = word[0][j-1] + 1

    # Initialize rest of array using min cost
    for i in range(1, end_range_a + 1):
        for j in range(1, end_range_b + 1):
            # If substitution is the minimal cost action
            # Determine if substituted character is the same
            if (list_a[i-1] == list_b[j-1]):
                word[i][j] = min(word[i-1][j] + 1,
                                 word[i][j-1] + 1,
                                 word[i-1][j-1])
                # Determines what operation is used
                if ( word[i-1][j] + 1 < word[i][j-1] + 1 and
                     word[i-1][j] + 1 < word[i-1][j-1]):
                    operation = Operation.DELETED
                elif ( word[i][j-1] + 1 < word[i-1][j] + 1 and
                       word[i][j-1] + 1 < word[i-1][j-1]):
                    operation = Operation.INSERTED
                else:
                    operation = Operation.SUBSTITUTED
            else:
                word[i][j] = min(word[i-1][j] + 1,
                                 word[i][j-1] + 1,
                                 word[i-1][j-1] + 1)
                if ( word[i-1][j] + 1 < word[i][j-1] + 1 and
                     word[i-1][j] + 1 < word[i-1][j-1] + 1):
                    operation = Operation.DELETED
                elif ( word[i][j-1] + 1 < word[i-1][j] + 1 and
                       word[i][j-1] + 1 < word[i-1][j-1] + 1):
                    operation = Operation.INSERTED
                else:
                    operation = Operation.SUBSTITUTED

    # Returns tuple of minimal cost to perform transformation
    # and last operation used
    ret_tuple = (word[end_range_b][end_range_a], operation)
    return ret_tuple
