#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "linked_list.h"
#include "mbstrings.h"



void update_down_helper(int curr_snake_coord_first, int curr_snake_coord_last, enum input_key current_direction, int snake_grows, size_t width, snake_t* snake_p, int* cells, size_t height) {

    if((cells[curr_snake_coord_first + (int)width] == FLAG_SNAKE)  && (curr_snake_coord_last != (curr_snake_coord_first + (int)width))) {
        g_game_over = 1;
        return;
    } 
            
    else {
        current_direction = INPUT_DOWN;
        snake_p->snake_direction = current_direction;

        int curr_snake_coord_first_local = *((int*)get_first(snake_p->snake_coordinates)); 

        if(cells[curr_snake_coord_first_local + width] == FLAG_FOOD) {
            
            if (snake_grows == 1) {
                g_score++; // Eating increases score
                curr_snake_coord_first_local = curr_snake_coord_first_local + width; 
                cells[curr_snake_coord_first_local] = FLAG_SNAKE;
                insert_first(&(snake_p->snake_coordinates), &curr_snake_coord_first_local, sizeof(int));
                place_food(cells, width, height); // Replaces food
            }

            else if (snake_grows == 0) { 
                g_score++; // Eating increases score
                place_food(cells, width, height);

                curr_snake_coord_first_local = curr_snake_coord_first_local + width;
                cells[curr_snake_coord_first_local] = FLAG_SNAKE;
                cells[curr_snake_coord_last] = FLAG_PLAIN_CELL;
                insert_first(&(snake_p->snake_coordinates), &curr_snake_coord_first_local, sizeof(int));

                void* to_remove = remove_last(&(snake_p->snake_coordinates));
                free(to_remove);
                

            }
        }

        else { 
            curr_snake_coord_first_local = curr_snake_coord_first_local + width; //still decreasing the position pointer
            cells[curr_snake_coord_last] = FLAG_PLAIN_CELL; //if its not food, the snake will move one to the left
            cells[curr_snake_coord_first_local] = FLAG_SNAKE; //the -1 position is a snake
            insert_first(&(snake_p->snake_coordinates), &curr_snake_coord_first_local, sizeof(int));

            void* to_remove = remove_last(&(snake_p->snake_coordinates));
            free(to_remove);
        }
    }
}




void update_up_helper(int curr_snake_coord_first, int curr_snake_coord_last, enum input_key current_direction, int snake_grows, size_t width, snake_t* snake_p, int* cells, size_t height) {

    if((cells[curr_snake_coord_first - (int)width] == FLAG_SNAKE) && (curr_snake_coord_last != (curr_snake_coord_first - (int)width))) {
        g_game_over = 1;
        return;
    } 
            
    else {
        current_direction = INPUT_UP;
        snake_p->snake_direction = current_direction;

        int curr_snake_coord_first_local = *((int*)get_first(snake_p->snake_coordinates)); 

        if(cells[curr_snake_coord_first_local - width] == FLAG_FOOD) {
            
            if (snake_grows == 1) {
                g_score++; // Eating increases score
                curr_snake_coord_first_local = curr_snake_coord_first_local - width; 
                cells[curr_snake_coord_first_local] = FLAG_SNAKE;
                insert_first(&(snake_p->snake_coordinates), &curr_snake_coord_first_local, sizeof(int));
                place_food(cells, width, height); // Replaces food
            }

            else if (snake_grows == 0) { 
                g_score++; // Eating increases score
                place_food(cells, width, height);
                curr_snake_coord_first_local = curr_snake_coord_first_local - width;
                cells[curr_snake_coord_first_local] = FLAG_SNAKE;
                cells[curr_snake_coord_last] = FLAG_PLAIN_CELL;
                insert_first(&(snake_p->snake_coordinates), &curr_snake_coord_first_local, sizeof(int));

                void* to_remove = remove_last(&(snake_p->snake_coordinates));
                free(to_remove);
            }
        }

        else { 
            curr_snake_coord_first_local = curr_snake_coord_first_local - width; //still decreasing the position pointer
            cells[curr_snake_coord_last] = FLAG_PLAIN_CELL; //if its not food, the snake will move one to the left
            cells[curr_snake_coord_first_local] = FLAG_SNAKE; //the -1 position is a snake
            insert_first(&(snake_p->snake_coordinates), &curr_snake_coord_first_local, sizeof(int));

            void* to_remove = remove_last(&(snake_p->snake_coordinates));
            free(to_remove);
        }
    }

}




