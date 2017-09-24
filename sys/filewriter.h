#pragma once

#include <sys/systm.h>

#define TRACE(text) { \
	log(7, "[%x] %i %s: %s \n", (unsigned int)curthread, __LINE__, __FILE__, text); \
} while(0)
