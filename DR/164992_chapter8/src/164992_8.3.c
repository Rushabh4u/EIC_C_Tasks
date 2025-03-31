/*
 * Program: Simplified Custom I/O Library
 * Author: Rushabh Goswami
 * Date:  21/12/24
 * Description: A basic implementation of buffered I/O functions, mimicking
 *              standard C I/O, with functions for reading, writing, opening,
 *              flushing, and closing files.
 */

#include <fcntl.h>  /* For file control options like open, creat, lseek */
#include <stdlib.h> /* For malloc and free */
#include <unistd.h> /* For read, write, close */

/* Define constants */
#ifdef NULL
#undef NULL
#endif
#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024       /* Size of the buffer */
#define OPEN_MAX 20       /* Maximum number of files open at once */
#define PERMS 0666        /* RW permissions for owner, group, others */

/* File structure to manage I/O */
typedef struct _iobuf {
    int cnt;    /* Characters left in buffer */
    char *ptr;  /* Pointer to next character in buffer */
    char *base; /* Base of the buffer */
    int flag;   /* File access mode */
    int fd;     /* File descriptor */
} FILE;

/* File object array */
extern FILE _iob[OPEN_MAX];

/* Predefined file pointers */
#define stdin (&_iob[0])
#define stdout (&_iob[1])

/* File access flags */
enum _flags {
    _READ = 01,  /* File open for reading */
    _WRITE = 02, /* File open for writing */
    _UNBUF = 03, /* File is unbuffered */
    _EOF = 010,  /* EOF occurred */
    _ERR = 020   /* Error occurred */
};

/* Function prototypes */
int _fillbuf(FILE *);
int _flushbuf(int, FILE *);
FILE *fopen(char *, char *);
int fclose(FILE *);
int fflush(FILE *);

/* Macros for simplified I/O operations */
#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))
#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

/* File object array for standard streams */
FILE _iob[OPEN_MAX] = {
    {0, (char *)0, (char *)0, _READ, 0},              /* stdin */
    {0, (char *)0, (char *)0, _WRITE, 1},             /* stdout */
    {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}     /* stderr */
};

/*
 * fopen: Open a file and return a FILE pointer
 * Arguments:
 *   name - File name
 *   mode - Mode string ('r', 'w', 'a')
 * Returns:
 *   Pointer to FILE structure on success, NULL on failure.
 */
FILE *fopen(char *name, char *mode) {
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
        return NULL; /* Invalid mode */
    }

    /* Find a free slot in the _iob array */
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
        if ((fp->flag & (_READ | _WRITE)) == 0) {
            break;
        }
    }
    if (fp >= _iob + OPEN_MAX) {
        return NULL; /* No free slots */
    }

    /* Open the file based on the mode */
    if (*mode == 'w') {
        fd = creat(name, PERMS);
    } else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1) {
            fd = creat(name, PERMS);
        }
        lseek(fd, 0L, 2); /* Move to end for append */
    } else {
        fd = open(name, O_RDONLY, 0);
    }

    if (fd == -1) {
        return NULL; /* File couldn't be opened */
    }

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}

/*
 * _fillbuf: Allocate and fill the input buffer
 * Arguments:
 *   fp - Pointer to FILE structure
 * Returns:
 *   Next character in buffer, or EOF on failure.
 */
int _fillbuf(FILE *fp) {
    int bufsize;

    /* Ensure the file is open for reading */
    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ) {
        return EOF;
    }

    /* Determine buffer size */
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    /* Allocate buffer if not already allocated */
    if (fp->base == NULL) {
        if ((fp->base = (char *)malloc(bufsize)) == NULL) {
            return EOF; /* Buffer allocation failed */
        }
    }

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);

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
 * _flushbuf: Flush the output buffer
 * Arguments:
 *   c - Character to write
 *   f - Pointer to FILE structure
 * Returns:
 *   Character written, or EOF on failure.
 */
int _flushbuf(int c, FILE *f) {
    int num_written, bufsize;
    unsigned char uc = c;

    if ((f->flag & (_WRITE | _EOF | _ERR)) != _WRITE) {
        return EOF;
    }

    if (f->base == NULL && !(f->flag & _UNBUF)) {
        if ((f->base = malloc(BUFSIZ)) == NULL) {
            f->flag |= _UNBUF;
        } else {
            f->ptr = f->base;
            f->cnt = BUFSIZ - 1;
        }
    }

    if (f->flag & _UNBUF) {
        /* Unbuffered write */
        f->ptr = f->base = NULL;
        f->cnt = 0;
        num_written = write(f->fd, &uc, 1);
        bufsize = 1;
    } else {
        /* Buffered write */
        bufsize = f->ptr - f->base;
        num_written = write(f->fd, f->base, bufsize);
        f->ptr = f->base;
        f->cnt = BUFSIZ - 1;
    }

    if (num_written == bufsize) {
        return c;
    } else {
        f->flag |= _ERR;
        return EOF;
    }
}

/*
 * fflush: Flush a FILE stream
 * Arguments:
 *   f - Pointer to FILE structure, or NULL to flush all streams
 * Returns:
 *   0 on success, -1 on failure.
 */
int fflush(FILE *f) {
    int retval = 0;
    FILE *fp;

    if (f == NULL) {
        /* Flush all output streams */
        for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
            if ((fp->flag & _WRITE) && fflush(fp) == -1) {
                retval = -1;
            }
        }
    } else {
        if (!(f->flag & _WRITE)) {
            return -1;
        }
        _flushbuf(EOF, f);
        if (f->flag & _ERR) {
            retval = -1;
        }
    }
    return retval;
}

/*
 * fclose: Close a file and free resources
 * Arguments:
 *   f - Pointer to FILE structure
 * Returns:
 *   0 on success, -1 on failure.
 */
int fclose(FILE *f) {
    if (f == NULL) {
        return -1;
    }

    fflush(f);
    if (f->base) {
        free(f->base);
    }
    f->base = NULL;
    f->ptr = NULL;
    f->cnt = 0;
    f->flag = 0;

    return close(f->fd);
}

/*
 * main: Entry point of the program
 * Description:
 *   Reads input character by character until 'x' is encountered, echoing
 *   each character to standard output.
 */
int main(int argc, char *argv[]) {
    int c;

    while ((c = getchar()) != 'x') {
        putchar(c);
    }

    return 0;
}

