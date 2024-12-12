#include <stdio.h>
#include <ctype.h>

#define SIZE 1000
#define BUFSIZE 100

/* Buffer for ungetch function */
char buf[BUFSIZE];
int bufp = 0;

/* Function to get a character, either from buffer or standard input */
int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* Function to push a character back onto the input buffer */
void ungetch(int c) {
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* Function to extract the next integer from input */
int getint(int *pn) {
	int c, sign;

	/* Skip white space */
	while (isspace(c = getch()));

	/* Check if input is not a valid number */
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); /* Push back non-numeric character */
		return -1;  /* Invalid input */
	}

	sign = (c == '-') ? -1 : 1;

	/* Check for sign character */
	if (c == '+' || c == '-')
		c = getch();

	/* Ensure a digit follows sign */
	if (!isdigit(c))
		return 0; /* Invalid representation */

	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');

	*pn *= sign;

	if (c != EOF)
		ungetch(c); /* Push back the last character */

	return c;
}

int main(void) {
	int choice;

	do {
		int n = 0, s = 0, array[SIZE];
		printf("\n--- Integer Input Program ---\n");
		printf("1. Enter integers\n");
		printf("2. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		if (choice == 1) {
			printf("\nEnter integers (press Ctrl+D or EOF to stop):\n");

			/* Loop to read integers using getint */
			while (n < SIZE && getint(&array[n]) != EOF) {
				printf("Stored %d at index %d\n", array[n], n);
				n++;
			}

			printf("\nYou entered %d integers.\n", n);
			printf("The integers are:\n");
			for (s = 0; s < n; s++) {
				printf("%d ", array[s]);
			}
			printf("\n");
		} else if (choice != 2) {
			printf("Invalid choice. Please try again.\n");
		}

	} while (choice != 2);

	printf("Exiting the program. Goodbye!\n");
	return 0;
}

