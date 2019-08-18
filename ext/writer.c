#include <errno.h>
#include <stdio.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "php.h"
#include "writer.h"

extern int errno;

pl_stream pl_stream_create(char *file)
{
    pl_stream stream;
    char *dir;

    struct stat st = {0};
    dir = (char*) malloc((strlen(file) + 1) * sizeof(char));
    strcpy(dir, file);
    dir = dirname(dir);
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0700);
    }

    stream = fopen(file, "w");
    if (stream == NULL) {
        php_error(E_ERROR, "Error opening file \"%s\": %s\n", file, strerror(errno));
    }

    return stream;
}

void pl_stream_write_trace_name(pl_stream stream, char *name)
{
    fputs("@", stream);
    fputs(name, stream);
    fputs("\n", stream);
}

void pl_stream_write_file_name(pl_stream stream, char *filename)
{
    fputs("+", stream);
    fputs(filename, stream);
    fputs("\n", stream);
}

void pl_stream_write_file_hash(pl_stream stream, char *hash)
{
    fputs("#", stream);
    fputs(hash, stream);
    fputs("\n", stream);
}

void pl_stream_write_file_ref(pl_stream stream, char *ref)
{
    fputs(">", stream);
    fputs(ref, stream);
    fputs("\n", stream);
}

void pl_stream_write_line_number(pl_stream stream, int lineno)
{
    fprintf(stream, "%d\n", lineno);
}

void pl_stream_close(pl_stream stream)
{
    fclose(stream);
}
