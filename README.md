# Organisation Hierarchy Binary Tree


Completed as an assignment for the Data Structures course at my university.

A C program that constructs and manipulates an organisation hierarchy represented as a binary tree. Each node in the tree corresponds to an employee (denoted by an uppercase letter), and the tree models reporting relationships between bosses and their team members.

## Features

1. **Tree Construction**: Parses a list of tuples `(node left-child right-child)` from a file and builds the binary tree. Missing children are marked with `X`.
2. **Inorder Traversal**: Prints the inorder sequence of employees.
3. **Tree Height**: Calculates and displays the height of the organisation tree.
4. **Boss Count**: Counts and prints the number of nodes that act as bosses (i.e., have at least one child).
5. **BST Verification**: Checks if the tree satisfies binary search tree (BST) properties based on alphabetical order. Reports the CEO if valid or the node where the violation occurs.
6. **Role Shuffling**: Applies a special rotation function (`specialFunction`) to the tree.
7. **Preorder Traversal**: Prints the preorder sequence of the tree after role shuffling.
8. **Employee Lookup**: Searches for specified employees (`nnn` and `ppp`) in the tree and prints their teammate or indicates if they are a sole team member.

## File Structure

```
project/
├── employees.txt   # Input file containing two lookup letters and employee tuples
├── main.c          # Source code implementing all tasks
└── README.md       # Project documentation
```

## Prerequisites

- GCC or any C compiler
- A terminal/command prompt

## Building

1. Clone the repository:
   ```sh
   git clone https://github.com/sarthak-jain37/Graded-Lab-2.git
   cd Graded-Lab-2
   ```
2. Compile the code:
   ```sh
   gcc -o main main.c
   ```

## Usage

1. Prepare an input file `employees.txt` in the project root with the following format:
   ```txt
   N P N L P J F N P X T F X X L X X T X X
   ```
   - The first two characters (`N` and `M`) are the lookup employees.
   - The rest are space-separated 3-character tuples: `(boss left-child right-child)`.
  
2. Run the program:
   ```sh
   ./main
   ```
3. The output will display:
   - Inorder traversal
   - Tree height
   - Number of bosses
   - BST verification result (including CEO if valid)
   - Preorder traversal after role shuffling
   - Lookup results for the specified employees

## Example Output

```txt
Inorder : F J L N P T 

The height of the tree : 4

The no. of bosses in the organization : 3

The Tree is a BST
CEO : J

Preorder : N J F L P T

Confirmed that P is an employee.
Team mate of P: J
Confirmed that T is an employee.
T is sole team member.
```