void update_right_helper(int curr_snake_coord_first, int curr_snake_coord_last, enum input_key current_direction, int snake_grows, size_t width, snake_t* snake_p, int* cells, size_t height) {
    if((cells[curr_snake_coord_first + 1] == FLAG_SNAKE) && (curr_snake_coord_last != (curr_snake_coord_first + 1))) {
        g_game_over = 1;
        return;
    } 
            
    else {
        current_direction = INPUT_RIGHT;
        snake_p->snake_direction = current_direction;

        int curr_snake_coord_first_local = *((int*)get_first(snake_p->snake_coordinates)); 

        if(cells[curr_snake_coord_first_local + 1] == FLAG_FOOD) {
            
            if (snake_grows == 1) {
                g_score++; // Eating increases score
                curr_snake_coord_first_local++; 
                cells[curr_snake_coord_first_local] = FLAG_SNAKE; //already the +1 from line above
                insert_first(&(snake_p->snake_coordinates), &curr_snake_coord_first_local, sizeof(int));
                place_food(cells, width, height); // Replaces food
            }
            else if (snake_grows == 0) { 
                g_score++; // Eating increases score
                place_food(cells, width, height);

                curr_snake_coord_first_local++; 
                cells[curr_snake_coord_first_local] = FLAG_SNAKE;
                cells[curr_snake_coord_last] = FLAG_PLAIN_CELL;
                insert_first(&(snake_p->snake_coordinates), &curr_snake_coord_first_local, sizeof(int));

                void* to_remove = remove_last(&(snake_p->snake_coordinates));
                free(to_remove);
            }
        }

        else { 
            curr_snake_coord_first_local++; //still decreasing the position pointer
            cells[curr_snake_coord_last] = FLAG_PLAIN_CELL; //if its not food, the snake will move one to the left
            cells[curr_snake_coord_first_local] = FLAG_SNAKE; //the -1 position is a snake
            insert_first(&(snake_p->snake_coordinates), &curr_snake_coord_first_local, sizeof(int));

            void* to_remove = remove_last(&(snake_p->snake_coordinates));
            free(to_remove);
        }
    }

}



