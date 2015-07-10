/*
* File:To print "n" top scorers
* Author: Aditi
* Date: 02-Jul-2015
* 
* COPYRIGHT: (C) 2015 - All rights reserved - Network Marvels (I) Pvt. Ltd.,
* Thane (India)
*-----------------------------------------------------------------------------
* Description: Program for printing the "n"top scorers in the class
* The program will accept the scores of the students in the class from the 
* file. Then user need to enter how many number of top top topers he need to 
* display.e.g.If user needs to display 3 topers then program will display 
* top three students of the class 
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
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

/*Defining a Structure*/
struct node
{
    char *name;
    int marks;
    struct node *next;
};
int main(int argc,char *argv[])
{
    int i,j,n,count=0;

    struct node *current;
    FILE *ifp;
    struct node *prev;struct node *head;struct node *temp;
    char *name;int marks;
    
    /*allocating memory to the variable name*/ 
    name=(char *)malloc(sizeof(char)*100);
    head=NULL;

    /*checking whether file name is passed or not*/ 
    if((argc==3)&&(strcmp(argv[1],"-f")==0))
    {
        ifp = fopen(argv[2],"r");/*Open the file*/
        if(ifp == NULL)
        {
            fprintf(stderr,"cant open the file");
        }
        else
        {
            /*Accept the marks and names from the file*/
            while(fscanf(ifp,"%s %d",name,&marks)!=EOF)
            {
                current =(struct node *)malloc(sizeof(struct node));

                /* Create a linked list & put the accepted values
                 * into a linked list.*/
                current->name=(char *)malloc(strlen(name));

                strcpy(current->name,name);
                current->marks=marks;

                printf("\n%s",current->name);
                printf("\n%d",current->marks);

                if(head == NULL)
                {
                    head = current;
                    prev = head;
                }
                else
                {
                    prev->next = current;
                }
                current->next = NULL;
                prev = current;
                count++;
            }
            printf("count:\n%d",count);
        }
    }
    fclose(ifp);
    
    /*Sort a linked list in the descending order*/
    for(i = 0;i < count;i++)
    {
        current = head;
        prev=current;
        temp = current->next;

        while(temp != NULL)
        {
            if(current->marks < temp->marks)
            {
                if ( head == current)
                {
                    head = temp;
                    current->next = temp->next;
                    temp->next = current;
                    prev = temp;
                    temp = current->next;
                }
                else
                {
                prev->next = temp;
                current->next = temp->next;
                temp->next = current;
                prev = temp;
                temp = current->next;
                }
            }
            else
            {
                prev = current;
                current = current->next;
                temp = temp->next;
            }
        }
    }
    
    /*Accepting the number of topers user want to display */
    printf("Enter the number of toppers you want to display:");
    scanf("%d",&n);

    current = head;

    /*Print the "n" topers*/
    for(j = 0;j < n;j++)
    {
     if(current != NULL)
    {
      printf("\n%s\n",current->name);
      current=current->next;
    }
    }
free(name);
}
