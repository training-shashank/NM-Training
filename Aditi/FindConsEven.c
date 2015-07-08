/*Program to find the "n" consecutive even numbers aftre given number "k".
 * Author: Aditi
 * Date: 02-Jul-2015
 * 
 * COPYRIGHT: (C) 2015 - All rights reserved - Network Marvels (I) Pvt. Ltd.,
 * Thane (India)
 *----------------------------------------------------------------------------
 * Description: Program for calculating n consecutive even numbers after 
 * given number k.
 * The program accepts the input by command line arguments,from
 * the file where numbers will be scanned line by line.
 * The input will be integer k from which the consecutive even number to be 
 * displayed and integer n which is the count of how many even numbers to be 
 * displayed.
 * The input will be processed to validate  the parameters and calculate the 
 * consecutive even numbers from the starting  number k.
 *-----------------------------------------------------------------------------
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
 *-----------------------------------------------------------------------------
 */
#include<ctype.h>
#include<string.h>
#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#define MAX_SIZE 100

char *msg;
/*Function declaration*/
int ValidateParam(char *,char *);
int  FindEven(char * ,char *);

int main(int argc,char *argv[])
{
    int n,j, k,i; FILE *ifp;char *strptr1,*strptr2;

    /*pointer memory allocation*/
    strptr1=(char *)malloc(sizeof(char));
    strptr2=(char *)malloc(sizeof(char));
    msg=(char *)malloc(MAX_SIZE);
    
    /*Print the help*/
    if(argc==2)
    {
        if(strcmp(argv[1],"--help")==0)
        {
            printf("\nProgram is calculating n consecutive even"
                    "numbers after a given number k\n");
            return 1;
        }
								
    }

    /*Accepting input through file*/
    if(argc==3)
    {
        if((strcmp(argv[1],"-f")==0))
        {   
            ifp=fopen(argv[2],"r");
            /*If file pointer points to the null then file cannot be opened*/
            if(ifp==NULL)
            {
                fprintf(stderr,"cant open input file!\n");
            }
            else
            {
                while(fscanf(ifp,"%s %s",strptr1,strptr2)!=EOF)
                {
                    printf("\n%s",strptr1);
                    printf("\n%s",strptr2);
                    FindEven(strptr1,strptr2);
                }
                fclose(ifp);
                return 1;
            }
        }
    
        /* Accepting an input from command line argument*/
        else
        {
            strptr1=(argv[1]);
            strptr2=(argv[2]);
            printf("\nThe integer to be start with and no of even no to be"
                    "displayed are resp:%s %s \n ",strptr1,strptr2);
        }
    }

    
    /*Accepting standard input*/
    else
    {
        //Accepting the starting integer to print consecutive even number
        printf("please enter the integer to be start with"
                ",to print consecutive even numbers:");
        scanf("\n%s",strptr1);
        
        //Accepting an integer to limit the printing of consrcutive even integers
        printf("plaese enter how many consecutive numbers to be"
            " displayed from given number:");
        scanf("\n%s",strptr2);
       
    }
   
    if(ValidateParam(strptr1,strptr2)==1)
    {
        FindEven(strptr1,strptr2);
    }
    else
    {
        printf(msg);
        
    }
}

/*Print the consecutive even numbers*/    
int FindEven(char *strptr1,char *strptr2)
{   int i;
    int k=atoi(strptr1);
    int n=atoi(strptr2);
    printf("\nThe consecutive even numbers are:");
    for(i=0;i<(2*n);i++)
    {
        k=k+1;
        if(k%2==0)//Check whether number is even or not
        {
            printf("\n%d",k);
        }
         
    }
    printf("\n");
}



/* parameter validation and printing even numbers is done
 * giv_num is a number enterd by user as a initial number
 * limit is the count for how many consecutive even numbers
 * to be displayed.This function checks that giv_num,limit
 * enterd ar within the range or not and then next even no
 * .is calculated.
 */

int ValidateParam(char *strptr1,char *strptr2)
{
    /*Parameter validation is done by checking the upper limit of
     * of the integer values
     */
    int k, n;
    if(sscanf(strptr1,"%i",&k)&&(sscanf(strptr2,"%i",&n)))
    {
        if((!((long int)(k+n*2)<(long int)k))&&(n>0))
        {   
          return 1;
        }
        else
       {
            strcpy(msg,"\nThe entered numbers are exceeding the limit\n");
            return 0;
        }
   }
   else
   {
        strcpy(msg,"\n Only Integers to be entered\n");
         return 0;
   }
   free (strptr1);
   free(strptr2);
   free(msg);

}





      

            









