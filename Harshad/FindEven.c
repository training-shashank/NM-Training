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
#include <time.h>
/******************************************************************************/

#define MAX_SIZE 100
#define ERROR 1
#define LOG 2
#define DEBUG 3

int line_no = 0;
char *err_msg = NULL;

/************************* Function Declarations ******************************/
int FileCheck(FILE *);
char *TrimWhiteSpace(char *);
void FindEven(char *, char *);
int ValidateParam(char *, char *);
void UpdateLog(int, char *);
void FreeMemory(char *, char *, char *);
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

    err_msg = (char *)malloc(MAX_SIZE);
    
    if ( err_msg == NULL ){
        printf("Memory to message isn't allocated\n");
        exit(0);
    }
    
    strcpy(err_msg, "Default message\n");

	printf("\nThis program is to print n-consecutive even numbers,"
                            " given the certain number\n");

    if (argc == 2){

        // if the argument is to print help for the program
        
        if (strcmp(argv[1], "--help") == 0){

            file_ptr = fopen("../text-files/FINDEVEN_README.txt", "r"); //read from file
       
            if( !FileCheck(file_ptr) ){
                UpdateLog(DEBUG, "Reading help from file");
                while ((ch = fgetc(file_ptr)) != EOF){
                    printf("%c", ch);
                }
            UpdateLog(LOG, "Read help from file");
            }
            else{
                printf("%s\n", err_msg);
                UpdateLog(ERROR, err_msg);
            }
            fclose(file_ptr);
            exit(0);
        }
        else{
            printf("Please provide valid option\n");
            UpdateLog(ERROR, "Valid option not provided");
            exit(0);
        }
    }

    else if ( argc == 3 ){

        // if input is passed through file which is a command line argument

        if ( strcmp(argv[1], "-f") == 0 ){

            printf("\nEntered file name: %s\n", argv[2]);
            file_ptr = fopen(argv[2], "r");
            
            if ( !FileCheck(file_ptr) ){
                printf("Taking input from file\n");
                   
                /* buff is to store the line read from file.
                 * line points to the trimmed string read from file.
                 * name stores the name of the student.
                 * s_marks stores the marks in string.
                 */

                char *buff, *line, *name, *s_nos;
                int marks;
                int count = 0;
                size_t len = 0;     // to store the line size read from file

                buff = (char *) malloc(MAX_SIZE);
                name = (char *) malloc(MAX_SIZE);
                
                printf("Reading input from file\n");
                UpdateLog(DEBUG, "Reading input from file");

                while ( getline(&buff, &len, file_ptr) != -1) {

                    UpdateLog(DEBUG, "Trimming white spaces from file line");
                    
                    line = TrimWhiteSpace(buff);
                    printf("Line read from file: %s\n", line);
            
                    // Checking whether record consists of number or not
                    if ( (s_nos = strsep(&line, " ")) != NULL )
                        strcpy(str_ptr1, s_nos);
                    else{
                        UpdateLog(ERROR, "Record is invalid");
                        strcpy(err_msg, "Record is invalid");
                        printf("%s\n", err_msg);
                        FreeMemory(str_ptr1, str_ptr2, err_msg);
                        exit(0);
                    }
                    if ( (s_nos = strsep(&line, "\n")) != NULL )
                        strcpy(str_ptr2, s_nos);
                    else{
                        UpdateLog(ERROR, "Record is invalid");
                        strcpy(err_msg, "Record is invalid");
                        printf("%s\n", err_msg);
                        FreeMemory(str_ptr1, str_ptr2, err_msg);
                        exit(0);
                    }
                       
                    UpdateLog(DEBUG, "Validating Parameters");
                                                
                    if ( ValidateParam(str_ptr1, str_ptr2) ){
                        UpdateLog(DEBUG, "Finding even numbers");
                        FindEven(str_ptr1, str_ptr2);
                    }
                    else{
                        printf("%s\n", err_msg);
                        UpdateLog(ERROR, err_msg);
                        FreeMemory(str_ptr1, str_ptr2, err_msg);
                        exit(0);
                    }
                }
                fclose(file_ptr);
                FreeMemory(str_ptr1, str_ptr2, err_msg);
                return 1;
            }
            else{
                printf("\n%s\n", err_msg);
                UpdateLog(ERROR, err_msg);
                FreeMemory(str_ptr1, str_ptr2, err_msg);
                exit(0);
            }
        }
        // numbers are passed as command line argument
        else{
            UpdateLog(DEBUG, "Scanning input from command line arguments");
            strcpy(str_ptr1, argv[1]);
            strcpy(str_ptr2, argv[2]);
        }
    }

    // numbers have to be read from standard input
    else if(argc == 1){
                
        UpdateLog(DEBUG, "Scanning input from standard input");
        printf("\nPlease enter the number you want to start from:\n");
        scanf("%s", str_ptr1);
    
        printf("\nPlease enter how many numbers you want to see:\n");
        scanf("%s", str_ptr2);
    }

    else{
        printf("Please enter valid arguments");
        UpdateLog(ERROR, "Valid arguments not provided");
        FreeMemory(str_ptr1, str_ptr2, err_msg);
        exit(0);
    }
    
   
    UpdateLog(DEBUG, "Validating arguments");
    if ( ValidateParam(str_ptr1, str_ptr2) ){
        UpdateLog(DEBUG, "Finding even numbers");
        FindEven(str_ptr1, str_ptr2);
    }
    else{
        printf("%s\n", err_msg);
        UpdateLog(ERROR, err_msg);
    }
    FreeMemory(str_ptr1, str_ptr2, err_msg);
  
}

