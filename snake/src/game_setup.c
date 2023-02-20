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
    enum board_init_status board;
    if (board_rep == NULL){
        board = initialize_default_board(cells_p, width_p, height_p);
        place_food(*cells_p, *width_p, *height_p);
        g_snake_column = 2;
        g_snake_row = 2;
        g_direction = INPUT_RIGHT; 
    
    }
    else {
        board = decompress_board_str(cells_p, width_p, height_p, snake_p, board_rep);
    }

    return board;
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
    
    size_t x_index = 0;

    for (size_t i = 0; i < strlen(compressed); ++i) { //For the length of the string - 1 (to index correctly)

        char comp = compressed[i];
        printf("%d/n", compressed[i]); // getting the value at this address
        int s_number = atoi(&compressed[i+1]); //pointer to the first number right after the current character. 

        if (comp == 'B') {
            printf("%p/n", (void*)*height_p);
            *height_p = s_number; //get number of rows
            printf("%p/n", (void*)*height_p);
        }
        else if (comp == 'x') {
            x_index = i;
            *width_p = s_number; // get numbers of columns
        }
    }

    int snake_count = 0; 
    int row_count = 0;
    int column_count = 0;


    //Pointer to keep track of expanded W and E (acts like an array)
    int* cells = malloc(*height_p * *width_p * sizeof(int)); //setting up array
    printf("%p/n", *cells_p);
    *cells_p = cells;

    int where_in_array = 0;

    for (size_t z = x_index + 1; z < (strlen(compressed) - x_index); ++z) {

        char comp = compressed[z]; //getting the value at this address
        printf("%d/n", compressed[z]);
        int s_number = atoi(&compressed[z+1]); //compressed is a pointer -> check if it works 

        if (comp == 'S') {
            snake_count = snake_count + s_number;

            if (snake_count != 1){ //we know it cant be smaller than 1
                //free(*cells_p);
                printf("snake_count != 1");
                return INIT_ERR_WRONG_SNAKE_NUM;
            }
            else {
                cells[where_in_array] = FLAG_SNAKE;
                where_in_array++;                
            }
        }

        else if (comp == 'W') {
            printf("%d\n",column_count);
            column_count = column_count + s_number; // same as for 'S'.
            printf("%d\n",s_number);
            printf("%d\n",column_count);

            if (column_count > (int)*width_p) {
                //free(*cells_p);
                return INIT_ERR_INCORRECT_DIMENSIONS;   // not handling if its smaller than column_n
            }
            else {
                for (int a = where_in_array; a < (s_number + where_in_array); ++a) {
                    printf("%d\n", s_number + where_in_array);
                    cells[a] = FLAG_PLAIN_CELL;
                    printf("%d\n", cells[a]);
                    printf("%d\n", where_in_array);
                }
                where_in_array = s_number + where_in_array;
            }
        }

        else if (comp == 'E') { //given the number after the E
            column_count = column_count + s_number; 
            
            if (column_count > (int)*width_p) {
                //free(*cells_p);
                return INIT_ERR_INCORRECT_DIMENSIONS;   // not handling if its smaller than column_n
            }
            else {
                for (int a = where_in_array; a < (s_number + where_in_array); ++a) {
                    cells[a] = FLAG_PLAIN_CELL;
                }
                where_in_array = s_number + where_in_array;
            }
        }

        else if (comp == '|') {
            row_count++;
            column_count = 0;

            if (row_count > (int)*height_p) {
                //free(*cells_p);
                return INIT_ERR_INCORRECT_DIMENSIONS;
            }
        }

        else if (((comp < DIGIT_START) || (comp > DIGIT_END))) { 
            //free(*cells_p);
            return INIT_ERR_BAD_CHAR; 
        }
        
    }

    if ((column_count > (int)*width_p) || (row_count > (int)*height_p)) {
        //free(*cells_p);
        return INIT_ERR_INCORRECT_DIMENSIONS;
    }

    return INIT_SUCCESS;
}
