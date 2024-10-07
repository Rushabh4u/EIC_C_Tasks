/*
*This code finds a specific string into the text file and replace it with some other text.
*Created by Rushabh Goswami (164992)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
 * Function to find and replace all occurrences of old_text with new_text 
 * in a file specified by the file_path.
 */
void find_and_replace(const char *file_path, const char *old_text, const char *new_text) {
    FILE *file;
    long file_size;
    char *buffer;

    /* 
     * Open the file in read mode. If the file cannot be opened,
     * print an error message and return.
     */
    file = fopen(file_path, "r");
    if (!file) {
        printf("Could not open file %s for reading.\n", file_path);
        return;
    }

    /* 
     * Find the size of the file by moving the file pointer to the end, 
     * then back to the beginning.
     */
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    /* 
     * Allocate memory for the file content. If memory allocation fails, 
     * print an error message, close the file, and return.
     */
    buffer = (char *)malloc(file_size + 1);
    if (!buffer) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return;
    }

    /* 
     * Read the content of the file into the buffer and 
     * null-terminate the buffer.
     */
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0'; 

    /* Close the file after reading its content */
    fclose(file); 

    /* 
     * Initialize pointers and calculate the lengths of old_text 
     * and new_text to be used in the replacement process.
     */
    char *pos = buffer;
    size_t old_text_len = strlen(old_text);
    size_t new_text_len = strlen(new_text);
    size_t len_diff = new_text_len - old_text_len;
    size_t count = 0;

    /* 
     * Count how many times old_text appears in the file content.
     * This is required to calculate the size of the new buffer.
     */
    char *temp;
    while ((temp = strstr(pos, old_text)) != NULL) {
        count++;
        pos = temp + old_text_len;
    }

    /* 
     * If old_text is not found in the file, print a message 
     * and free the allocated memory.
     */
    if (count == 0) {
        printf("'%s' not found in %s.\n", old_text, file_path);
        free(buffer);
        return;
    }

    /* 
     * Allocate a new buffer to store the updated content. 
     * If memory allocation fails, free the buffer and return.
     */
    size_t new_size = file_size + (len_diff * count);
    char *new_buffer = (char *)malloc(new_size + 1);
    if (!new_buffer) {
        printf("Memory allocation failed.\n");
        free(buffer);
        return;
    }

    /* 
     * Reset the position pointer to the start of the original buffer and 
     * start replacing occurrences of old_text with new_text.
     */
    pos = buffer;
    char *new_pos = new_buffer;
    while ((temp = strstr(pos, old_text)) != NULL) {
        /* Copy content before old_text */
        size_t len_before_old_text = temp - pos;
        memcpy(new_pos, pos, len_before_old_text);
        new_pos += len_before_old_text;

        /* Copy new_text instead of old_text */
        memcpy(new_pos, new_text, new_text_len);
        new_pos += new_text_len;

        /* Move past old_text in the original buffer */
        pos = temp + old_text_len;
    }

    /* Copy remaining content after the last occurrence of old_text */
    strcpy(new_pos, pos);

    /* 
     * Open the file in write mode to update its content with the new buffer.
     * If the file cannot be opened for writing, print an error message and free memory.
     */
    file = fopen(file_path, "w");
    if (!file) {
        printf("Could not open file %s for writing.\n", file_path);
        free(buffer);
        free(new_buffer);
        return;
    }

    /* Write the updated content to the file */
    fwrite(new_buffer, 1, new_size, file);

    /* Print a success message indicating the replacement is done */
    printf("Replaced '%s' with '%s' in %s.\n", old_text, new_text, file_path);

    /* Clean up: Close the file and free the allocated buffers */
    fclose(file);
    free(buffer);
    free(new_buffer);
}

int main() {
    /* Variables to store the file path, old text, and new text */
    char file_path[] = "rushabh.txt";
    char old_text[100];
    char new_text[100];

    /* 
     * Get the text to be replaced from the user. 
     * Use scanf to read the input from the user.
     */
    printf("Enter the text to be replaced: ");
    scanf("%s", old_text);

    /* 
     * Get the new text to replace the old text. 
     * Use scanf to read the input from the user.
     */
    printf("Enter the new text: ");
    scanf("%s", new_text);

    /* Call the find_and_replace function to perform the replacement */
    find_and_replace(file_path, old_text, new_text);

    return 0;
}

