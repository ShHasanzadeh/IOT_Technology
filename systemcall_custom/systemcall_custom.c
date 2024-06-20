
#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE0(systemcall_custom)

{
    printk("Helo World!!!!!!!!!!!\n");
    return 0;
}

