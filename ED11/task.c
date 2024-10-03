/*
*This is the program of Serving dosas from the stack to the eaters standing in the queue
*ED11
*Createt by Rushabh Goswami (164992)
*/

#include<stdio.h>
#include<stdlib.h>

int main() {
    /* Declare number of eaters and dosas */
    printf("How many eaters and dosas are there?: ");
    int n;
    scanf("%d", &n);

    /* Dynamically allocate arrays for dosas and eaters */
    int dosas[n], eaters[n];

    /* Input dosas in the stack */
    printf("Enter dosas in the stack: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &dosas[i]);
    }

    /* Input eaters in the queue */
    printf("Enter eaters in the queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &eaters[i]);
    }

    /* Initialize variables for stack and queue positions */
    int top = 0, rear = n - 1, front = 0;
    int remainingEaters = n, failedAttempts = 0;

    /* Process until either all eaters are fed or failure condition is met */
    while (remainingEaters > failedAttempts && top >= 0) {
    
        if (dosas[top] == eaters[front]) {
        
            /* If dosa matches eater, serve dosa and update positions */
            failedAttempts = 0;
            remainingEaters--;
            front++;
            top++;

            /* Reset front if it exceeds array bounds */
            if (front == n)
                front = 0;
        } else {
        
            /* If dosa does not match, rotate eater to the end of the queue */
            failedAttempts++;
            rear++;
            
            if (rear == n)
                rear = 0;
                
            eaters[rear] = eaters[front];
            front++;

            /* Reset front if it exceeds array bounds */
            if (front == n)
                front = 0;
        }
    }

    /* Output result based on remaining eaters */
    if (failedAttempts != 0)
        printf("%d eaters remain hungry.\n", remainingEaters);
    else
        printf("All eaters got their dosas.\n");

    return 0;
}

