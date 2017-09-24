#pragma once

int filewriter_init_module(void);

int filewriter_deinit_module(void);

int filewriter_write(struct thread *td, char *line, u_int len);

int filewriter_trace(struct thread *td, int linen,
					 char *file, char *line, u_int len);

#define TRACE(text) { \
	filewriter_trace(curthread, __LINE__, __FILE__, text, strlen(text)); \
} while(0)
