/*------------------------------------------------------------------------------
 * File: SortMarks.c
 * Author: Harshd
 * Date: 02-Jul-2015
 *
 * COPYRIGHT: (C) 2015 - All rights reserved - Network Marvels (I) Pvt. Ltd.,
 * Thane (India)
 *-----------------------------------------------------------------------------
 * Description: Program to find top-n scorers in the class.
 * The program reads input from the file, where input is stored in the form of
 * (stud_name marks) & prints top-n scorers.
 * Program also has an option to show the help to the user by taking command
 * line argument '--help'.
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

/******************************** Header files ********************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
/******************************************************************************/

#define MAX_SIZE 100

/******************************************************************************/
/**                                                                          **/
/**                      TYPEDEFS AND STRUCTURES                             **/
/**                                                                          **/
/******************************************************************************/

struct StudListType{
    int marks;
    char *name;
    struct StudListType *nxtStudPtr;
} *head = NULL, *prev_node;

typedef struct StudListType StudListType;

/**************************** Global Declarations *****************************/
char *err_msg;
/******************************************************************************/

/**************************** Function Declarations ***************************/
int FileCheck(FILE *);
int ValidateParam(char *,char *);
int CreateList(char *, int, StudListType *);
void SortList(int);
void PrintList(StudListType *);
int UpdateLog(FILE *, char *, char *);
/******************************************************************************/

int main(int argc, char* argv[]){

    FILE *file_ptr, *log_ptr;   // pointers to file & log respectively.
    char ch;                    // character to be read from file.
    int i;

    err_msg = (char *) malloc(MAX_SIZE);
    log_ptr = fopen("SORT_MARKS_LOG.txt", "a");

    if (argc == 2){
        // if the argument is to print help for the program
        if (strcmp(argv[1], "--help") == 0){
            file_ptr = fopen("SORTMARKS_README.txt", "r"); //read from file
         
            /* Check whether file is empty or not */
            if ( !FileCheck(file_ptr) ){
                fseek(file_ptr, 0, SEEK_SET);
                while ((ch = fgetc(file_ptr)) != EOF){
                    printf("%c", ch);
                }
            }
            else{
                /* Putting in the log */
                if ( UpdateLog(log_ptr, "Error", err_msg) ){
                	printf("%s", err_msg);
                	exit(0);
                }
                else{
                	printf("%s", err_msg);
                	exit(0);
                }
            }
            fclose(file_ptr);
        }
        return 1;
    }

    if (argc == 3){

        /* Read input from file */
        if ( strcmp(argv[1], "-f") == 0){
            file_ptr = fopen(argv[2], "r");
            
            /*Start reading from file */
            if ( !FileCheck(file_ptr) ){
                    
                fseek(file_ptr, 0, SEEK_SET);
                printf("Taking input from file\n");
                    
                char *name, *marks;
                int count = 0;
                    
                printf("Reading input from file\n");
                name = (char *) malloc(MAX_SIZE);

                /* Create linked list */
                while( fscanf(file_ptr, "%s %s", name, marks) != EOF){
                    printf("Variables read: %s %s\n", name, marks);
                        
                    if ( ValidateParam(name, marks) ){
                        if ( CreateList(name, atoi(marks), head) )
                            count++;        // node inserted successfully
                    }
                    else{
                        /* Putting in the log */
                		if ( UpdateLog(log_ptr, "Error", err_msg) ){
		                	printf("%s", err_msg);
		                	exit(0);
		                }
		                else{
		                	printf("%s", err_msg);
		                	exit(0);
		                }
                    }
                }
                free(name);
                    
                printf("Count: %d\n", count);

                /* Sorting linked list */
                //SortList(count);

            }// end of if
            else{
                /* Putting in the log */
                if ( UpdateLog(log_ptr, "Error", err_msg) ){
                	printf("%s", err_msg);
                	exit(0);
                }
                else{
                	printf("%s", err_msg);
                	exit(0);
                }
            }
        }// end of else
    }// end of if
    
    PrintList(head);    
    free(err_msg);
    fclose(log_ptr);
    return 0;
}
/*
/******************************************************************************/
/**                                                                          **/
/**                              LOCAL FUNCTIONS                             **/
/**                                                                          **/
/******************************************************************************/

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
        strcpy(err_msg, "\nFile doesn't exists\n");
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
        else
            return 0;
    }   
}
/*******************************************************************************
 * Function: ValidateParam()
 * Working: Validates for the parameter read from the file. If parameters are
 * valid returns 1 else 0;
 * Input: name & marks read from file.
 * Return value: 1 or 0.
 ******************************************************************************/

