/*
*This program prints the minimum and maximum limits of the signed and unsigned integer and floating point data types.
*Autor: Rushabh Goswami
*Created: 17/7/2024
*/

// Required Libraries
#include <stdio.h>
#include <limits.h>
#include<float.h>

int main() {
	//These lines prints the minimum and maximum limits of various data types which is already declared in limits.h & float.h header files.
    printf("Ranges for signed types:\n");
    printf("char:   %d to %d\n", CHAR_MIN, CHAR_MAX);
    printf("short:  %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("int:    %d to %d\n", INT_MIN, INT_MAX);
    printf("long:   %ld to %ld\n", LONG_MIN, LONG_MAX);

    printf("Ranges for unsigned types:\n");
    printf("unsigned char:  0 to %u\n", UCHAR_MAX);
    printf("unsigned short: 0 to %u\n", USHRT_MAX);
    printf("unsigned int:   0 to %u\n", UINT_MAX);
    printf("unsigned long:  0 to %lu\n", ULONG_MAX);
    
    printf("Ranges for floating point types:\n");
    printf("float:       %E to %E\n", FLT_MIN, FLT_MAX);
    printf("double:      %E to %E\n", DBL_MIN, DBL_MAX);
    printf("long double: %LE to %LE\n", LDBL_MIN, LDBL_MAX);

    return 0;
}

