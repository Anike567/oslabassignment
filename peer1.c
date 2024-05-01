#include <stdio.h>
#include <stdbool.h>

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main(void) {
    FILE *fptr;
    fptr = fopen("msg.txt", "w");
    if (fptr == NULL) {
        printf("Error opening the file\n");
        return 1; 
    }

    int num;
    scanf("%d", &num);

    char msg1[] = {'P', 'r', 'i', 'm', 'e', '\0'};
    char msg2[] = {'N', 'o', 't', ' ', 'p', 'r', 'i', 'm', 'e', '\0'};

    if (is_prime(num)) {
        fprintf(fptr, "%s\n", msg1); 
    } else {
        fprintf(fptr, "%s\n", msg2); 
    }

    fclose(fptr); 

    return 0; 
}
