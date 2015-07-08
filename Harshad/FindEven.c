/*------------------------------------------------------------------------------
 * File: FindEven.c
 * Author: Harshd
 * Date: 02-Jul-2015
 *
 * COPYRIGHT: (C) 2015 - All rights reserved - Network Marvels (I) Pvt. Ltd.,
 * Thane (India)
 *-----------------------------------------------------------------------------
 * Description: Program to find consecutive n-even numbers after certain number.
 * Numbers are first stored in char pointers named 'str_ptr1' & 'str_ptr2'.
 * str_ptr1 refers to the number from which the count should be done.
 * str_ptr2 refers to the count number.
 * The program takes input either from command line or from standard input or
 * reads from the file.
 * Program also has an option to show the help to the user by taking command
 * line argument '--help'.
 * To read input from a file '-f' option should be specified in command line
 * arguments & path to the file should be specified after that.
 *------------------------------------------------------------------------------
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *------------------------------------------------------------------------------
 */

/************************ Header files ****************************************/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
/******************************************************************************/

#define MAX_SIZE 100

char *msg = NULL;

/************************* Function Declarations ******************************/
  void FindEven(char *, char *);
  int ValidateParam(char *, char *);
/******************************************************************************/

/******************************************************************************/
int main(int argc, char *argv[]){
/******************************************************************************/

    char ch, *str_ptr1, *str_ptr2;        // pointers for numbers
    FILE *file_ptr;
        
    str_ptr1 = (char *)malloc(sizeof(char) * MAX_SIZE );
    
    if ( str_ptr1 == NULL ){
        printf("Memory to string pointer isn't allocated\n");
        exit(0);
    }

    str_ptr2 = (char *)malloc(sizeof(char) * MAX_SIZE);
    
    if ( str_ptr2 == NULL ){
        printf("Memory to string pointer 2 isn't allocated\n");
        exit(0);
    }

    msg = (char *)malloc(MAX_SIZE);
    
    if ( msg == NULL ){
        printf("Memory to message isn't allocated\n");
        exit(0);
    }
    
    strcpy(msg, "Default message\n");

	printf("\nThis program is to print n-consecutive even numbers,"
                            " given the certain number\n");

    if (argc == 2){

        // if the argument is to print help for the program
        
        if (strcmp(argv[1], "--help") == 0){

            file_ptr = fopen("FINDEVEN_README.txt", "r"); //read from file
       
            fseek(file_ptr, 0, SEEK_END);
            int f_size = ftell(file_ptr);
            
            if ( f_size == 0){
                printf("File is empty\n");
                exit(0);
            }
            else{
                fseek(file_ptr, 0, SEEK_SET);
                while ((ch = fgetc(file_ptr)) != EOF){
                    printf("%c", ch);
                }
            }
        
            fclose(file_ptr);
        }
        return 1;
    }

    else if (argc == 3){

        // if input is passed through file which is a command line argument

        if (strcmp(argv[1], "-f") == 0){

            printf("\nEntered file name: %s\n", argv[2]);
            file_ptr = fopen(argv[2], "r");
            int f_size;
            if(file_ptr != NULL){
                fseek(file_ptr, 0, SEEK_END);
                f_size = ftell(file_ptr);
                if ( f_size == 0){
                    printf("File is empty.\n");
                    exit(0);
                }
                else{
//                  printf("File Size: %d\n", f_size);
                    fseek(file_ptr, 0, SEEK_SET);
                    while( fscanf(file_ptr,"%s %s", str_ptr1, str_ptr2) != EOF ){
                        if ( ValidateParam(str_ptr1, str_ptr2) )
                            FindEven(str_ptr1, str_ptr2);
                        else
                            printf("%s", msg);
                    }
                }
                fclose(file_ptr);
                return 1;
            }
            else{
                printf("\nFile can't be opened\n");
                return 0;
            }
        }
        // numbers are passed as command line argument
        else{
                strcpy(str_ptr1, argv[1]);
                strcpy(str_ptr2, argv[2]);
        }
    }

    // numbers have to be read from standard input
    else if(argc == 1){

        printf("\nPlease enter the number you want to start from:\n");
        scanf("%s", str_ptr1);
    
        printf("\nPlease enter how many numbers you want to see:\n");
        scanf("%s", str_ptr2);
    }
    
    if ( ValidateParam(str_ptr1, str_ptr2) )
        FindEven(str_ptr1, str_ptr2);
    else
        printf("%s", msg);
    free(str_ptr1);
    free(str_ptr2);
    free(msg);
}

/*****************************************************************************/
/**                             LOCAL FUNCTIONS                             **/
/**                                                                         **/
/*****************************************************************************/

/******************************************************************************
 * Function: ValidateParam(char *, char *)
 * input: strPtr1, strPtr2
 * strPtr1 is the given number in string format.
 * strPtr2 is the count for the even numbers.
 * Checks whether entered numbers are as per prerequisite or not & returns the 
 * flag.
 ******************************************************************************
 */

/******************************************************************************/
int ValidateParam(char *str_ptr1, char * str_ptr2){
/******************************************************************************/

    /* size declared as limit for integer range    *
     * num takes the starting number from str_ptr1 *
     * limit takes the count from str_ptr2         *
     */
    int num, limit, size;
    size = pow(2, sizeof(int) * 8 - 1) - 1;    // maximum range of int

    if ( sscanf(str_ptr1, "%i", &num) && sscanf(str_ptr2, "%i", &limit) ){
        
        if ( -size < num && limit < size ){
            if ( 0 < limit && limit < size ){
                if ( ( num + limit * 2 ) < num ){
                    strcpy(msg, "Given range is too wide\n");
                    return 0;
                }
                else{
                    return 1;
                }
            }
            else{
                strcpy(msg, "Given count exceeds limit\n");
                return 0;
            }
        }
        else{
            strcpy(msg, "Given number exceeds limit\n");
            return 0;
        }
    }
    else{
        strcpy(msg, "\nPlease give numbers\n");
        return 0;
    }
}

/******************************************************************************
 * Function: FindEven
 * input: strPtr1, strPtr2
 * strPtr1 refers to the number from which count should begin.
 * strPtr2 refers to the count number
 * If the number is validate prints the n-consecutive even numbers.
 ******************************************************************************
 */

/******************************************************************************/
void FindEven(char *str_ptr1, char * str_ptr2){
/******************************************************************************/    
    int i, num, limit;

    if ( sscanf(str_ptr1, "%i", &num) && sscanf(str_ptr2, "%i", &limit) ){
        printf("Numbers successfully scanned\n");
    }
    else
        printf("Numbers couldn't be scanned\n");

    printf("%d even number(s) after number %d are:", limit, num);
        
    if (num % 2 == 0)
        num += 2;
    else
        num++;
        
    for (i = 0; i < limit; i++){
        printf("\n%d", num);
        num += 2;
    }
    printf("\n");
}

/******************************************************************************/
/**                                                                          **/
/**                                 EOF                                      **/
/**                                                                          **/
/******************************************************************************/


