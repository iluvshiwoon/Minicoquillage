from itertools import product

# Define the elements to combine
elements = ["<<", "echo", "LIM", "|"]

# Generate all combinations of length 4
combinations = list(product(elements, repeat=4))

# Create a string representation for each combination without quotes and commas
combinations_display = [" ".join(comb) for comb in combinations]

# Write the combinations to a file
with open('cmds.txt', 'w') as file:
    for combination in combinations_display:
        file.write(combination + '\n')
