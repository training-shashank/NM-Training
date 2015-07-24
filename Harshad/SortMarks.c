/*------------------------------------------------------------------------------
 * File: SortMarks.c
 * Author: Harshad
 * Date: 02-Jul-2015
 *
 * COPYRIGHT: (C) 2015 - All rights reserved - Network Marvels (I) Pvt. Ltd.,
 * Thane (India)
 *-----------------------------------------------------------------------------
 * Description: Program to find top-n scorers in the class.
 * The program reads input only from the file, where input is stored in the
 * & prints top-n scorers.
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

/******************************** MACROS **************************************/
#define MAX_SIZE 100
#define ERROR 1
#define LOG 2
#define DEBUG 3
#define SUCCESS 1
#define FAILURE 0
#define HELP_FILE "../text-files/SORTMARKS_README.txt"
#define LOG_FILE "SORT_MARKS_LOG.txt"
/******************************************************************************/

/************************ TYPEDEFS AND STRUCTURES *****************************/
struct StudListType{
    int marks;
    char *name;
    struct StudListType *nxtStudPtr;
} *head = NULL, *prev_node;

typedef struct StudListType StudListType;
/******************************************************************************/

/**************************** GLOBAL DECLARATIONS *****************************/
char *err_msg, *no = NULL;
char const DELIM[2] = " ";
int list_count = 0, line_no = 0;
/******************************************************************************/

/**************************** FUNCTION DECLARATIONS ***************************/
int FileCheck(FILE *);
char* TrimWhiteSpace(char *);
int ValidateParam(char *,int);
int CreateList(char *, int, StudListType *);
int PrintList(StudListType *);
void UpdateLog(int, char *);
/******************************************************************************/

int main(int argc, char* argv[]){

    FILE *file_ptr;   // pointers to file & log respectively.
    char ch;                    // character to be read from file.
    int i;
    StudListType *current, *temp;

    err_msg = (char *) malloc(MAX_SIZE);
    strcpy(err_msg, "NO ERROR");

    if (argc == 2){
        // if the argument is to print help for the program
        if (strcmp(argv[1], "--help") == 0){
            file_ptr = fopen(HELP_FILE, "r"); //read from file
         
            /* Check whether file is empty or not */
            if ( FileCheck(file_ptr) ){
                UpdateLog(DEBUG, "Reading help from file") ;
                fseek(file_ptr, 0, SEEK_SET);
                while ((ch = fgetc(file_ptr)) != EOF){
                    printf("%c", ch);
                }
            }
            else{
                /* Putting in the log */
                printf("\n%s\n", err_msg);
                UpdateLog(ERROR, strcat(err_msg, "Exiting program"));
                exit(-1);
            }
            UpdateLog(LOG, "Read help from file complete."); 
            fclose(file_ptr);
            exit(-1);
        }
        else{
            printf("Please provide valid options\n");
            UpdateLog(ERROR, "Valid options not provided. Exiting program."); 
            exit(-1);
        }
    }

    if (argc >= 3){

        /* Read input from file */
        if ( strcmp(argv[1], "-f") == 0){
            file_ptr = fopen(argv[2], "r+");
            
            /*Start reading from file */
            if ( FileCheck(file_ptr) ){
                    
                printf("Taking input from file\n");
                   
                /* buff is to store the line read from file.
                 * line points to the trimmed string read from file.
                 * name stores the name of the student.
                 * s_marks stores the marks in string.
                 */

                char *temp, *buff, *line, *name, *s_marks;
                int marks;
                size_t len = 0;     // to store the line size read from file

                buff = (char *) malloc(MAX_SIZE);
                name = (char *) malloc(MAX_SIZE);
                temp = (char *) malloc(MAX_SIZE);
                
                printf("Reading input from file\n");

                /* Create linked list */
                UpdateLog(LOG, "Creating linked list");
                while ( getline(&buff, &len, file_ptr) != -1) {

                    strcpy(name, "");
                    marks = -1;
                  //  strcpy(temp, "");
                    UpdateLog(DEBUG, "Trimming white spaces from file line");
                    
                    line = TrimWhiteSpace(buff);
                    printf("Line read from file: %s\n", line);
            
                    // strcpy(name, strsep(&line, " "));
                    
                    temp = strtok(line, DELIM);
                   // printf("temp: %s\n", temp);

                    while ( temp != NULL ){
                        strcat(name, temp);
                        strcat(name, " ");
                       // printf("name: %s\n",name);
                        temp = strtok(NULL, DELIM);
                        if (temp == NULL )
                            break;
                       // printf("temp in while: %s\n", temp);
                        if ( sscanf(temp, "%i", &marks) )
                            break;
                    }
                    
                    strcpy(name, TrimWhiteSpace(name));
                    
                   // printf("Marks: %d\n",marks);
                        
                    UpdateLog(DEBUG, "Validating Parameters");
                        
                    if ( ValidateParam(name, marks) ){
                        UpdateLog(DEBUG, "Adding node to the list");
                        
                        if ( CreateList(name, marks, head) )
                            list_count++;        // node inserted successfully
                    }
                    else{
                         /* Putting in the log */
                        printf("\n%s\n", err_msg);
                        UpdateLog(ERROR, strcat(err_msg, ". Ignoring record."));
                    }
                }


                free(name);
                free(buff);

                printf("Count: %d\n", list_count);
            }// end of if
            else{
                /* Putting in the log */
                printf("\n%s\n", err_msg);
                UpdateLog(ERROR, err_msg);
            }
        }// end of if
        else{
        	printf("\n%s not a valid option\n", argv[1]);
        	strcpy(argv[1], " not a valid option");
        	UpdateLog(DEBUG,  argv[1]);
        }
    }// end of if
	else{
		printf("Valid arguments not provided. Type '--help' option to see help\n");
		exit(-1);
	}
    
    if ( argc == 4 )
        no = argv[3];

    if ( !PrintList(head) ){
    	printf("\n%s\n", err_msg);
        UpdateLog(ERROR, err_msg);
    }
    else
       UpdateLog(LOG, "Printed sorted linked list");
    
    UpdateLog(LOG, "Freeing the linked list memory");

    if( head != NULL){
    	current = head;
    	while( current != NULL){
    		temp = current;
    		current = current->nxtStudPtr;
    		free(temp->name);
    		free(temp);
    	}
    }		    	
    free(err_msg);
    
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
        strcpy(err_msg, "File doesn't exists");
        return FAILURE;
    }
    else{    
        fseek(file_ptr, 0, SEEK_END);

        int f_size = ftell(file_ptr);

        /* print error message */
        if ( f_size == 0){
            strcpy(err_msg, "File is empty");
            return FAILURE;
        }
        else{
            fseek(file_ptr, 0, SEEK_SET);
            return SUCCESS;
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

/*******************************************************************************
 * Function: ValidateParam()
 * Working: Validates for the parameter read from the file. If parameters are
 * valid returns 1 else 0;
 * Input: name & marks read from file.
 * Return value: 1 or 0.
 ******************************************************************************/

/******************************************************************************/
int ValidateParam(char *name, int marks){
/******************************************************************************/

    int name_len, i = 0;
    
    name_len = strlen(name);

    /* checking whether name consists of only alphabets */
    while ( i < name_len){
        if ( isalpha(name[i]) || isspace(name[i]) || name[i] == '.'){
            i++;
            continue;
        }
        else{
            strcpy(err_msg, "Name is not in right format");
            return FAILURE;
        }
    }

    /* checking whether marks are within range */
    if ( 0 <= marks && marks <= 100 ){
        printf("checking marks\n");
        return SUCCESS;
    }
    else{
        strcpy(err_msg, "Marks should be between 0 to 100");
        return FAILURE;
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
    node->name = (char *) malloc(strlen(name) + 1);
    
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
                    return SUCCESS;
                }
                else{
                    prev->nxtStudPtr = node;
                    return SUCCESS;
                }
            }
            else{
                prev = current;
                current = current->nxtStudPtr;
            }
        }
        if ( current == NULL ){
            prev->nxtStudPtr = node;
            return SUCCESS;
        }
    }
    else{
        head = node;
        return SUCCESS;
    }
    return FAILURE;
}

