#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int boomersooner() {

   //inputed values
   int input;

   //loops through input
    while((scanf("%d", &input) == 1))
    {
        //multiple of 3
        if((input % 3) == 0 && (input % 5) == 0)
        {
            printf("Boomer Sooner!\n");
        }
        //multiple of 3
        else if((input % 3) == 0)
        {
            printf("Boomer!\n");
        }
        //multiple of 5
        else if((input % 5) == 0)
        {
            printf("Sooner!\n");
        }
        //not a multple of 3 or 5
        else
        {
            printf("%d\n", input);
        }
    }
    return 0;
    
}

int main (int argc, char **argv) {
    int result; 

    // Error Check
    if (argc > 1) {
        dprintf(STDERR_FILENO, "Usage: %s <n>\n", argv[0]);
        exit(0);
    }
    else {
        dprintf(STDERR_FILENO, "Starting BoomerSooner...\n");
    }

    // Call the function to print out values
    result = boomersooner();

    return result; // Return program status
}