#include "common.h"

#include <stdlib.h>

// TODO: define global variables needed for your snake! (part 1A)

g_game_over = 0;  // 1 if game is over, 0 otherwise
g_score = 0;      // game score: 1 point for every food eaten
g_direction = INPUT_RIGHT; // direction of the snake
g_snake_column = 2; //horizontal position of snake
g_snake_row = 2; //vertical position of snake

/** Sets the seed for random number generation.
 * Arguments:
 *  - `seed`: the seed.
 */
void set_seed(unsigned seed) {
    /* DO NOT MODIFY THIS FUNCTION */
    srand(seed);
    /* DO NOT MODIFY THIS FUNCTION */
}

/** Returns a random index in [0, size)
 * Arguments:
 *  - `size`: the upper bound for the generated value (exclusive).
 */
unsigned generate_index(unsigned size) {
    /* DO NOT MODIFY THIS FUNCTION */
    return rand() % size;
    /* DO NOT MODIFY THIS FUNCTION */
}
