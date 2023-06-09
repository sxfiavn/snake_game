#include "common.h"

#include <stdlib.h>

// TODO: define global variables needed for your snake! (part 1A)
int g_game_over;  // 1 if game is over, 0 otherwise
int g_score;      // game score: 1 point for every food eaten
// enum input_key g_direction; // direction of the snake
// int g_snake_column; //horizontal position of snake (when used as index, position 3 (0,1,2,3))
// int g_snake_row; //vertical position of snake (same as above with index)

//
int g_name_len;
char* g_name;

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
