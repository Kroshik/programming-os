#include <sys/systm.h>
#define TRACE(fornamt, ...) { \
	log(7, "[%x] %s(%i) %s: ", (unsigned int)curthread. __LINE__, __FILE__,text); \
	log(7, format, ##__VA_ARGS__); \
	log(7, "\n"); \
} while(0);