void update_left_helper(int curr_snake_coord_first, int curr_snake_coord_last, enum input_key current_direction, int snake_grows, size_t width, snake_t* snake_p, int* cells, size_t height) {
    //Check if the head is a snake and if the last and first position have the same coordinates (they touch), game over. 
    if((cells[curr_snake_coord_first - 1] == FLAG_SNAKE) && (curr_snake_coord_last != (curr_snake_coord_first - 1))){ //so that they dont overlap
        g_game_over = 1;
        return;
    }    
            
    else {
        current_direction = INPUT_LEFT;
        snake_p->snake_direction = current_direction;

        int curr_snake_coord_first_local = *((int*)get_first(snake_p->snake_coordinates)); 
                
        if(cells[curr_snake_coord_first_local - 1] == FLAG_FOOD) {

            if (snake_grows == 1) {
                g_score++; // Eating increases score
                curr_snake_coord_first_local--; 
                cells[curr_snake_coord_first_local] = FLAG_SNAKE;
                insert_first(&(snake_p->snake_coordinates), &curr_snake_coord_first_local, sizeof(int));
                place_food(cells, width, height); // Replaces food
            }

            else if (snake_grows == 0) { 
                g_score++; // Eating increases score
                place_food(cells, width, height);


                curr_snake_coord_first_local--;
                cells[curr_snake_coord_first_local] = FLAG_SNAKE;
                cells[curr_snake_coord_last] = FLAG_PLAIN_CELL;
                insert_first(&(snake_p->snake_coordinates), &curr_snake_coord_first_local, sizeof(int));

                void* to_remove = remove_last(&(snake_p->snake_coordinates));
                free(to_remove);
            }
        }

        else { 
            curr_snake_coord_first_local--; //still decreasing the position pointer
            cells[curr_snake_coord_last] = FLAG_PLAIN_CELL; //if its not food, the snake will move one to the left
            cells[curr_snake_coord_first_local] = FLAG_SNAKE; //the -1 position is a snake
            insert_first(&(snake_p->snake_coordinates), &curr_snake_coord_first_local, sizeof(int));

            void* to_remove = remove_last(&(snake_p->snake_coordinates));
            free(to_remove);
        }
    }

}



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
    enum input_key current_direction = snake_p->snake_direction;

    if (g_game_over != 1) {

        //Current Snake Position - Global
        int curr_snake_coord_first = *((int*)get_first(snake_p->snake_coordinates));   
        int curr_snake_coord_last = *((int*)get_last(snake_p->snake_coordinates)); 

        
        // Dealing with extra cases

        //If the snake is growing and its size (has more than 1 coordinate) is bigger than 1:
        // Make sure that the snake cant turn around and 'overlap' with the rest of the body
        // As per instructions: In the actual snake game, if the snake is length 2 or longer and immediately tries to go back the way it came (backing into itself), the movement 
        // is not accepted and the snake continues to move in its previous direction.
        if ((growing == 1) && (length_list(snake_p->snake_coordinates) > 1)) {
            if((current_direction == INPUT_UP) && input == INPUT_DOWN){
                input = INPUT_UP;
            }
            if((current_direction == INPUT_DOWN) && input == INPUT_UP){
                input = INPUT_DOWN;
            }
            if((current_direction == INPUT_LEFT) && input == INPUT_RIGHT){
                input = INPUT_LEFT;
            }
            if((current_direction == INPUT_RIGHT) && input == INPUT_LEFT) { 
                input = INPUT_RIGHT;
            }
        }

        //Handling Walls (game over)
        if (((cells[curr_snake_coord_first + width] == FLAG_WALL) && input == INPUT_DOWN) || 
            ((cells[curr_snake_coord_first - width] == FLAG_WALL) &&  input == INPUT_UP) || 
            ((cells[curr_snake_coord_first + 1] == FLAG_WALL) && input == INPUT_RIGHT) || 
            ((cells[curr_snake_coord_first - 1] == FLAG_WALL) && input == INPUT_LEFT))
            { 
            g_game_over = 1;
            return;
            }
     
        if (input == INPUT_NONE) {
            //input = *((int*)get_first(snake_p->snake_direction)); //If not, should keep moving to where it was before. 
            
            if (current_direction == INPUT_DOWN) {
                if ((cells[curr_snake_coord_first + width] == FLAG_WALL)) {
                    g_game_over = 1;
                    return;
                }
                update_down_helper(curr_snake_coord_first, curr_snake_coord_last, current_direction, growing, width, snake_p, cells, height);
            }

            //Case when user is clicking the upwards arrow button
            if (current_direction == INPUT_UP) {
                if ((cells[curr_snake_coord_first - width] == FLAG_WALL)) {
                    g_game_over = 1;
                    return;
                }
                update_up_helper(curr_snake_coord_first, curr_snake_coord_last, current_direction, growing, width, snake_p, cells, height);
            }
                
            //Case when user is clicking the right button
            if (current_direction == INPUT_RIGHT) {
                if ((cells[curr_snake_coord_first + 1] == FLAG_WALL)) {
                    g_game_over = 1;
                    return;
                }
                update_right_helper(curr_snake_coord_first, curr_snake_coord_last, current_direction, growing, width, snake_p, cells, height);
            }

            //Case when the user is clicking the left arrow
            if(current_direction == INPUT_LEFT){
                if ((cells[curr_snake_coord_first - 1] == FLAG_WALL)) {
                    g_game_over = 1;
                    return;
                }
                update_left_helper(curr_snake_coord_first, curr_snake_coord_last, current_direction, growing, width, snake_p, cells, height);
            }
        }

        //When input from user is downwards key
        if (input == INPUT_DOWN) {
            update_down_helper(curr_snake_coord_first, curr_snake_coord_last, current_direction, growing, width, snake_p, cells, height);
        }

        //Case when user is clicking the upwards arrow button
        if (input == INPUT_UP) {
            update_up_helper(curr_snake_coord_first, curr_snake_coord_last, current_direction, growing, width, snake_p, cells, height);
        }
            
        //Case when user is clicking the right button
        if (input == INPUT_RIGHT) {
            update_right_helper(curr_snake_coord_first, curr_snake_coord_last, current_direction, growing, width, snake_p, cells, height);
        }

        //Case when the user is clicking the left arrow
        if(input == INPUT_LEFT) {
            update_left_helper(curr_snake_coord_first, curr_snake_coord_last, current_direction, growing, width, snake_p, cells, height);
        }

    }
    else if (g_game_over == 1){
        return;
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
    //strcpy(write_into, "placeholder");

    //Print Out Prompt For User
    printf("Name >\n");

    //To read their response (first input is 0: indicating should read it as std input)
    int response = (int)read(0, write_into, 1000); 

    //While their response is invalid
    while (response == 1) {
        printf("Name Invalid: must be longer than 0 characters.\n"); //throw message

        //Prompt to their input again
        printf("Name >\n");
        response = (int)read(0, write_into, 1000);
    }

    write_into[response - 1] = '\0'; //A Null byte, indicate end of string
}


/** Cleans up on game over — should free any allocated memory so that the
 * LeakSanitizer doesn't complain.
 * Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - snake_p: a pointer to your snake struct. (not needed until part 2)
 */
void teardown(int* cells, snake_t* snake_p) {
    free(cells);
    free(snake_p->snake_coordinates);
}
