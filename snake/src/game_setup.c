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
    
    return initialize_default_board(cells_p, width_p, height_p);

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
    // TODO: implement!


    // Keep Snake Count
    int s_count = 0;

    // Search for substring for number of rows and columns
    char e_x = strchr(compressed, 'x');  
    int index_x = (int)(e_x - string); // Index for 'x'

    char e_y = strchr(compressed, '|');
    int index_y = (int)(e_y - string); // Index for first '|'
    
    int row_n = substr(compressed, 0, e_x)
    int column_n = substr(compressed, 0, e_y)

    // Variables to use with the loops to keep track of compressed notation
    // In the end row_n need to match row_count (same for column)
    int row_count = 0
    int column_count = 0


    for (int i = 0; i < len(compressed); ++i) {
        if (compressed[i] == 'S') {
            s_count++;
        }
        else if (compressed[i] == '|') {
            row_count++;
        }
        else if ((compressed[i] == 'W') || (compressed[i] == 'E') )
    }

    if (s_count != 1){
        return INIT_ERR_WRONG_SNAKE_NUM;
    }

    if ((row_count != row_n) || (column_count != column_n)) {
        return INIT_ERR_INCORRECT_DIMENSIONS
    }

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

    //Potential Errors:

        // return INIT_ERR_INCORRECT_DIMENSIONS;
            //-> If more/less rows than specified in between compressed[0] and the first x is (rows are separated by | character)
                // Can count how many | characters to count number of rows
            //-> If more/less columns that specified in between the first x and the first |. 
                // Count all of the numbers after each | 
                // TODO: figure out how to count each row (count number after every W and E? )
        
        // return INIT_ERR_WRONG_SNAKE_NUM;
            // If more/less than 1 appearance of the letter S in the whole board
                
        //INIT_ERR_BAD_CHAR
            // If any characters that are not: B, x, 1,2,3,4,5,6,7,8,9,0, W, E, S  appear on the board. 

        // Else: init success. 

    return INIT_UNIMPLEMENTED;
}
