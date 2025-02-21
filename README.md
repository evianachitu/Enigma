# ENIGMA++

## Authors
Eviana Chițu & Irina-Maria Mîcnea

## Overview
ENIGMA++ is a program designed for **encryption and decryption** of messages using two different methods: the **Linear Congruential Generator (LCG) method** and the **Subtractive method**. The program relies on **seeded random numbers** for encryption and decryption, ensuring the reversibility of the process.

## Problem Description
The program allows a user to input a string, which is then encrypted using **pseudo-random number generators** based on the two different techniques:
- **Linear Congruential Generator (LCG) method**
- **Subtractive method**

Each character in the string is modified using the **XOR operation**, which ensures that applying the operation twice results in the original message.

## Encryption Methods
### 1. Linear Congruential Generator (LCG) Method
- Uses a mathematical formula to generate pseudo-random numbers.
- Applies XOR encryption with the generated numbers.
- Uses a single integer **seed** provided by the user.
- Decryption is performed using the same process and seed.

### 2. Subtractive Method
- Uses an array of **55 seed values** to initialize encryption.
- Generates a sequence of pseudo-random numbers using a subtractive algorithm.
- Encrypts/decrypts input strings using XOR with the generated values.

## Implementation Details
### LCG Method
- Uses the values **A = 1664525**, **C = 1013904223**, and **M = 0xFFFFFFFF** for random number generation.
- Implements `lcg(uint32_t previous)`, which calculates:
  ```c
  uint32_t lcg(uint32_t previous) {
      return A * previous + C;
  }
  ```
- The function `encrypt1(char *input, int seed)` iterates through the string and XORs each character with the generated random byte.

### Subtractive Method
- Requires **55 seed values** from the user.
- Uses the `generateNext(unsigned char state[55], int *index)` function to generate a pseudo-random sequence:
  ```c
  unsigned char generateNext(unsigned char state[55], int *index) {
      unsigned char nextValue = (state[(*index - 24 + 55) % 55] - state[(*index - 55 + 55) % 55]) % 256;
      state[*index] = nextValue;
      *index = (*index + 1) % 55;
      return nextValue;
  }
  ```
- The function `encrypt2(char *input, unsigned char state[55])` loops through the string and XORs each character with the generated sequence.

## Compilation and Usage
### Compilation
To compile the program, use:
```sh
gcc enigma.c -o enigma
```

### Running the Program
Execute the compiled program:
```sh
./enigma
```

### Input Format
1. Enter the string to be encrypted/decrypted.
2. Provide a **seed value** for the LCG method.
3. Enter **55 seed values** for the Subtractive method.

### Example
#### Input:
```
Enter the input string:
Hello, World!

Enter the LCG seed value:
1234

Enter 55 seed values (0-255):
3 27 45 99 ... (total 55 numbers)
```

#### Output:
```
Encrypted string (LCG): ɤÓ$%^&
Decrypted string (LCG): Hello, World!

Encrypted string (Subtractive): @#*(^%$!
Decrypted string (Subtractive): Hello, World!
```

## Test Cases
### Case 1: Basic Text
#### Input:
```
Irina and Eviana study Computer Science.
177
(55 seed values)
```
#### Output:
```
Encrypted string (LCG): ���syçOcÓ3æua...
Decrypted string (LCG): Irina and Eviana study Computer Science.

Encrypted string (Subtractive): qAÅGÃÉ©Fã...
Decrypted string (Subtractive): Irina and Eviana study Computer Science.
```

### Case 2: Punctuation and Numbers
#### Input:
```
King's Day is a national holiday in the Kingdom of the Netherlands, celebrated on 27 April.
33
(55 seed values)
```
#### Output:
```
Encrypted string (LCG): GÆpé�',�¡UzªDÃ{�æ...
Decrypted string (LCG): King's Day is a national holiday in the Kingdom of the Netherlands, celebrated on 27 April.

Encrypted string (Subtractive): ���+&5�ýV9|Oî;...
Decrypted string (Subtractive): King's Day is a national holiday in the Kingdom of the Netherlands, celebrated on 27 April.
```

## Evaluation
- The LCG method uses a simple mathematical approach with **single-seed initialization**.
- The Subtractive method uses **55 values**, offering more complexity in encryption.
- The encryption and decryption are fully reversible due to XOR operations.
- The implementation is optimized for speed and efficiency.


