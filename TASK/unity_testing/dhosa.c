#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE 100

int matchDhosas(int iStack[], int iNumOfEmp, int iQueue[]) {
    int iStackPointer = iNumOfEmp - 1;  // Start at the top of the stack
    int iQueueFront = 0;                // Initialize queue front
    int iUnmatchedCount = 0;            // Count unmatched employees

    while (iQueueFront <= iStackPointer) {
        if (iUnmatchedCount == (iStackPointer - iQueueFront + 1)) {
            // If we encounter consecutive unmatched elements
            return iStackPointer - iQueueFront + 1;
        }

        // Ensure stack is not empty before trying to access it
        if (iStackPointer >= 0) {
            // Check if the top of the stack matches the queue's front preference
            if (iQueue[iQueueFront] == iStack[iStackPointer]) {
                iStackPointer--;
                iQueueFront++;
                iUnmatchedCount = 0;  // Reset the unmatched count
            } else {
                iUnmatchedCount++;
                // Rotate the front to back if no match
                if (iQueueFront < MAX_SIZE - 1) {
                    iQueueFront++;
                }
            }
        } else {
            // If stack is empty, break out of the loop
            break;
        }
    }
    return iQueueFront - iStackPointer;
}

