#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

//sh
#include <linux/kernel.h>
#include <string.h>
#include <errno.h>

#define MY_CUSTOM_SYSCALL_NUM 449


//sh
/*
long custom_syscall(void)
{
    return syscall(MY_CUSTOM_SYSCALL_NU);
}
int main(int argc, char *argv[])
{
    long activity;
    activity = custom_syscalll();

    if(activity < 0)
    {
        perror("Sorry! Your system call appears to have failed.\n");
    }

    else
    {

        printf("Congratulations! Your system call is functional. Run the command dmesg in the terminal and find out!\n");


    }

    return 0;
}
*/

////////////////////////


int main() {
    pid_t pid = getpid();
    const char *filename = "output.txt";

    long result = syscall(MY_CUSTOM_SYSCALL_NUM, pid, filename);

    if (result == 0) {
        printf("System call executed successfully.\n");
    } else {
        perror("System call failed");
    }

    return 0;
}

