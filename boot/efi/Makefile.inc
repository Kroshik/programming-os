# $FreeBSD: releng/10.3/sys/boot/efi/Makefile.inc 293660 2016-01-11 15:30:19Z emaste $

BINDIR?=	/boot

.if ${MACHINE_CPUARCH} == "i386"
CFLAGS+=        -march=i386
CFLAGS+=	-msoft-float
.endif

# Options used when building app-specific efi components
# See conf/kern.mk for the correct set of these
CFLAGS+=	-ffreestanding -Wformat
LDFLAGS+=	-nostdlib

.if ${MACHINE_CPUARCH} == "amd64"
CFLAGS+=	-fshort-wchar
CFLAGS+=	-mno-red-zone
CFLAGS+=	-mno-mmx -mno-sse
CFLAGS.clang+=	-mno-aes -mno-avx
CFLAGS+=	-msoft-float
.endif


.include "../Makefile.inc"