/******************************************************************************/
int ValidateParam(char *name, char *marks){
/******************************************************************************/

    int name_len, i_marks, i = 0;
    
    name_len = strlen(name);

    /* checking whether name consists of only alphabets */
    while ( i < name_len ){
        if ( isalpha(name[i++]) )
            continue;
        else{
            strcpy(err_msg, "Name is not in right format");
            return 0;
        }
    }

    /* checking whether marks are only numbers */
    if ( sscanf(marks, "%i", &i_marks) )
        return 1;
    else{
        strcpy(err_msg, "Marks should be in number format");
        return 0;
    }
}

/*******************************************************************************
 * Function: CreateList()
 * Working: Creates the node of type StudListType & adds it to the list
 * Input: name & marks read from file.
 ******************************************************************************/

/******************************************************************************/
int CreateList(char *name, int marks, StudListType *f_head){
/******************************************************************************/

    StudListType *node, *prev, *current;
                    
    node = (StudListType *) malloc(sizeof (StudListType));
    node->name = (char *) malloc(strlen(name));
    
    strcpy(node->name, name);
    node->marks = marks;
    node->nxtStudPtr = NULL;

    if ( f_head != NULL ){
        prev = f_head;
        current = prev;
        while ( current != NULL ){

            if ( current->marks < node->marks ){
                
                node->nxtStudPtr = current;
                
                if ( current == f_head ){
                    head = node;
                    return 1;
                }
                else{
                    prev->nxtStudPtr = node;
                    return 1;
                }
            }
            else{
                prev = current;
                current = current->nxtStudPtr;
            }
        }
        if ( current == NULL ){
            prev->nxtStudPtr = node;
            return 1;
        }
    }
    else{
        head = node;
        return 1;
    }
    return 0;
}

/*******************************************************************************
 * Function: PrintList()
 * Working: Prints the sorted linked list.
 ******************************************************************************/
 
/******************************************************************************/
void PrintList(StudListType *f_head){
/******************************************************************************/

    int limit, i = 1;
    StudListType *prev, *temp;
    
    /* printing sorted linked list */
    printf("Printing linked list\n");
    
    printf("\nHow many toppers you want to see:\n");
    scanf("%d", &limit);

    prev = f_head;

    printf("Name\t\tMarks\n");
    printf("----\t\t-----\n");
    
    while ( prev != NULL && i <=limit){

        printf("%s\t\t%d", prev->name, prev->marks);
        printf("\n");
        temp = prev;
        prev = prev->nxtStudPtr;
        i++;
    }
}

/*******************************************************************************
 * Function: UpdateLog()
 * Working: Updates the log file.
 * Input: File pointer, type of log, message
 ******************************************************************************/
 
/******************************************************************************/
int UpdateLog(FILE *log, char *log_type, char *msg){
/******************************************************************************/

    char buff[20];              // temporary buffer to store date
	if(log != NULL){
	    //printf("Entering into log\n");
	    time_t now = time(NULL);
	    
	    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
	    
	    fputs(buff, log);
	    fputs("\t", log);
	    fputs(log_type, log);
	    fputs("\t", log);
	    fputs(msg, log);
	    
		strcpy(err_msg, "Log updated\n");
		return 1;
	}
	else{
		strcpy(err_msg, "\nLog file not found\n");
		return 0;
	}
}

/******************************************************************************/
/**                                                                          **/
/**                                 EOF                                      **/
/**                                                                          **/
/******************************************************************************/
