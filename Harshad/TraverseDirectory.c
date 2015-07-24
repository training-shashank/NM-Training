/*------------------------------------------------------------------------------
 * File: TraverseDirectory.c
 * Author: Harshd
 * Date: 02-Jul-2015
 *
 * COPYRIGHT: (C) 2015 - All rights reserved - Network Marvels (I) Pvt. Ltd.,
 * Thane (India)
 *-----------------------------------------------------------------------------
 * Description: Program to traverse through directories & list all the files
 * The program takes as input the file path either from command line or from 
 * standard input or reads from the file & traverses through directory & 
 * sub-directories in it & list all the files.
 * Program also has an option to show the help to the user by taking command
 * line argument of --help.
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

/****************************** HEADER FILES **********************************/
#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
/******************************************************************************/

/******************************** MACROS **************************************/
#define SUCCESS 0
#define FAILURE 1
#define HELP_FILE "/home/harshad/dump/text-files/TRAVERSE_READEME.txt"
#define LOG_FILE "/home/harshad/dump/text-files/traverse_log.txt"
/******************************************************************************/

/************************** FUNCTION DECLARATIONS *****************************/
void traverseDirectory(char *);
/******************************************************************************/

int main(int argc, char* argv[]){
	char *path,*file;
    DIR* dir;
    struct dirent *ent;
    struct stat states;
    FILE* fp;
    char ch;
    size_t len = 0;
    char *temp;

    path = (char *)malloc(sizeof(char)*100);
    
    //Checking whether command line argument is passed
    if(argc == 2){
        
        //if the argument is to print help for the program
        if(strcmp(argv[1], "--help") == 0){

                fp = fopen(HELP_FILE,"r");
                while((ch = fgetc(fp)) != EOF){
                    printf("%c", ch);
                }
        }
         // Pass the directory argument to traverse
         else{
             strcpy(path, argv[1]);
         }
    }
        
    // if the path is to be read from another file
    else if(argc == 3){

        if(strcmp(argv[1],"-f") == 0){
        
            fp = fopen(argv[2],"r");
        
            if(fp != NULL){
        
                printf("\nFile opened\n");
                getline(&path, &len, fp);
                //strcat(strcat("\"",path),"\"");
                printf("\nRetrieved path from file is %s\n", strcat(path,"\0"));
                
            }
            else{
                printf("\nFile couldn't be opened\n");
                exit(EXIT_FAILURE);
            }
        }
        else{
            // print invalid option & update error log
            exit(EXIT_FAILURE);
    }
    
    else if ( argc == 1 ){
        printf("\nEnter the directory path to be traversed:\n");
        scanf("%s",path);
        printf("\nPath Entered:\n%s",path);
                    
    }
    traverseDirectory(path);
    free(path);
}

/*******************************************************************************
 **                                                                           **
 **                             LOCAL FUNCTIONS                               **
 **                                                                           **
*******************************************************************************/

/*******************************************************************************
 * Function: traverseDirectory()
 * Working: Lists the content (files & sub-directories of directory specified.
 * Input: Path to traverse
 * Output: All the sub-directories & files in given path.
 ******************************************************************************/
void traverseDirectory(char *name){
	DIR* dir;
	struct dirent *ent;
	struct stat states;
	
	printf("\nIn traverse function\n%s",name);
    // check whether directory passed can be opened or not
    if((dir = opendir(name)) != NULL){

        // get the status of the directory
		stat(name,&states);
		
        while((ent=readdir(dir)) != NULL){
		
            // if the directory received is current or parrent directory
            // then ignore it
            if(!strcmp(ent->d_name,".") || !strcmp(ent->d_name,"..")){
        	                continue;
                	}
		
            // check whether the type of path is directory of file
            // if it's directory then follow through newly found directory
            else if(S_ISDIR(ent->d_type & DT_DIR)){
        	    printf("\nDirectory found.");
				traverseDirectory(ent->d_name);
                	}
		
            // if the path is of file print it
            else{
				printf("%s",name);
	            printf("/%s \n",ent->d_name);
			}
		}
		closedir(dir);
	}
    else{
        printf("\nfile couldn't be opened\n");
    }
}

/*******************************************************************************
 **                                                                           **
 **                                 EOF                                       **
 **                                                                           **
*******************************************************************************/

