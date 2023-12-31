#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//maximum size of all unicode characters
#define MAX_SIZE 1112064

//struct that stores unicode objects
struct UnicodeElement 
{
    //variable for frequency of unicode characters 
    int frequency;

    //variables for the bits of unicode characters in an character array
    unsigned char bytes[4];

}; typedef struct UnicodeElement UnicodeElement;

//swap function that is used by built-in c function (quick sort)
int swap(const void *X, const void *Y)
{
    int xCount, yCount;

    xCount = ((struct UnicodeElement *)X)->frequency;
    yCount = ((struct UnicodeElement *)Y)->frequency;

    if(yCount > xCount)
    {
        return 1;
    }
        else
        {
            return -1;
        }

}

//prints and sorts out unicode characters
void print(struct UnicodeElement element[], int size)
{
    //prints out unicode object values
    for (int i  = 0; i < size; i++)
    {
        //byte array
        unsigned char arr[4];
        
        //copy array of Unicode array elements
        arr[0] = element[i].bytes[0];
        arr[1] = element[i].bytes[1];
        arr[2] = element[i].bytes[2];
        arr[3] = element[i].bytes[3];

        unsigned char *str = &arr[0];

        //print out in correct format
        printf("%s", str);
        printf("->");
        printf("%d\n", element[i].frequency);
    }
    
}

int main(int argc, char **argv)
{
    //struct that points to unicode objects
    UnicodeElement *UnicodeArr = (malloc(MAX_SIZE * sizeof(UnicodeElement)));

    //variable for intialization of empty byte
    int byteEmpty;

    //varaible for bytes in a chacter array
    unsigned char arr[4];
    
    //built in c fucntion that sets all values of array to 0 in the memory
    memset(UnicodeArr, 0, sizeof(UnicodeArr));

   //variable that acess struct elements from unicode and tracks count
    int count = 0;

    //variable that stores the byte size result
    int result = 0;

    //varaiable that marks if character exists
    int marker = 0;
        
    //gets first byte by reading first unicode character
    byteEmpty = fgetc(stdin);

    //get first bytes of characters until it reaches EOF
    while(byteEmpty != EOF) 
    {
        //initialize result to 0 in loop
        result = 0;
        
            //checker to see what kind of bytes it is
            if (byteEmpty >= 240)
            { 		
                result = 4;
             
            } 
            else if (byteEmpty >= 224) 
            {  
                result = 3;
            } 
            else if (byteEmpty >= 192) 
            {  
                result = 2;
            }
            else
            {
                result = 1;
            }

            //read next bytes in character array
            if(result == 4)
            {
                arr[1] = (unsigned char)fgetc(stdin);
                arr[2] = (unsigned char)fgetc(stdin);
                arr[3] = (unsigned char)fgetc(stdin);
            }

            else if(result == 3)
            {
                arr[1] = (unsigned char)fgetc(stdin);
                arr[2] = (unsigned char)fgetc(stdin);
            }

            else if(result == 2)
            {
                arr[1] = (unsigned char)fgetc(stdin);
            }
        
        
        //varaible for the index used in loops
        int i;

        //initialize marker to 0 in loop
        marker = 0;

        //check to see if given unicode was already read in or not
        for(i = 0; i < count; i++)
        {
            //uses bitwise operators to check the byte correctness
            //if it matches all conditons it'll equal 1
            if(result == 4)
            {
                marker = (UnicodeArr[i].bytes[0] == (unsigned char) byteEmpty) & (UnicodeArr[i].bytes[1] ==  arr[1]) & (UnicodeArr[i].bytes[2] ==  arr[2]) & (UnicodeArr[i].bytes[3] ==  arr[3]);
            }
            else if(result == 3)
            {
                marker = (UnicodeArr[i].bytes[0] == (unsigned char) byteEmpty) & (UnicodeArr[i].bytes[1] ==  arr[1]) & (UnicodeArr[i].bytes[2] == arr[2]);
            }
            else if(result == 2)
            {
                marker = (UnicodeArr[i].bytes[0] == (unsigned char) byteEmpty) & (UnicodeArr[i].bytes[1] == arr[1]);
            }
            else
            {
                marker = (UnicodeArr[i].bytes[0] == (unsigned char) byteEmpty);
            }

            //break if character is found in array
            if(marker == 1)
            {
                UnicodeArr[i].frequency++;
                break;
            }
        }

        //if character is not found in array, add it and increase count by 1
        if(marker == 0)
        {
            //increment pointer by amount of characters
            UnicodeArr[count].frequency++;

            if(result == 1)
            {
                UnicodeArr[count].bytes[0] = byteEmpty;
            }
            if(result == 2)
            {
                UnicodeArr[count].bytes[0] = (unsigned char) byteEmpty;

                UnicodeArr[count].bytes[1] = arr[1];
            }
            if(result == 3)
            {
                UnicodeArr[count].bytes[0] = (unsigned char) byteEmpty;

                UnicodeArr[count].bytes[1] = arr[1];
                UnicodeArr[count].bytes[2] = arr[2];
            }
            if(result == 4)
            {
                UnicodeArr[count].bytes[0] = (unsigned char) byteEmpty;

                UnicodeArr[count].bytes[1] = arr[1];
                UnicodeArr[count].bytes[2] = arr[2];
                UnicodeArr[count].bytes[3] = arr[3];
            }
           
           //increment count of characters by 1
            count++;
        }
    }

    //quick sort built in c function
    qsort(UnicodeArr, count, sizeof(UnicodeElement), swap);

    //print out unicode character and the count
    print(UnicodeArr, count);
    
    return 0;
}