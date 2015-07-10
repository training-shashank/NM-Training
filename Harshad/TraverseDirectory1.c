/*Program to traverse through directories*/

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<error.h>

void traverseDirectory(char name[1000]){
	DIR* dir;
	struct dirent *ent;
	struct stat states;
		
	dir = opendir(name);

	/*Checking whether opened directory is null or not*/
	if(!dir){
		//perror(name);
		closedir(dir);
		return ;
	}

	/*Traversing through directory*/
	while((ent=readdir(dir)) != NULL){
		stat(ent->d_name,&states);					//Retrieving the status of given path
		
		if(!strcmp(".", ent->d_name) || !strcmp("..", ent->d_name)){	//if name is '.' or '..' then continue
			continue;
		}
		else{
			printf("\n%s/%s\n",name,ent->d_name);			//print the whole path
	
			if(S_ISDIR(states.st_mode)){				//checking whether path is directory or not
				/*temp = name;		
				strcat(temp,"/");
				strcat(temp,ent->d_name);*/
		
				traverseDirectory(ent->d_name);			//recursive call
			}
		}
	}
	
	closedir(dir);								//close the directory
}

int main(){
	char path[100];
	printf("Enter the path:\n");
	scanf("%s",&path);
	traverseDirectory(path);
}
