typedef FILE *pl_stream;

pl_stream pl_stream_create(char *file);
void pl_stream_write_trace_name(pl_stream stream, char *name);
void pl_stream_write_file_name(pl_stream stream, char *filename);
void pl_stream_write_file_hash(pl_stream stream, char *hash);
void pl_stream_write_file_ref(pl_stream stream, char *ref);
void pl_stream_write_line_number(pl_stream stream, int lineno);
void pl_stream_close(pl_stream stream);
