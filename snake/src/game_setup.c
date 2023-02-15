#include "game_setup.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Some handy dandy macros for decompression
#define E_CAP_HEX 0x45
#define E_LOW_HEX 0x65
#define S_CAP_HEX 0x53
#define S_LOW_HEX 0x73
#define W_CAP_HEX 0x57
#define W_LOW_HEX 0x77
#define DIGIT_START 0x30
#define DIGIT_END 0x39

/** Initializes the board with walls around the edge of the board.
 *
 * Modifies values pointed to by cells_p, width_p, and height_p and initializes
 * cells array to reflect this default board.
 *
 * Returns INIT_SUCCESS to indicate that it was successful.
 *
 * Arguments:
 *  - cells_p: a pointer to a memory location where a pointer to the first
 *             element in a newly initialized array of cells should be stored.
 *  - width_p: a pointer to a memory location where the newly initialized
 *             width should be stored.
 *  - height_p: a pointer to a memory location where the newly initialized
 *              height should be stored.
 */
enum board_init_status initialize_default_board(int** cells_p, size_t* width_p,
                                                size_t* height_p) {
    *width_p = 20;
    *height_p = 10;
    int* cells = malloc(20 * 10 * sizeof(int));
    *cells_p = cells;
    for (int i = 0; i < 20 * 10; i++) {
        cells[i] = FLAG_PLAIN_CELL;
    }

    // Set edge cells!
    // Top and bottom edges:
    for (int i = 0; i < 20; ++i) {
        cells[i] = FLAG_WALL;
        cells[i + (20 * (10 - 1))] = FLAG_WALL;
    }
    // Left and right edges:
    for (int i = 0; i < 10; ++i) {
        cells[i * 20] = FLAG_WALL;
        cells[i * 20 + 20 - 1] = FLAG_WALL;
    }

    // Add snake
    cells[20 * 2 + 2] = FLAG_SNAKE;

    return INIT_SUCCESS;
}

/** Initialize variables relevant to the game board.
 * Arguments:
 *  - cells_p: a pointer to a memory location where a pointer to the first
 *             element in a newly initialized array of cells should be stored.
 *  - width_p: a pointer to a memory location where the newly initialized
 *             width should be stored.
 *  - height_p: a pointer to a memory location where the newly initialized
 *              height should be stored.
 *  - snake_p: a pointer to your snake struct (not used until part 2!)
 *  - board_rep: a string representing the initial board. May be NULL for
 * default board.
 */
enum board_init_status initialize_game(int** cells_p, size_t* width_p,
                                       size_t* height_p, snake_t* snake_p,
                                       char* board_rep) {
    // TODO: implement!
    board =  initialize_default_board(cells_p, width_p, height_p);
    place_food(*cells_p, *width_p, *height_p);
    return board;
    
    // if (board_rep == NULL){
    //     place_food(*cells_p, *width_p, *height_p);
    //     return initialize_default_board(cells_p, width_p, height_p); 
    // }
    // else {
    //     return decompress_board_str(cells_p, width_p, height_p, snake_p, board_rep);
    // }
}

/** Takes in a string `compressed` and initializes values pointed to by
 * cells_p, width_p, and height_p accordingly. Arguments:
 *      - cells_p: a pointer to the pointer representing the cells array
 *                 that we would like to initialize.
 *      - width_p: a pointer to the width variable we'd like to initialize.
 *      - height_p: a pointer to the height variable we'd like to initialize.
 *      - snake_p: a pointer to your snake struct (not used until part 2!)
 *      - compressed: a string that contains the representation of the board.
 * Note: We assume that the string will be of the following form:
 * B24x80|E5W2E73|E5W2S1E72... To read it, we scan the string row-by-row
 * (delineated by the `|` character), and read out a letter (E, S or W) a number
 * of times dictated by the number that follows the letter.
 */
enum board_init_status decompress_board_str(int** cells_p, size_t* width_p,
                                            size_t* height_p, snake_t* snake_p,
                                            char* compressed) {
    

    for (size_t i = 0; i < (strlen(compressed) - 1); ++i) {

        char comp = compressed[i]; // getting the value at this address
        int s_number = atoi(&compressed[i+1]); //pointer to the first number right after the current character. 

        if (comp == 'B') {
            *height_p = s_number;
        }
        else if (comp == 'x') {
            *width_p = s_number;
        }
        
        if (((int)*height_p == 0) || ((int)*width_p == 0)) {
            return INIT_ERR_INCORRECT_DIMENSIONS;
        }

    }

    int snake_count = 0; 
    int row_count = 0;
    int column_count = 0;

    //Pointer to keep track of expanded W and E (acts like an array)
    int* array_board_maker = malloc(*height_p * *width_p * sizeof(int)); 
    *cells_p = array_board_maker;
    int where_in_array = 0;

    for (size_t i = 0; i < (strlen(compressed) - 1); ++i) {

        char comp = compressed[i]; //getting the value at this address
        int s_number = atoi(&compressed[i+1]); //compressed is a pointer -> check if it works 

        if (comp == 'S') {
            snake_count = snake_count + s_number;

            if (snake_count != 1){ //we know it cant be smaller than 1
                return INIT_ERR_WRONG_SNAKE_NUM;
            }
            else {
                array_board_maker[where_in_array] = FLAG_SNAKE;
                where_in_array++;
                // g_snake_column = ;
                // g_snake_row = ;
                
            }
        }

        else if (comp == 'W') {
            column_count = column_count + s_number; // same as for 'S'.
            
            if (column_count > (int)*width_p) {
                return INIT_ERR_INCORRECT_DIMENSIONS;   // not handling if its smaller than column_n
            }
            else {
                for (int a = 0; a < s_number; ++a) {
                    array_board_maker[where_in_array] = FLAG_WALL;
                    where_in_array++;
                }
            }
        }

        else if (comp == 'E') {
            column_count = column_count + s_number; // same as for 'S'.
            
            if (column_count > (int)*width_p) {
                return INIT_ERR_INCORRECT_DIMENSIONS;   // not handling if its smaller than column_n
            }
            else {
                for (int a = 0; a < s_number; ++a) {
                    array_board_maker[where_in_array] = FLAG_PLAIN_CELL;
                    where_in_array++;
                }
            }
        }

        else if (comp == '|') {
            row_count++;

            if (row_count > (int)*height_p) {
                return INIT_ERR_INCORRECT_DIMENSIONS;
            }
        }

        else if (((comp < DIGIT_START) || (comp < DIGIT_END))) { 
            return INIT_ERR_BAD_CHAR; 
        }
        
    }

    if ((column_count < (int)*width_p) || (row_count < (int)*height_p)) {
        return INIT_ERR_INCORRECT_DIMENSIONS;
    }

    return INIT_SUCCESS;
}
