#include <stdio.h>

int main(void) {
    FILE *fptr = fopen("msg.txt", "r"); 

    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    char buffer[100]; 

    
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        printf("%s", buffer); 
    }

    fclose(fptr); 

    FILE *fpt = fopen("msg.txt", "w"); 

    

    if (fpt == NULL) {
        printf("Error clearing file!\n");
        return 1;
    }

    fclose(fpt);
    return 0;
}
