#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/pcpu.h>
#include <sys/proc.h>
#include <sys/syscallsubr.h>
#include <sys/fcntl.h>
#include <sys/file.h>
#include <sys/sysproto.h>
#include <sys/filewriter.h>

__FBSDID("$FreeBSD: releng/10.3/sys/kern/kern_filewriter.c 264366 2014-04-12 06:50:11Z dchagin $");

// some simple defines to keep the code clean
#define MODNAME "filewriter"
#define MODVERSION  "1.0"
#define PATH "/var/log/test23.log"

// some ugly globals vars, we may look at getting rid of these.
static int filewriter_log_fd = -1;
static volatile int filewriter_hooked = 0;
static char filewriter_line[4096];

static int
filewriter_writelog(struct thread *td, int fd, char *line, u_int len)
{
  struct uio auio;
  struct iovec aiov;
  int err;

  bzero(&aiov, sizeof(aiov));
  bzero(&auio, sizeof(auio));
  
  aiov.iov_base = line;
  aiov.iov_len = len;
  
  auio.uio_iov = &aiov;
  auio.uio_offset = 0;
  auio.uio_segflg = UIO_SYSSPACE;
  auio.uio_rw = UIO_WRITE;
  auio.uio_iovcnt = 1;
  auio.uio_resid = len;

  auio.uio_td = td;

  err = kern_writev(td, fd, &auio);

  return err;
}

int filewriter_write(struct thread *td, char *line, u_int len)
{
	return filewriter_writelog(td, filewriter_log_fd, line, len);
}

int filewriter_trace(struct thread *td, int linen,
					 char *file, char *line, u_int len)
{
	int res = 0;
    sprintf(filewriter_line, "[%x] %i %s: %s \n", (unsigned int)td, linen, file, line);
	res |= filewriter_write(td, line, len);
	return res;
}

static int
filewriter_closelog(struct thread *td, int fd)
{
  if(fd)
  {
    return kern_close(td, fd);
  }
  return 0;
}

static int
filewriter_openlog(struct thread *td, int *fd, char *path)
{
  int error;
  error = kern_open(td, path, UIO_SYSSPACE, O_WRONLY | O_CREAT | O_APPEND, 0644);
  if (!error)
  {
    *fd = td->td_retval[0];
  }
  return error;
}

// called when the module is first loaded into the kernel, hooking our functions into
// the IP stack using pfil hooks. These hooks are designed for firewall processing,
// but work equally well for our purposes - we just never tell the stack to drop a packet.
int
filewriter_init_module(void)
{
    // if we're alredy hooked in, do nothing
    if (filewriter_hooked)
        return (0);

    filewriter_hooked = 1;

    filewriter_openlog(curthread, &filewriter_log_fd, PATH);

	TRACE("init_module");

    return 0;
}

// called when the module is unloaded from the kernel, unhooking our functions from
// the IP stacks. 
int
filewriter_deinit_module(void)
{
    // if we're already unhooked, do nothing
    if (!filewriter_hooked)
        return (0);

    // let our module know we're no longer hooked in
    filewriter_hooked = 0;

	TRACE("deinit_module");

    filewriter_closelog(curthread, filewriter_log_fd);

    return 0;
}
