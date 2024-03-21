#include <stdio.h>
#include <stdint.h>

#define STATE_SIZE 200 // Example size for demonstration purposes

// Function to initialize the state matrix with zeros
void initialize_state(uint64_t state[][STATE_SIZE]) {
    for (int i = 0; i < STATE_SIZE; i++) {
        for (int j = 0; j < STATE_SIZE; j++) {
            state[i][j] = 0;
        }
    }
}

// Function to simulate diffusion over a certain number of rounds
void simulate_diffusion(uint64_t state[][STATE_SIZE], int rounds) {
    for (int r = 0; r < rounds; r++) {
        // Perform diffusion operations (not shown, since we're ignoring the permutation)
        // For demonstration, let's just toggle the bits in some random lanes
        for (int i = 0; i < STATE_SIZE; i++) {
            for (int j = 0; j < STATE_SIZE; j++) {
                if ((i + j + r) % 2 == 0) { // Example condition for toggling bits
                    state[i][j] ^= 1;
                }
            }
        }
    }
}

// Function to check if all lanes have at least one nonzero bit
int check_nonzero_bits(uint64_t state[][STATE_SIZE]) {
    for (int i = 0; i < STATE_SIZE; i++) {
        for (int j = 0; j < STATE_SIZE; j++) {
            if (state[i][j] != 0) {
                return 1; // Found a nonzero bit
            }
        }
    }
    return 0; // All lanes have zero bits
}

int main() {
    uint64_t state[STATE_SIZE][STATE_SIZE];
    int rounds = 0;

    // Initialize the state matrix with zeros
    initialize_state(state);

    // Simulate diffusion until all lanes have at least one nonzero bit
    while (!check_nonzero_bits(state)) {
        simulate_diffusion(state, 1); // Simulate one round of diffusion
        rounds++;
    }

    // Output the number of rounds required
    printf("Number of rounds required for all lanes to have nonzero bits: %d\n", rounds);

    return 0;
}
