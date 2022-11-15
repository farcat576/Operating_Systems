#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE3(Q2,int*,src,int*,dest,int,len){
	int buffer[8];
	if (__copy_from_user(buffer,src,sizeof(int)*(len))) return -EFAULT;
	if (__copy_to_user(dest,buffer,sizeof(int)*(len))) return -EFAULT;
	return 0;
}
