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

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>

void traverseDirectory(char *name){
	DIR* dir;
	struct dirent *ent;
	struct stat states;
	
	if((dir = opendir(name)) != NULL){

		stat(name,&states);
		
        while((ent=readdir(dir)) != NULL){
		
            if(!strcmp(ent->d_name,".") || !strcmp(ent->d_name,"..")){
        	                continue;
                	}
		
            else if(S_ISDIR(ent->d_type & DT_DIR)){
        	                printf("\nDirectory found.");
				//strcat(name,"/");
				//strcat(name,ent->d_name);
				traverseDirectory(ent->d_name);
                	}
		
            else{
				printf("%s",name);
	                        printf("/%s \n",ent->d_name);
			}
		}
		closedir(dir);
	}
}

int main(int argc, char* argv[]){
	char *path,*file;
    DIR* dir;
    struct dirent *ent;
    struct stat states;
    FILE* fp;
    char ch;
    size_t len;
    int option;

    //Checking whether command line argument is passed
    if(argc == 1){
        
        //if the argument is to print help for the program
        if(strcmp(argv[1], "--help")){

                fp = fopen("TRAVERSE_README.txt","r");
                while((ch = fgetc(fp)) != EOF){
                    printf("%c", ch);
                }
        }
        
        //checking whether passed argument is directory path or filename
        else{
            dir = opendir(argv[1]);
            if(dir){
                stat(argv[1], &states);
                
                ent = readdir(dir);
                
                if(ent != NULL){      

                    //checking whether argument is directory
                    if(S_ISDIR(ent->d_type & DT_DIR)){
                        traverseDirectory(argv[1]);
                    }

                    //if argument is file to be read for the directory path i/p
                    else{
                       fp = fopen(argv[1],"r");
                       getline(&path, &len, fp);
                       printf("\nRetrieved path from file is %s\n", path);
                       traverseDirectory(path);
                    }
                }

                else{
                    printf("\nCan't read from passed directory\n");
                }
            }
           
            // if the passed directory can't be opened. 
            else{
                printf("\nCan't open passed directoy\n");
            }
        }
    }

    //Take input from user
    else{
        printf("\nSelect from given options:");
        printf("\n1.Read path from file");
        printf("\n2.Manually enter the path");
        printf("\nEnter the option:\n");
        scanf("%d", &option);

        switch(option){
            case 1: printf("\nEnter the filename\n");
                    scanf("%s",file);
                    fp = fopen(file,"r");
                    getline(&path, &len, fp);
                    printf("\nRetrieved path from file is %s\n", path);
                    traverseDirectory(path);
                    break;
            case 2: printf("\nEnter the directory path to be traversed:\n");
                    scanf("%s",path);
                    traverseDirectory(path);
                    break;
            default: printf("\nPlease enter valid choice next time\n");
                     break;
        }
    }
}