/*****************************************************************************/
/**                             LOCAL FUNCTIONS                             **/
/**                                                                         **/
/*****************************************************************************/

/*******************************************************************************
 * Function: FileCheck()
 * Working: This function checks whether mentioned file exists or not & if
 * exists whether it's empty or not.
 * Input: function takes as input file pointer & returns the result whether file
 * can be used or not.
 * Return value: 1 or 0.
 ******************************************************************************/

/******************************************************************************/
int FileCheck(FILE *file_ptr){
/******************************************************************************/

    if ( file_ptr == NULL){
        strcpy(err_msg, "File doesn't exists");
        return 1;
    }
    else{    
        fseek(file_ptr, 0, SEEK_END);

        int f_size = ftell(file_ptr);

        /* print error message */
        if ( f_size == 0){
            strcpy(err_msg, "File is empty");
            return 1;
        }
        else{
            fseek(file_ptr, 0, SEEK_SET);
            return 0;
        }
    }   
}

/*******************************************************************************
 * Function: TrimWhiteSpace(char *)
 * Working: This function takes as input a string & trim the leading & trailing
 * white spaces (i.e. tabs & spaces).
 * Return value: string with leading & trailing white spaces removed.
 ******************************************************************************/

/******************************************************************************/
char* TrimWhiteSpace(char *str){
/******************************************************************************/
    char *end;

    // Trim leading space
    while(isspace(*str)) str++;

    if(*str == 0)  // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace(*end)) end--;

    // Write new null terminator
    *(end+1) = '\0';
    return str;
}

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
                    strcpy(err_msg, "Given range is too wide\n");
                    return 0;
                }
                else{
                    return 1;
                }
            }
            else{
                strcpy(err_msg, "Given count exceeds limit\n");
                return 0;
            }
        }
        else{
            strcpy(err_msg, "Given number exceeds limit\n");
            return 0;
        }
    }
    else{
        strcpy(err_msg, "Please give input as integer numbers");
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

/*******************************************************************************
 * Function: UpdateLog()
 * Working: Updates the log file.
 * Input: Type of log, message
 ******************************************************************************/
 
/******************************************************************************/
void UpdateLog(int log_type, char *msg){
/******************************************************************************/

    line_no++;      // incrementing record number 
    FILE *log;
    // buff is temporary buffer to store date
    char buff[20], chr, n_string[3];        
    int f_size ;

    log = fopen("FIND_EVEN_LOG.txt", "a+");


    if ( !fseek(log, 0, SEEK_END) ){
        f_size = ftell(log);

        if ( f_size == 0){
            fputs("\tId\t|\tTimestamp\t\t|\tType\t|\tMessage\n", log);
            fputs("-------------------------------------------------------"
                    "---------------------------------------------\n", log);
        }

        fseek(log, 0, SEEK_SET);
        chr = fgetc(log);
            
        if ( log != NULL ){
            if ( line_no == 1 )
                fputs("========================================================"
                       "==============================================\n", log);
            time_t now = time(NULL);
	    
            strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
    	    snprintf(n_string, 12, "%d", line_no);
            fputs("\t", log);
            fputs(n_string, log);
            fputs("\t|", log);
            fputs("\t", log);
            fputs(buff, log);
        	fputs("\t|", log);
	        
            switch(log_type){
                case 1:
                    fputs("\t", log);
    	            fputs("ERROR", log);
            		break;

                case 2:
                    fputs("\t", log);
                    fputs("LOG", log);
                    break;
                case 3:
                    fputs("\t", log);
                    fputs("DEBUG", log);
                    break;
            }
        
            fputs("\t|", log);
            fputs("\t", log);
            fputs(msg, log);
            fputs("\n", log);
            fputs("-------------------------------------------------------"
                "-------------------------------------------\n", log);
	    
            strcpy(err_msg, "Log updated");
	    }
    	else{
	    	strcpy(err_msg, "Log file not found");
	    }
        fclose(log);
    }
}

/*******************************************************************************
 * Function: FreeMemory()
 * Working: Frees allocated memory to parameters.
 * Input: two numbers & one error message
 ******************************************************************************/

/******************************************************************************/
void FreeMemory(char *str1, char *str2, char *msg){
/******************************************************************************/
    UpdateLog(LOG, "Freeing memory");
    free(str1);
    free(str2);
    free(msg);
}

/******************************************************************************/
/**                                                                          **/
/**                                 EOF                                      **/
/**                                                                          **/
/******************************************************************************/
