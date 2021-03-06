/*
 * Copyright (c) 2015-2016 Qlogic Corporation
 * All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _BXE_IOCTL_H_
#define _BXE_IOCTL_H_

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: releng/10.3/sys/dev/bxe/bxe_ioctl.h 293788 2016-01-12 23:16:27Z davidcs $");

#include <sys/ioccom.h>


struct bxe_grcdump {
    uint16_t pci_func;
    uint32_t grcdump_size;
    void *grcdump;
    uint32_t grcdump_dwords;
};
typedef struct bxe_grcdump bxe_grcdump_t;


/*
 * Read grcdump size
 */
#define BXE_GRC_DUMP_SIZE     _IOWR('e', 1, bxe_grcdump_t)

/*
 * Read grcdump
 */
#define BXE_GRC_DUMP          _IOWR('e', 2, bxe_grcdump_t)


#endif /* #ifndef _QLNX_IOCTL_H_ */
