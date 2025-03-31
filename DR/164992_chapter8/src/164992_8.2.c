/*
 * Program: Custom Buffered I/O
 * Author:Rushabh Goswami
 * Created Date: 21/12/24
 * Description: This program demonstrates a simplified implementation of a custom 
 *              buffered input/output system similar to standard C I/O. It defines
 *              functions for reading and writing with buffering and uses them in a 
 *              program that echoes input until the character 'x' is encountered.
 */

/* Required header files */
#include <stdlib.h>  /* For malloc and other utility functions */
#include <unistd.h>  /* For read, write system calls */

/* Redefine NULL to ensure compatibility */
#ifdef NULL
#undef NULL
#endif
#define NULL 0

/* Constants */
#define EOF (-1)           /* End of File marker */
#define BUFSIZE 1024       /* Size of buffer */
#define OPEN_MAX 20        /* Maximum number of files open at once */

/* Structure to represent file information */
typedef struct _iobuf {
    int cnt;    /* Characters left in buffer */
    char *ptr;  /* Pointer to next character */
    char *base; /* Location of the buffer */
    int flag;   /* File access mode */
    int fd;     /* File descriptor */
} FILE;

/* File objects for standard streams */
extern FILE _iob[OPEN_MAX];

/* Define standard input and output */
#define stdin (&_iob[0])
#define stdout (&_iob[1])

/* Flags for file access modes */
enum _flags {
    _READ = 01,  /* File open for reading (binary 1) */
    _WRITE = 02, /* File open for writing (binary 10) */
    _UNBUF = 03, /* File is unbuffered (binary 11) */
    _EOF = 010,  /* EOF has occurred (binary 1000) */
    _ERR = 020   /* Error occurred on this file (binary 10000) */
};

/* Function prototypes */
int _fillbuf(FILE *fp);           /* Fill input buffer */
int _flushbuf(int c, FILE *fp);   /* Flush output buffer */

/* Macros for simplified I/O operations */
#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))
#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

/*
 * _fillbuf: Allocate and fill the input buffer.
 * Arguments:
 *   fp - Pointer to the FILE structure
 * Returns:
 *   The next character in the buffer, or EOF on failure.
 */
int _fillbuf(FILE *fp) {
    int bufsize;

    /* Ensure the file is open for reading */
    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ) {
        return EOF;
    }

    /* Determine buffer size based on mode */
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;

    /* Allocate buffer if not already allocated */
    if (fp->base == NULL) {
        if ((fp->base = (char *)malloc(bufsize)) == NULL) {
            return EOF; /* Buffer allocation failed */
        }
    }

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    /* Handle read errors or EOF */
    if (--fp->cnt < 0) {
        if (fp->cnt == -1) {
            fp->flag |= _EOF;
        } else {
            fp->flag |= _ERR;
        }
        fp->cnt = 0;
        return EOF;
    }

    return (unsigned char)*fp->ptr++;
}

/*
 * _flushbuf: Flush the output buffer.
 * Arguments:
 *   c - Character to write
 *   f - Pointer to the FILE structure
 * Returns:
 *   The character written, or EOF on failure.
 */
int _flushbuf(int c, FILE *f) {
    int num_written, bufsize;
    unsigned char uc = c;

    /* Ensure the file is open for writing */
    if ((f->flag & (_WRITE | _EOF | _ERR)) != _WRITE) {
        return EOF;
    }

    /* Allocate buffer if not already allocated */
    if (f->base == NULL && ((f->flag & _UNBUF) == 0)) {
        if ((f->base = malloc(BUFSIZE)) == NULL) {
            f->flag |= _UNBUF;
        } else {
            f->ptr = f->base;
            f->cnt = BUFSIZE - 1;
        }
    }

    /* Handle unbuffered writes */
    if (f->flag & _UNBUF) {
        f->ptr = f->base = NULL;
        f->cnt = 0;
        if (c == EOF) {
            return EOF;
        }
        num_written = write(f->fd, &uc, 1);
        bufsize = 1;
    } else {
        /* Buffered writes */
        bufsize = (int)(f->ptr - f->base);
        num_written = write(f->fd, f->base, bufsize);
        f->ptr = f->base;
        f->cnt = BUFSIZE - 1;
    }

    if (num_written == bufsize) {
        return c;
    } else {
        f->flag |= _ERR;
        return EOF;
    }
}

/* File objects for standard streams */
FILE _iob[OPEN_MAX] = {
    {0, (char *)0, (char *)0, _READ, 0},               /* stdin */
    {0, (char *)0, (char *)0, _WRITE, 1},              /* stdout */
    {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}      /* stderr */
};

/*
 * main: Entry point of the program.
 * Arguments:
 *   argc - Number of command-line arguments
 *   argv - Array of command-line arguments
 * Returns:
 *   0 on successful execution.
 * Description:
 *   Reads input character by character and echoes it to standard output
 *   until the character 'x' is encountered.
 */
int main(int argc, char *argv[]) {
    int c;

    while ((c = getchar()) != 'x') {
        putchar(c);
    }

    return 0;
}

