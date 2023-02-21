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
    enum input_key current_direction = INPUT_RIGHT;

    if (g_game_over != 1) {

        //Current Snake Position - Global
        int curr_snake_coord_first = *((int*)get_first(snake_p->snake_coordinates));   
        int curr_snake_coord_last = *((int*)get_last(snake_p->snake_coordinates)); 

        
        // Dealing with extra cases

        //Ways the game is over
        if ((cells[curr_snake_coord_first + width] == FLAG_WALL) && (current_direction == INPUT_DOWN) && (input == INPUT_DOWN)) {
            g_game_over = 1;
        }
        if ((cells[curr_snake_coord_first - width] == FLAG_WALL) && (current_direction == INPUT_UP) && (input == INPUT_UP)) {
            g_game_over = 1; 
        }

        if ((cells[curr_snake_coord_first + 1] == FLAG_WALL) && (current_direction == INPUT_RIGHT) && (input == INPUT_RIGHT)) {
            g_game_over = 1;
        }
        if ((cells[curr_snake_coord_first - 1] == FLAG_WALL) && (current_direction == INPUT_LEFT) && (input == INPUT_LEFT)) {
            g_game_over = 1;
        } 

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

        

        if (input == INPUT_NONE) {
            input = *((int*)get_first(snake_p->snake_direction)); //If not, should keep moving to where it was before. 
            //TODO: IMPLEMENT
        }

    //When input from user is downwards key
    if (input == INPUT_DOWN){

        if((cells[curr_snake_coord_first + (int)width] == FLAG_SNAKE) 
        && (curr_snake_coord_last != (curr_snake_coord_first + (int)width))){
            g_game_over = 1;
        } 
        
        else {
            current_direction = INPUT_UP;
            snake_p->snake_direction = current_direction;

            int curr_snake_coord_first_local = *((int*)get_first(snake_p->snake_coordinates)); 

            if(cells[curr_snake_coord_first - width] == FLAG_FOOD){
        
                    if (growing == 1) {
                        g_score++; // Eating increases score
                        curr_snake_coord_first_local = curr_snake_coord_first_local + width; 
                        cells[curr_snake_coord_first_local] = FLAG_SNAKE;
                        insert_first(&(snake_p->snake_coordinates), &curr_snake_coord_first_local, sizeof(int));
                        place_food(cells, width, height); // Replaces food
                    }

                    else if (growing == 0) { 
                        g_score++; // Eating increases score
                        place_food(cells, width, height); // Replaces food
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

    //Case when user is clicking the upwards arrow button
    if (input == INPUT_UP){

        if((cells[curr_snake_coord_first - (int)width] == FLAG_SNAKE) 
        && (curr_snake_coord_last != (curr_snake_coord_first - (int)width))){
            g_game_over = 1;
        } 
        
        else {
            current_direction = INPUT_UP;
            snake_p->snake_direction = current_direction;

            int curr_snake_coord_first_local = *((int*)get_first(snake_p->snake_coordinates)); 

            if(cells[curr_snake_coord_first - width] == FLAG_FOOD){
        
                    if (growing == 1) {
                        g_score++; // Eating increases score
                        curr_snake_coord_first_local = curr_snake_coord_first_local - width; 
                        cells[curr_snake_coord_first_local] = FLAG_SNAKE;
                        insert_first(&(snake_p->snake_coordinates), &curr_snake_coord_first_local, sizeof(int));
                        place_food(cells, width, height); // Replaces food
                    }

                    else if (growing == 0) { 
                        g_score++; // Eating increases score
                        place_food(cells, width, height); // Replaces food
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
        


    //Case when user is clicking the right button
    if (input == INPUT_RIGHT){

        if((cells[curr_snake_coord_first + 1] == FLAG_SNAKE) 
        && (curr_snake_coord_last != (curr_snake_coord_first + 1))){
            g_game_over = 1;
        } 
        
        else {
            current_direction = INPUT_RIGHT;
            snake_p->snake_direction = current_direction;

            int curr_snake_coord_first_local = *((int*)get_first(snake_p->snake_coordinates)); 

            if(cells[curr_snake_coord_first + 1] == FLAG_FOOD){
        
                    if (growing == 1) {
                        g_score++; // Eating increases score
                        curr_snake_coord_first_local++; 
                        cells[curr_snake_coord_first_local] = FLAG_SNAKE;
                        insert_first(&(snake_p->snake_coordinates), &curr_snake_coord_first_local, sizeof(int));
                        place_food(cells, width, height); // Replaces food
                    }

                    else if (growing == 0) { 
                        g_score++; // Eating increases score
                        place_food(cells, width, height); // Replaces food
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


     //Case when the user is clicking the left arrow
        if(input == INPUT_LEFT){

            //Check if the head is a snake and if the last and first position have the same coordinates (they touch), game over. 
            if((cells[curr_snake_coord_first - 1] == FLAG_SNAKE) && (curr_snake_coord_last != (curr_snake_coord_first - 1))){
                g_game_over = 1;
        
            else {
                current_direction = INPUT_LEFT;
                snake_p->snake_direction = current_direction;
            
                if(cells[curr_snake_coord_first - 1] == FLAG_FOOD){
                    int curr_snake_coord_first_local = *((int*)get_first(snake_p->snake_coordinates)); 
                    if (growing == 1) {
                        g_score++; // Eating increases score
                        curr_snake_coord_first_local--; 
                        cells[curr_snake_coord_first_local] = FLAG_SNAKE;
                        insert_first(&(snake_p->snake_coordinates), &curr_snake_coord_first_local, sizeof(int));
                        place_food(cells, width, height); // Replaces food
                    }

                    else if (growing == 0) { 
                        g_score++; // Eating increases score
                        place_food(cells, width, height); // Replaces food
                    }
                }

                else { 
                    int curr_snake_coord_first_local = *((int*)get_first(snake_p->snake_coordinates)); 
                    curr_snake_coord_first_local--; //still decreasing the position pointer
                    cells[curr_snake_coord_last] = FLAG_PLAIN_CELL; //if its not food, the snake will move one to the left
                    cells[curr_snake_coord_first_local] = FLAG_SNAKE; //the -1 position is a snake
                    insert_first(&(snake_p->snake_coordinates), &curr_snake_coord_first_local, sizeof(int));
                    void* to_remove = remove_last(&(snake_p->snake_coordinates));
                    free(to_remove);
                }
            }
        }
    }







        // New Snake Position
        int new_cell = *((int*)get_first(snake_p->snake_coordinates));

        if (cells[new_cell] == FLAG_WALL || cells[new_cell] == FLAG_SNAKE) {
            g_game_over = 1;
            return;
        }

        else if (cells[new_cell] == FLAG_FOOD) {
            g_score++; //Ate food, should be more
            cells[old_cell] = FLAG_PLAIN_CELL;
            cells[new_cell] = FLAG_SNAKE;
            place_food(cells, width, height); //Place new food
        }


        else {
            cells[old_cell] = FLAG_PLAIN_CELL;
            cells[new_cell] = FLAG_SNAKE;
        }
    }
    else {
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
    free(cells);
}
