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

char *err_msg;

int main(int argc, char* argv[]){

    FILE *file_ptr;
    char ch;
    int i, f_size;

    err_msg = (char *) malloc(MAX_SIZE);

    if (argc == 2){
        // if the argument is to print help for the program
        if (strcmp(argv[1], "--help") == 0){
            file_ptr = fopen("SORTMARKS_README.txt", "r"); //read from file
            
            fseek(file_ptr, 0, SEEK_END);

            f_size = ftell(file_ptr);
            
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

    if (argc == 3){
        if ( strcmp(argv[1], "-f") == 0){
            file_ptr = fopen(argv[2], "r");
            
            if ( file_ptr == NULL ){
                strcpy(err_msg, "\nFile couldn't be opened\n");
                printf("%s", err_msg);
                exit(0);
            }
            else{

                fseek(file_ptr, 0, SEEK_END);
                f_size = ftell(file_ptr);
                if ( f_size == 0){
                    printf("File is empty.\n");
                    exit(0);
                }
                else{
                    fseek(file_ptr, 0, SEEK_SET);
                    printf("Taking input from file\n");
                    char *name;
                    int marks, count = 0;
                    name = (char *) malloc(MAX_SIZE);
                    printf("Reading input from file\n");
                    while( fscanf(file_ptr, "%s %d", name, &marks) != EOF){
                        printf("Variables read: %s %d\n", name, marks);
                        StudListType *node;
                    
                        node = (StudListType *) malloc(sizeof (StudListType));
                        node->name = (char *) malloc(strlen(name));
                    
                        strcpy(node->name, name);
                        node->marks = marks;
                    
                        if ( head == NULL ){
                            head = node;
                            prev_node = head;
                        }
                        else{
                            prev_node->nxtStudPtr = node;
                        }
                        node->nxtStudPtr = NULL;
                        prev_node = node;
                        count++;
                    }
                    printf("Count: %d\n", count);
                    /* Sorting linked list */
                    if ( head != NULL){
                        printf("Sorting linked list\n");
                        StudListType *node, *temp;
   
                        for( i = 0; i < count; i++){
    
                            prev_node = head;
                            node = prev_node;
                            temp = node->nxtStudPtr;

                            printf("Prev node: %s %d %p\n",prev_node->name, 
                                prev_node->marks, (void *) node->nxtStudPtr);
                            printf("node: %s %d %s %p\n",node->name,
                                node->marks, (void *) node->nxtStudPtr);

                            while(temp != NULL){
                                if ( node->marks < temp->marks ){
                                    //printf("Swapping\n");
                                    if ( node == head ){
                                        printf("Swapping start\n");
                                        node->nxtStudPtr = temp->nxtStudPtr;
                                        temp->nxtStudPtr = node;
                                        prev_node = temp;
                                        temp = node->nxtStudPtr;
                                        head = prev_node;
                                    }
                                    else{
                                        printf("Swapping inbetween\n");
                                        prev_node->nxtStudPtr = temp;
                                        node->nxtStudPtr = temp->nxtStudPtr;
                                        temp->nxtStudPtr = node;
                                        prev_node = temp;
                                        temp = node->nxtStudPtr;
                                    }
                                }
                                else{
                                    prev_node = node;
                                    node = temp;
                                    temp = temp->nxtStudPtr;
                                }   
                            }// end of while
                        }// end of for
    
                        /* printing sorted linked list */
                        printf("Printing linked list\n");
                        prev_node = head;
                        while ( prev_node != NULL ){
                            printf("%s %d",prev_node->name, prev_node->marks);
                            printf("\n");
                            prev_node = prev_node->nxtStudPtr;
                        }

                    }// end of if
                }// end of else
            }// end of else
        }// end of if
    }// end of if
                    
    free(err_msg);
    //TakeInput();
    //sortMarks();
    return 0;
}
/*
/******************************************************************************/
/**                                                                          **/
/**                              LOCAL FUNCTIONS                             **/
/**                                                                          **/
/******************************************************************************/

/*******************************************************************************
 * Function: TakeInput()
 * working: dynamically allocates the memory according to the number of students
 * to the pointer of structure StudListType & stores their information.
 * size is the number of students in the class.
 *******************************************************************************
 

/******************************************************************************
void TakeInput(){
/******************************************************************************

    printf("How many students:\n");
	scanf("%d",&size);
   
	printf("Enter the student's information:\n");
   
    StudListType *head; 
    StudListType *stud = (StudListType *)malloc(sizeof(StudListType));
    head = stud;

    for(i=0;i<size;i++){
        if (i>0){
            StudListType *ptr = (StudListType *)malloc(sizeof(StudListType));
            printf("\nStudent %d name: ", i+1);
    		scanf("%s", ptr->studName);
            printf("\nStudent %d marks: ", i+1);
            scanf("%d", ptr->marks);
            stud->nxtStudPtr = ptr;
            ptr->nxtStudPtr = NULL;
            stud = ptr;
        }
        else{
             printf("\nStudent %d name: ", i+1);
             scanf("%s", stud->studName);
             printf("\nStudent %d marks: ", i+1);
             scanf("%d", stud->marks);
             stud->nxtStudPtr = NULL;
	    }
    }
    StudListType *ptr = (StudListType *)malloc(sizeof(StudListType));
    ptr = head;
    while(ptr != NULL){
        printf("\nStudent's name: %s", ptr->studName);
        ptr = ptr->nxtStudPtr;
    }
}
/*
/******************************************************************************
 * Function: SortMarks()
 * working: Sorts the linked list studList structure according to the marks of
 * students.
 ******************************************************************************
 

/******************************************************************************
void SortMarks(){
/******************************************************************************

	printf("\nHow many toppers you want:\n");
    scanf("%d",&limit);
    printf("Toppers are:\n\n");

    StudListType *head = studList;
    StudListType *temp = head;
	//Sorting marks descendingly
	
	for(i = 0; i < size; i++){
		for(j = i+1; j < size; j++){
			if(studList[i].marks<studList[j].marks){
				marks[i] = marks[i] + marks[j];
				marks[j] = marks[i] - marks[j];
				marks[i] = marks[i] - marks[j];
			}
		}
		if(i == limit)
			break;
		else
			printf("%d\n",marks[i]);                                //Printing top-n marks
	}
	/*
	printf("\nSorted marks:\n");
	for(i=0;i<size;i++)
	printf("%d\n",marks[i]);
	//marks = temp;*
}

/******************************************************************************
void printToppers(){
/******************************************************************************

	sortMarks();
	printf("\nHow many toppers you want:\n");
	scanf("%d",&k);
	printf("Toppers are:\n\n");
	for(i=0;i<k;i++){
		printf("%d\n",marks[i]);
	}
}
*/
