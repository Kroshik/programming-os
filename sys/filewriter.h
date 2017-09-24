#pragma once

#include <sys/systm.h>

#define TRACE(format, ...) { \
	log(7, "[%x] %s(%i) %s: ", (unsigned int)curthread, __func__, __LINE__, __FILE__); \
	log(7, format, ##__VA_ARGS__); \
	log(7, "\n"); \
} while(0)
