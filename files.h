static const char *security_directories[1] = {
    "bsd"
};

static const char *kern_files[27] = {
    "ostype",
    "osrelease",
    "osrevision",
    "version",
    "maxvnodes",
    "maxproc",
    "maxprocperuid",
    "maxfiles",
    "maxfilesperproc",
    "argmax",
    "securelevel",
    "hostname",
    "hostid",
    "clockrate",
    "posix1version",
    "ngroups",
    "job_control",
    "saved_ids",
    "boottime",
    "domainname",
    "filedelay",
    "dirdelay",
    "metadelay",
    "osreldate",
    "bootfile",
    "corefile",
    "logsigexit"
};

static const char *security_bsd_files[4] = {
    "suser_enabled",
    "see_other_uids",
    "unprivileged_proc_debug",
    "unprivileged_read_msgbuf"
};

static const char *vm_files[1] = {
    "loadavg"
};

static const char *hw_files[10] = {
    "machine",
    "model",
    "ncpu",
    "byteorder",
    "physmem",
    "usermem",
    "pagesize",
    "floatingpoint",
    "machine_arch",
    "realmem"
};

static const char *kern_files[3] = {
    "adjkerntz",
    "disable_rtc_set",
    "guessed_bootdev"
};

static const char *kern_files[20] = {
    "cs_path",
    "bc_base_max",
    "bc_dim_max",
    "bc_scale_max",
    "bc_string_max",
    "coll_weights_max",
    "expr_nest_max",
    "line_max",
    "re_dup_max",
    "posix2_version",
    "posix2_c_bind",
    "posix2_c_dev",
    "posix2_char_term",
    "posix2_fort_dev",
    "posix2_fort_run",
    "posix2_localedef",
    "posix2_sw_dev",
    "posix2_upe",
    "stream_max",
    "tzname_max"
};