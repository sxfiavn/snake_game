#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "linked_list.h"
#include "mbstrings.h"

/** Updates the game by a single step, and modifies the game information
 * accordingly. Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - width: width of the board.
 *  - height: height of the board.
 *  - snake_p: pointer to your snake struct (not used until part 2!)
 *  - input: the next input.
 *  - growing: 0 if the snake does not grow on eating, 1 if it does.
 */
void update(int* cells, size_t width, size_t height, snake_t* snake_p,
            enum input_key input, int growing) {
    // `update` should update the board, your snake's data, and global
    // variables representing game information to reflect new state. If in the
    // updated position, the snake runs into a wall or itself, it will not move
    // and global variable g_game_over will be 1. Otherwise, it will be moved
    // to the new position. If the snake eats food, the game score (`g_score`)
    // increases by 1. This function assumes that the board is surrounded by
    // walls, so it does not handle the case where a snake runs off the board.

    // TODO: implement!

    //Current Snake Position
    int old_cell = (width * (g_snake_row)) + g_snake_column;

    if (g_direction != INPUT_NONE) {
        g_direction = input;
    }

    if (g_direction == INPUT_RIGHT) {
        g_snake_column++;
    }
    if (g_direction == INPUT_LEFT) {
        g_snake_column--;
    }
    if (g_direction == INPUT_UP) {
        g_snake_row--;
    }
    if (g_direction == INPUT_DOWN) {
        g_snake_row++;
    }

    // New Snake Position
    int new_cell = (width * (g_snake_row)) + g_snake_column;

    if (cells[new_cell] == FLAG_WALL || cells[new_cell] == FLAG_SNAKE) {
        g_game_over = 1;
    }
    else if (cells[new_cell] == FLAG_FOOD) {
        g_score++;
        cells[old_cell] = FLAG_PLAIN_CELL;
        cells[new_cell] = FLAG_SNAKE;
        place_food(cells, width, height);
    }
    else {
        cells[old_cell] = FLAG_PLAIN_CELL;
        cells[new_cell] = FLAG_SNAKE;
    }
    
}

/** Sets a random space on the given board to food.
 * Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - width: the width of the board
 *  - height: the height of the board
 */
void place_food(int* cells, size_t width, size_t height) {
    /* DO NOT MODIFY THIS FUNCTION */
    unsigned food_index = generate_index(width * height);
    if (*(cells + food_index) == FLAG_PLAIN_CELL) {
        *(cells + food_index) = FLAG_FOOD;
    } else {
        place_food(cells, width, height);
    }
    /* DO NOT MODIFY THIS FUNCTION */
}

/** Prompts the user for their name and saves it in the given buffer.
 * Arguments:
 *  - `write_into`: a pointer to the buffer to be written into.
 */
void read_name(char* write_into) {
    // TODO: implement! (remove the call to strcpy once you begin your
    // implementation)
    strcpy(write_into, "placeholder");
}

/** Cleans up on game over — should free any allocated memory so that the
 * LeakSanitizer doesn't complain.
 * Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - snake_p: a pointer to your snake struct. (not needed until part 2)
 */
void teardown(int* cells, snake_t* snake_p) {
    // TODO: implement!
}
