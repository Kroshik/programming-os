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

// some simple defines to keep the code clean
#define MODNAME "filewriter"
#define MODVERSION  "1.0"
#define PATH "/var/log/test23.log"

// some ugly globals vars, we may look at getting rid of these.
static volatile int filewriter_hooked = 0;
static int testfd = 0;


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

  printf("fd: %u\n", fd);
  printf(aiov.iov_base);
  err = kern_writev(td, fd, &auio);
  printf("write err: %u\n", err);

  return err;
}


static int
filewriter_closelog(struct thread *td, int fd)
{
  printf("filewriter_closelog fd: %d\n", fd);
  if(fd)
  {
    struct close_args fdtmp;
    fdtmp.fd = fd;
    printf("filewriter_closelog thread ptr: %x\n", (unsigned int)td);
    return close(td, &fdtmp);
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
    printf("openlog fd: %d\n", *fd);
  }
  else
    printf("openlog failed\n");
  return error;
}

// called when the module is first loaded into the kernel, hooking our functions into
// the IP stack using pfil hooks. These hooks are designed for firewall processing,
// but work equally well for our purposes - we just never tell the stack to drop a packet.
static int
init_module(void)
{
    char filewriter_line[128];

    // if we're alredy hooked in, do nothing
    if (filewriter_hooked)
        return (0);

    filewriter_hooked = 1;

    filewriter_openlog(curthread, &testfd, PATH);

    sprintf(filewriter_line, "init_module()\tFile: %s\tcurthread ptr: %x\n", PATH, (unsigned int)curthread);

    filewriter_writelog(curthread, testfd, filewriter_line, strlen(filewriter_line));

    // print message to the user's current terminal as opposed to 
    // printf which prints to the kernel's stdout (which is attached 
    // to getty 0)
    uprintf("Loaded %s %s\n", MODNAME, MODVERSION);

    return 0;
}

// called when the module is unloaded from the kernel, unhooking our functions from
// the IP stacks. 
static int
deinit_module(void)
{
    char filewriter_line[128];

    // if we're already unhooked, do nothing
    if (!filewriter_hooked)
        return (0);

    // let our module know we're no longer hooked in
    filewriter_hooked = 0;

    sprintf(filewriter_line, "deinit_module()\tFile: %s\tcurthread ptr: %x\n\n", PATH, (unsigned int)curthread);

    filewriter_writelog(curthread, testfd, filewriter_line, strlen(filewriter_line)); 

    filewriter_closelog(curthread, testfd);

    uprintf("Unloaded %s %s\n", MODNAME, MODVERSION);

    return 0;
}

// This is the function that is called to load and unload the functions. It hands off
// to seperate functions to do the work.
static int load_handler(module_t mod, int what, void *arg)
{
	int err = 0;

	switch(what)
	{
		case MOD_LOAD:
      err = init_module();
			break;

		case MOD_UNLOAD:
      err = deinit_module();
			break;

		default:		
			err = EINVAL;
			break;
	}

	return(err);
}

// a struct that holds basic data on the module
static moduledata_t filewriter_mod =
{
	"filewriter",      //module's name
	load_handler, //execution entry point for the module
	NULL
};