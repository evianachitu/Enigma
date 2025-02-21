#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define A 1664525
#define C 1013904223
#define M 0xFFFFFFFF // 2^32 type for M

// LCG METHOD 
// Linear Congruential Generator (LCG) function
uint32_t lcg(uint32_t previous) {
    return A * previous + C; // Generate next random number
}

// Encrypt/Decrypt function using XOR with a random byte
void encrypt1(char *input, int seed) {
    uint32_t rand = seed;
    for (int i = 0; i < strlen(input); i++) {
        rand = lcg(rand); // Generate the next random number
        input[i]^= rand % 256; // XOR the character with a random byte (0-255)
    }
}

// SUBTRACTIVE METHOD
// Function to generate the 55-byte seed
void generateKey(unsigned char key[55]) {
    printf("Enter 55 seed values (0-255):\n");
    for (int i = 0; i < 55; i++) { // Loop for 55 values
        scanf("%hhu", &key[i]);
    }
}

// Generate the next number in the subtractive PRNG
unsigned char generateNext(unsigned char state[55], int *index) {
    unsigned char nextValue = (state[(*index - 24 + 55) % 55] - state[(*index - 55 + 55) % 55]) % 256; // m = 256
    state[*index] = nextValue; // Store the new value
    *index = (*index + 1) % 55; // Update the index circularly
    return nextValue; // Return the generated value
}

// Encrypt/Decrypt function using the subtractive method
void encrypt2(char *input, unsigned char state[55]) {
    int index = 0; // Index for the state array
    for (int i = 0; i < strlen(input); i++) {
        unsigned char key = generateNext(state, &index); // Generate the next pseudorandom number
        input[i] ^= key; // XOR the character with a pseudorandom byte
    }
}

int main() {
    unsigned char state[55]; // Array to store the last 55 values for subtractive method
    char input[1024]; // Buffer to hold the input string
    char copy[1024]; // Buffer to hold a copy of the input string
    int seed; // Seed for LCG method

    // Read the input string
    printf("Enter the input string:\n");
    scanf(" %[^\n]", input); // Read string input with spaces
    strcpy(copy, input); // Copy the input string into the 'copy' buffer

    // OPTION 1: LCG Method
    printf("Enter the LCG seed value:\n");
    scanf("%d", &seed); // Read seed value

    // Encrypt the input string using the LCG method
    encrypt1(input, seed);

    // Print encrypted string
    printf("Encrypted string (LCG):\n%s\n", input);

    // Decrypt the input string using the same LCG method
   // strcpy(input, copy); // Restore the original string from the copy
    encrypt1(input, seed); // XORing again retrieves the original string

    // Print decrypted string
    printf("Decrypted string (LCG):\n%s\n", input);

    // OPTION 2: Subtractive Method
    generateKey(state); // Get the seed values for the subtractive method

    // Encrypt the input string using the subtractive method
    strcpy(input, copy); // Restore the original string from the copy
    encrypt2(input, state);

    // Print encrypted string
    printf("Encrypted string (Subtractive):\n%s\n", input);

    // Re-initialize the state array before decrypting (to ensure it's reset to the same initial state)
    generateKey(state); // Re-initialize the state

    // Decrypt the input string using the same subtractive method
    encrypt2(input, state); // XORing again retrieves the original string

    // Print decrypted string
    printf("Decrypted string (Subtractive):\n%s\n", input);

    return 0;
}
