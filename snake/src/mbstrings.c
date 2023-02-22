#include "mbstrings.h"

/* mbslen - multi-byte string length
 * - Description: returns the number of UTF-8 code points ("characters")
 * in a multibyte string. If the argument is NULL or an invalid UTF-8
 * string is passed, returns -1.
 *
 * - Arguments: A pointer to a character array (`bytes`), consisting of UTF-8
 * variable-length encoded multibyte code points.
 *
 * - Return: returns the actual number of UTF-8 code points in `src`. If an
 * invalid sequence of bytes is encountered, return -1.
 *
 * - Hints:
 * UTF-8 characters are encoded in 1 to 4 bytes. The number of leading 1s in the
 * highest order byte indicates the length (in bytes) of the character. For
 * example, a character with the encoding 1111.... is 4 bytes long, a character
 * with the encoding 1110.... is 3 bytes long, and a character with the encoding
 * 1100.... is 2 bytes long. Single-byte UTF-8 characters were designed to be
 * compatible with ASCII. As such, the first bit of a 1-byte UTF-8 character is
 * 0.......
 *
 * You will need bitwise operations for this part of the assignment!
 */
size_t mbslen(const char* bytes) {
    // TODO: implement!
    //return 0;
    
    if (!bytes) {  // if null
	    return -1; 
    }

    char single = 0b10000000;
    char two = 0b11100000;
    char three = 0b11110000;
    char four = 0b11111000;

    int UTF_count = 0;

    int i = 0;

    while (bytes[i] != '\0' ) { //While we haven't encountered NUL

        unsigned char unsignedb = (unsigned char)bytes[i];

        if ((single & unsignedb) == 0b0) {
            i++;
        }
        if ((two & unsignedb) == 0b11000000) {
            i+=2;
        }
        if ((three & unsignedb) == 0b11100000) {
            i+=3;
        }
        if ((four & unsignedb) == 0b11110000) {
            i+=4;
        }

        UTF_count++;

    }

    return UTF_count;
}

