include sys_call_x64_constants.inc  ;SYSCALL Constants
include sys_call_x64_errors.inc     ;SYSCALL Errors


    _SYSCALL_DEF MACRO _n,_St,_Args:VARARG
        .code
        _St PROC SYSTEMV _Args_:VARARG
           MOV R10,RCX ; SYSCALL uses R10 instead of RCX
           MOV RAX,_n
           SYSCALL
           RET
        _St ENDP
    ENDM
    
    _SYSCALL_DEF 0,_read,_fd,buf,count
    _SYSCALL_DEF 1,_write,_fd,buf,count
    _SYSCALL_DEF 2,_open,filename,_flags,mode
    _SYSCALL_DEF 3,_close,_fd:dword
    _SYSCALL_DEF 4,_stat,filename,statbuf
    _SYSCALL_DEF 5,_fstat,fd,statbuf
    _SYSCALL_DEF 6,_lstat,filename,statbuf
    _SYSCALL_DEF 7,_poll,ufds,nfds,timeout_msecs
    _SYSCALL_DEF 8,_lseek,fd,_offset,origin
    _SYSCALL_DEF 9,_mmap,_addr,_len,prot,_flags,fd,off
    _SYSCALL_DEF 10,_mprotect,start,_len,prot
    _SYSCALL_DEF 11,_munmap,_addr,_len
    _SYSCALL_DEF 12,_brk,brk
    _SYSCALL_DEF 13,_rt_sigaction,sig,act,oact,sigsetsize
    _SYSCALL_DEF 14,_rt_sigprocmask,how,nset,oset,sigsetsize
    _SYSCALL_DEF 15,_rt_sigreturn,_unused
    _SYSCALL_DEF 16,_ioctl,fd,cmd,arg
    _SYSCALL_DEF 17,_pread64,fd,buf,count,pos
    _SYSCALL_DEF 18,_pwrite64,fd,buf,count,pos
    _SYSCALL_DEF 19,_readv,fd,vec,vlen
    _SYSCALL_DEF 20,_writev,fd,vec,vlen
    _SYSCALL_DEF 21,_access,filename,mode
    _SYSCALL_DEF 22,_pipe,filedes
    _SYSCALL_DEF 23,_select,n,inp,outp,fd_setexp,tvp
    _SYSCALL_DEF 24,_sched_yield
    _SYSCALL_DEF 25,_mremap,_addr,old_len,new_len,_flags,ew_addr
    _SYSCALL_DEF 26,_msync,start,_len,_flags
    _SYSCALL_DEF 27,_mincore,start,_len,vec
    _SYSCALL_DEF 28,_madvise,start,_len_in,behavior
    _SYSCALL_DEF 29,_shmget,key,_size,shmflg
    _SYSCALL_DEF 30,_shmat,shmid,shmaddr,shmflg
    _SYSCALL_DEF 31,_shmctl,shmid,cmd,buf
    _SYSCALL_DEF 32,_dup,fildes
    _SYSCALL_DEF 33,_dup2,oldfd,newfd
    _SYSCALL_DEF 34,_pause
    _SYSCALL_DEF 35,_nanosleep,rqtp,rmtp
    _SYSCALL_DEF 36,_getitimer,which,value
    _SYSCALL_DEF 37,_alarm,seconds
    _SYSCALL_DEF 38,_setitimer,which,value,ovalue
    _SYSCALL_DEF 39,_getpid
    _SYSCALL_DEF 40,_sendfile,out_fd,in_fd,_offset,count
    _SYSCALL_DEF 41,_socket,family,_type,protocol
    _SYSCALL_DEF 42,_connect,fd,uservaddr,_addrlen
    _SYSCALL_DEF 43,_accept,fd,upeer_sockaddr,upeer_addrlen
    _SYSCALL_DEF 44,_sendto,fd,buff,_len,_flags,_addr,_addr_len
    _SYSCALL_DEF 45,_recvfrom,fd,ubuf,_size,_flags,_addr,_addr_len
    _SYSCALL_DEF 46,_sendmsg,fd,msg,_flags
    _SYSCALL_DEF 47,_recvmsg,fd,msg,_flags
    _SYSCALL_DEF 48,_shutdown,fd,how
    _SYSCALL_DEF 49,_bind,fd,umyaddr,_addrlen
    _SYSCALL_DEF 50,_listen,fd,backlog
    _SYSCALL_DEF 51,_getsockname,fd,usockaddr,usockaddr_len
    _SYSCALL_DEF 52,_getpeername,fd,usockaddr,usockaddr_len
    _SYSCALL_DEF 53,_socketpair,family,_type,protocol,usockvec
    _SYSCALL_DEF 54,_setsockopt,fd,level,optname,optval,optlen
    _SYSCALL_DEF 55,_getsockopt,fd,level,optname,optval,optlen
    _SYSCALL_DEF 56,_clone,clone_flags,newsp,parent_tid,child_tid
    _SYSCALL_DEF 57,_fork
    _SYSCALL_DEF 58,_vfork
    _SYSCALL_DEF 59,_execve,filename,argv,envp
    _SYSCALL_DEF 60,_exit,error_code
    _SYSCALL_DEF 61,_wait4,upid,stat_addr,_options,ru
    _SYSCALL_DEF 62,_kill,pid,sig
    _SYSCALL_DEF 63,_uname,_name
    _SYSCALL_DEF 64,_semget,key,nsems,semflg
    _SYSCALL_DEF 65,_semop,semid,tsops,nsops
    _SYSCALL_DEF 66,_semctl,semid,semnum,cmd,arg
    _SYSCALL_DEF 67,_shmdt,shmaddr
    _SYSCALL_DEF 68,_msgget,key,msgflg
    _SYSCALL_DEF 69,_msgsnd,msqid,msgp,msgsz,msgflg
    _SYSCALL_DEF 70,_msgrcv,msqid,msgp,msgsz,msgtyp,msgflg
    _SYSCALL_DEF 71,_msgctl,msqid,cmd,buf
    _SYSCALL_DEF 72,_fcntl,fd,cmd,arg
    _SYSCALL_DEF 73,_flock,fd,cmd
    _SYSCALL_DEF 74,_fsync,fd
    _SYSCALL_DEF 75,_fdatasync,fd
    _SYSCALL_DEF 76,_truncate,_path,_length
    _SYSCALL_DEF 77,_ftruncate,fd,_length
    _SYSCALL_DEF 78,_getdents,fd,dirent,count
    _SYSCALL_DEF 79,_getcwd,buf,_size
    _SYSCALL_DEF 80,_chdir,filename
    _SYSCALL_DEF 81,_fchdir,fd
    _SYSCALL_DEF 82,_rename,oldname,newname
    _SYSCALL_DEF 83,_mkdir,_pathname,mode
    _SYSCALL_DEF 84,_rmdir,_pathname
    _SYSCALL_DEF 85,_creat,_pathname,mode
    _SYSCALL_DEF 86,_link,oldname,newname
    _SYSCALL_DEF 87,_unlink,_pathname
    _SYSCALL_DEF 88,_symlink,oldname,newname
    _SYSCALL_DEF 89,_readlink,_path,buf,bufsiz
    _SYSCALL_DEF 90,_chmod,filename,mode
    _SYSCALL_DEF 91,_fchmod,fd,mode
    _SYSCALL_DEF 92,_chown,filename,user,_group
    _SYSCALL_DEF 93,_fchown,fd,user,_group
    _SYSCALL_DEF 94,_lchown,filename,user,_group
    _SYSCALL_DEF 95,_umask,_mask
    _SYSCALL_DEF 96,_gettimeofday,tv,tz
    _SYSCALL_DEF 97,_getrlimit,resource,rlim
    _SYSCALL_DEF 98,_getrusage,who,ru
    _SYSCALL_DEF 99,_sysinfo,info
    _SYSCALL_DEF 100,_times,info
    _SYSCALL_DEF 101,_ptrace,request,pid,_addr,data
    _SYSCALL_DEF 102,_getuid
    _SYSCALL_DEF 103,_syslog,_type,buf,_len
    _SYSCALL_DEF 104,_getgid
    _SYSCALL_DEF 105,_setuid,uid
    _SYSCALL_DEF 106,_setgid,gid
    _SYSCALL_DEF 107,_geteuid
    _SYSCALL_DEF 108,_getegid
    _SYSCALL_DEF 109,_setpgid,pid,pgid
    _SYSCALL_DEF 110,_getppid
    _SYSCALL_DEF 111,_getpgrp
    _SYSCALL_DEF 112,_setsid
    _SYSCALL_DEF 113,_setreuid,ruid,euid
    _SYSCALL_DEF 114,_setregid,rgid,egid
    _SYSCALL_DEF 115,_getgroups,gidsetsize,_grouplist
    _SYSCALL_DEF 116,_setgroups,gidsetsize,_grouplist
    _SYSCALL_DEF 117,_setresuid,ruid,euid,suid
    _SYSCALL_DEF 118,_getresuid,ruid,euid,suid
    _SYSCALL_DEF 119,_setresgid,rgid,egid,sgid
    _SYSCALL_DEF 120,_getresgid,rgid,egid,sgid
    _SYSCALL_DEF 121,_getpgid,pid
    _SYSCALL_DEF 122,_setfsuid,uid
    _SYSCALL_DEF 123,_setfsgid,gid
    _SYSCALL_DEF 124,_getsid,pid
    _SYSCALL_DEF 125,_capget,header,dataptr
    _SYSCALL_DEF 126,_capset,header,data
    _SYSCALL_DEF 127,_rt_sigpending,set,sigsetsize
    _SYSCALL_DEF 128,_rt_sigtimedwait,uthese,uinfo,uts,sigsetsize
    _SYSCALL_DEF 129,_rt_sigqueueinfo,pid,sig,uinfo
    _SYSCALL_DEF 130,_rt_sigsuspend,unewset,sigsetsize
    _SYSCALL_DEF 131,_sigaltstack,uss,uoss
    _SYSCALL_DEF 132,_utime,filename,times
    _SYSCALL_DEF 133,_mknod,filename,umode,dev
    _SYSCALL_DEF 135,_personality,personality
    _SYSCALL_DEF 136,_ustat,dev,uubuf
    _SYSCALL_DEF 137,_statfs,_pathname,buf
    _SYSCALL_DEF 138,_fstatfs,fd,buf
    _SYSCALL_DEF 139,_sysfs,_option,arg1,arg2
    _SYSCALL_DEF 140,_getpriority,which,who
    _SYSCALL_DEF 141,_setpriority,which,who,niceval
    _SYSCALL_DEF 142,_sched_setparam,pid,param
    _SYSCALL_DEF 143,_sched_getparam,pid,param
    _SYSCALL_DEF 144,_sched_setscheduler,pid,policy,param
    _SYSCALL_DEF 145,_sched_getscheduler,pid
    _SYSCALL_DEF 146,_sched_get_priority_max,policy
    _SYSCALL_DEF 147,_sched_get_priority_min,policy
    _SYSCALL_DEF 148,_sched_rr_get_interval,pid,interval
    _SYSCALL_DEF 149,_mlock,start,_len
    _SYSCALL_DEF 150,_munlock,start,_len
    _SYSCALL_DEF 151,_mlockall,_flags
    _SYSCALL_DEF 152,_munlockall
    _SYSCALL_DEF 153,_vhangup
    _SYSCALL_DEF 154,_modify_ldt,func,_ptr,bytecount
    _SYSCALL_DEF 155,_pivot_root,new_root,put_old
    _SYSCALL_DEF 156,__sysctl,args
    _SYSCALL_DEF 157,_prctl,_option,arg2,arg3,arg4,arg5
    _SYSCALL_DEF 158,_arch_prctl,task_task,code,_addr
    _SYSCALL_DEF 159,_adjtimex,txc_p
    _SYSCALL_DEF 160,_setrlimit,resource,rlim
    _SYSCALL_DEF 161,_chroot,filename
    _SYSCALL_DEF 162,_sync
    _SYSCALL_DEF 163,_acct,_name
    _SYSCALL_DEF 164,_settimeofday,tv,tz
    _SYSCALL_DEF 165,_mount,dev_name,dir_name,_type,_flags,data
    _SYSCALL_DEF 166,_umount2,target,_flags
    _SYSCALL_DEF 167,_swapon,specialfile,swap_flags
    _SYSCALL_DEF 168,_swapoff,specialfile
    _SYSCALL_DEF 169,_reboot,magic1,magic2,cmd,arg
    _SYSCALL_DEF 170,_sethostname,_name,_len
    _SYSCALL_DEF 171,_setdomainname,_name,_len
    _SYSCALL_DEF 172,_iopl,level,regs
    _SYSCALL_DEF 173,_ioperm,from,num,turn_on
    _SYSCALL_DEF 175,_init_module,umod,_len,uargs
    _SYSCALL_DEF 176,_delete_module,name_user,_flags
    _SYSCALL_DEF 179,_quotactl,cmd,special,id,_addr
    _SYSCALL_DEF 186,_gettid
    _SYSCALL_DEF 187,_readahead,fd,_offset,count
    _SYSCALL_DEF 188,_setxattr,_pathname,_name,value,_size,_flags
    _SYSCALL_DEF 189,_lsetxattr,_pathname,_name,value,_size,_flags
    _SYSCALL_DEF 190,_fsetxattr,fd,_name,value,_size,_flags
    _SYSCALL_DEF 191,_getxattr,_pathname,_name,value,_size
    _SYSCALL_DEF 192,_lgetxattr,_pathname,_name,value,_size
    _SYSCALL_DEF 193,_fgetxattr,fd,_name,value,_size
    _SYSCALL_DEF 194,_listxattr,_pathname,list,_size
    _SYSCALL_DEF 195,_llistxattr,_pathname,list,_size
    _SYSCALL_DEF 196,_flistxattr,fd,list,_size
    _SYSCALL_DEF 197,_removexattr,_pathname,_name
    _SYSCALL_DEF 198,_lremovexattr,_pathname,_name
    _SYSCALL_DEF 199,_fremovexattr,fd,_name
    _SYSCALL_DEF 200,_tkill,pid,sig
    _SYSCALL_DEF 201,_time,tloc
    _SYSCALL_DEF 202,_futex,uaddr,op,val,utime,uaddr2,val3
    _SYSCALL_DEF 203,_sched_setaffinity,pid,_len,user_mask_ptr
    _SYSCALL_DEF 204,_sched_getaffinity,pid,_len,user_mask_ptr
    _SYSCALL_DEF 206,_io_setup,nr_events,ctxp
    _SYSCALL_DEF 207,_io_destroy,ctx
    _SYSCALL_DEF 208,_io_getevents,ctx_id,min_nr,nr,events
    _SYSCALL_DEF 209,_io_submit,ctx_id,nr,iocbpp
    _SYSCALL_DEF 210,_io_cancel,ctx_id,iocb,result
    _SYSCALL_DEF 212,_lookup_dcookie,cookie64,buf,_len
    _SYSCALL_DEF 213,_epoll_create,_size
    _SYSCALL_DEF 216,_remap_file_pages,start,_size,prot,pgoff,_flags
    _SYSCALL_DEF 217,_getdents64,fd,dirent,count
    _SYSCALL_DEF 218,_set_tid_address,tidptr
    _SYSCALL_DEF 219,_restart_syscall
    _SYSCALL_DEF 220,_semtimedop,semid,tsops,nsops,timeout
    _SYSCALL_DEF 221,_fadvise64,fd,_offset,_len,advice
    _SYSCALL_DEF 222,_timer_create,which_clock,timer_event_spec,created_timer_id
    _SYSCALL_DEF 223,_timer_settime,timer_id,_flags,new_setting,old_setting
    _SYSCALL_DEF 224,_timer_gettime,timer_id,setting
    _SYSCALL_DEF 225,_timer_getoverrun,timer_id
    _SYSCALL_DEF 226,_timer_delete,timer_id
    _SYSCALL_DEF 227,_clock_settime,which_clock,tp
    _SYSCALL_DEF 228,_clock_gettime,which_clock,tp
    _SYSCALL_DEF 229,_clock_getres,which_clock,tp
    _SYSCALL_DEF 230,_clock_nanosleep,which_clock,_flags,rqtp,rmtp
    _SYSCALL_DEF 231,_exit_group,error_code
    _SYSCALL_DEF 232,_epoll_wait,epfd,events,maxevents,timeout
    _SYSCALL_DEF 233,_epoll_ctl,epfd,op,fd,event
    _SYSCALL_DEF 234,_tgkill,tgid,pid,sig
    _SYSCALL_DEF 235,_utimes,filename,utimes
    _SYSCALL_DEF 237,_mbind,start,_len,mode,nmask,maxnode,_flags
    _SYSCALL_DEF 238,_set_mempolicy,mode,nmask,maxnode
    _SYSCALL_DEF 239,_get_mempolicy,policy,nmask,maxnode,_addr,_flags
    _SYSCALL_DEF 240,_mq_open,u_name,oflag,mode,u_attr
    _SYSCALL_DEF 241,_mq_unlink,u_name
    _SYSCALL_DEF 242,_mq_timedsend,mqdes,u_msg_ptr,msg_len,msg_prio,u_abs_timeout
    _SYSCALL_DEF 243,_mq_timedreceive,mqdes,u_msg_ptr,msg_len,u_msg_prio,u_abs_timeout
    _SYSCALL_DEF 244,_mq_notify,mqdes,u_notification
    _SYSCALL_DEF 245,_mq_getsetattr,mqdes,u_mqstat,u_omqstat
    _SYSCALL_DEF 246,_kexec_load,entry,nr_segments,segments,_flags
    _SYSCALL_DEF 247,_waitid,which,upid,infop,_options,ru
    _SYSCALL_DEF 248,_add_key,_type,_description,_payload,plen
    _SYSCALL_DEF 249,_request_key,_type,_description,_callout_info,destringid
    _SYSCALL_DEF 250,_keyctl,_option,arg2,arg3,arg4,arg5
    _SYSCALL_DEF 251,_ioprio_set,which,who,ioprio
    _SYSCALL_DEF 252,_ioprio_get,which,who
    _SYSCALL_DEF 253,_inotify_init
    _SYSCALL_DEF 254,_inotify_add_watch,fd,_pathname,_mask
    _SYSCALL_DEF 255,_inotify_rm_watch,fd,_s32wd
    _SYSCALL_DEF 256,_migrate_pages,pid,maxnode,old_nodes,new_nodes
    _SYSCALL_DEF 257,_openat,dfd,filename,_flags,mode
    _SYSCALL_DEF 258,_mkdirat,dfd,_pathname,mode
    _SYSCALL_DEF 259,_mknodat,dfd,filename,mode,dev
    _SYSCALL_DEF 260,_fchownat,dfd,filename,user,_group,flag
    _SYSCALL_DEF 261,_futimesat,dfd,filename,utimes
    _SYSCALL_DEF 262,_newfstatat,dfd,filename,statbuf,flag
    _SYSCALL_DEF 263,_unlinkat,dfd,_pathname,flag
    _SYSCALL_DEF 264,_renameat,oldfd,oldname,newfd,newname
    _SYSCALL_DEF 265,_linkat,oldfd,oldname,newfd,newname,_flags
    _SYSCALL_DEF 266,_symlinkat,oldname,newfd,newname
    _SYSCALL_DEF 267,_readlinkat,dfd,_pathname,buf,bufsiz
    _SYSCALL_DEF 268,_fchmodat,dfd,filename,mode
    _SYSCALL_DEF 269,_faccessat,dfd,filename,mode
    _SYSCALL_DEF 270,_pselect6,n,inp,outp,exp,tsp,sig
    _SYSCALL_DEF 271,_ppoll,ufds,nfds,tsp,sigmask,sigsetsize
    _SYSCALL_DEF 272,_unshare,unshare_flags
    _SYSCALL_DEF 273,_set_robust_list,head,_len
    _SYSCALL_DEF 274,_get_robust_list,pid,head_ptr,_len_ptr
    _SYSCALL_DEF 275,_splice,fd_in,off_in,fd_out,off_out,_len,_flags
    _SYSCALL_DEF 276,_tee,fdin,fdout,_len,_flags
    _SYSCALL_DEF 277,_sync_file_range,fd,_offset,bytes,_flags
    _SYSCALL_DEF 278,_vmsplice,fd,iov,nr_segs,_flags
    _SYSCALL_DEF 279,_move_pages,pid,nr_pages,pages,nodes,status,_flags
    _SYSCALL_DEF 280,_utimensat,dfd,filename,utimes,_flags
    _SYSCALL_DEF 281,_epoll_pwait,epfd,events,maxevents,timeout,sigmask,sigsetsize
    _SYSCALL_DEF 282,_signalfd,ufd,user_mask,_sizemask
    _SYSCALL_DEF 283,_timerfd_create,clockid,_flags
    _SYSCALL_DEF 284,_eventfd,count
    _SYSCALL_DEF 285,_fallocate,fd,mode,_offset,_len
    _SYSCALL_DEF 286,_timerfd_settime,ufd,_flags,utmr,otmr
    _SYSCALL_DEF 287,_timerfd_gettime,ufd,otmr
    _SYSCALL_DEF 288,_accept4,fd,upeer_sockaddr,upeer_addrlen,_flags
    _SYSCALL_DEF 289,_signalfd4,ufd,user_mask,_sizemask,_flags
    _SYSCALL_DEF 290,_eventfd2,count,_flags
    _SYSCALL_DEF 291,_epoll_create1,_flags
    _SYSCALL_DEF 292,_dup3,oldfd,newfd,_flags
    _SYSCALL_DEF 293,_pipe2,filedes,_flags
    _SYSCALL_DEF 294,_inotify_init1,_flags
    _SYSCALL_DEF 295,_preadv,fd,vec,vlen,pos_l,pos_h
    _SYSCALL_DEF 296,_pwritev,fd,vec,vlen,pos_l,pos_h
    _SYSCALL_DEF 297,_rt_tgsigqueueinfo,tgid,pid,sig,uinfo
    _SYSCALL_DEF 298,_perf_event_open,attr_uptr,pid,cpu,_group_fd,_flags
    _SYSCALL_DEF 299,_recvmmsg,fd,mmsg,vlen,_flags,timeout
    _SYSCALL_DEF 300,_fanotify_init,_flags,event_f_flags
    _SYSCALL_DEF 301,_fanotify_mark,fanotify_fd,_flags,_mask,dfd,_pathname
    _SYSCALL_DEF 302,_prlimit64,pid,resource,new_rlim,old_rlim
    _SYSCALL_DEF 303,_name_to_handle_at,dfd,_name,handle,mnt_id,flag
    _SYSCALL_DEF 304,_open_by_handle_at,dfd,_name,handle,mnt_id,_flags
    _SYSCALL_DEF 305,_clock_adjtime,which_clock,tx
    _SYSCALL_DEF 306,_syncfs,fd
    _SYSCALL_DEF 307,_sendmmsg,fd,mmmsg,vlen,_flags
    _SYSCALL_DEF 308,_setns,fd,nstype
    _SYSCALL_DEF 309,_getcpu,cpup,nodep,unused
    _SYSCALL_DEF 310,_process_vm_readv,pid,lvec,liovcnt,rvec,riovcnt,_flags
    _SYSCALL_DEF 311,_process_vm_writev,pid,lvec,liovcnt,rvec,riovcnt,_flags
    _SYSCALL_DEF 312,_kcmp,pid1,pid2,_type,idx1,idx2
    _SYSCALL_DEF 313,_finit_module,fd,uargs,_flags
    _SYSCALL_DEF 314,_sched_setattr,pid,sched_attrattr,_flags
    _SYSCALL_DEF 315,_sched_getattr,pid,sched_attrattr,_size,_flags
    _SYSCALL_DEF 316,_renameat2,olddfd,oldname,newdfd,newname,_flags
    _SYSCALL_DEF 317,_seccomp,op,_flags,uargs
    _SYSCALL_DEF 318,_getrandom,buf,count,_flags
    _SYSCALL_DEF 319,_memfd_create,uname_ptr,_flags
    _SYSCALL_DEF 320,_kexec_file_load,kernel_fd,initrd_fd,cmdline_len,cmdline_ptr,_flags
    _SYSCALL_DEF 321,_bpf,cmd,attr,_size
    _SYSCALL_DEF 322,_stub_execveat,dfd,filename,argv,envp,_flags
    _SYSCALL_DEF 323,_userfaultfd,_flags
    _SYSCALL_DEF 324,_membarrier,cmd,_flags
    _SYSCALL_DEF 325,_mlock2,start,_len,_flags
    _SYSCALL_DEF 326,_copy_file_range,fd_in,off_in,fd_out,off_out,_len,_flags
    _SYSCALL_DEF 327,_preadv2,fd,vec,vlen,pos_l,pos_h,_flags
    _SYSCALL_DEF 328,_pwritev2,fd,vec,vlen,pos_l,pos_h,_flags