/*******************************************************************************
 * Function: PrintList()
 * Working: Prints the sorted linked list.
 ******************************************************************************/
 
/******************************************************************************/
int PrintList(StudListType *f_head){
/******************************************************************************/

    int i = 1, limit;
    StudListType *prev, *temp;
    char *no_tmp = NULL;
    
    /* printing sorted linked list */
    if ( f_head != NULL ){
    
	    printf("Printing linked list\n");
	    
	    if ( no == NULL ){
            if ( (no = (char *) malloc(MAX_SIZE)) == NULL ){
                strcpy(err_msg, "Memory couldn't be allocated to "
                        "number of toppers variable");
                return FAILURE;
            }
            else{
                no_tmp = no;
            }
            printf("\nHow many toppers you want to see:\n");
    	    scanf("%s", no);
        }
        if ( !sscanf(no, "%i", &limit) ){
            strcpy(err_msg, "Count was not in number format");
            if ( no_tmp != NULL )
                free(no_tmp);
            return FAILURE;
        }
	
    if ( limit > 0 && limit <= list_count ){
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
            if ( no_tmp != NULL )
                free(no_tmp);
	        return SUCCESS;
        }
        else{
            strcpy(err_msg, "Range is out of bound.");
            return FAILURE;
        }
	}
	else{
		strcpy(err_msg, "List is empty");
		return FAILURE;
	}
}

/*******************************************************************************
 * Function: UpdateLog()
 * Working: Updates the log file.
 * Input: File pointer, type of log, message
 ******************************************************************************/
 
/******************************************************************************/
void UpdateLog(int log_type, char *msg){
/******************************************************************************/

    line_no++;      // incrementing record number 
    FILE *log;
    // buff is temporary buffer to store date
    char buff[20], chr, n_string[3];        
    int f_size ;

    log = fopen(LOG_FILE, "a+");


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
	    }
    	else{
	    	printf("Log file not found\n");
	    }
        fclose(log);
    }
}

/******************************************************************************/
/**                                                                          **/
/**                                 EOF                                      **/
/**                                                                          **/
/******************************************************************************/
