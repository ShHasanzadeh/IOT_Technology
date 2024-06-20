
# Adding A System Call To The Linux Kernel (5.15.1) In Ubuntu (20.04 LTS) 

## Section 1 - Preparation  
# 1.1 - Fully update your operating system
~$ sudo apt update && sudo apt upgrade -y

# 1.2 - Download and install the essential packages to compile kernels.
~$ sudo apt install build-essential libncurses-dev libssl-dev libelf-dev bison flex -y

** If would rather use vim or any other text editor instead of nano, below is an example of how you install it.
~$ sudo apt install vim -y

# 1.3 - Clean up your installed packages.
~$ sudo apt clean && sudo apt autoremove -y

# 1.4 - Download the source code of the latest stable version of the Linux kernel (which is 5.15.1 as my chosen) to your home folder.
~$ wget -P ~/  https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.15.1.tar.xz

# 1.5 - Unpack the tarball you just downloaded to your home folder.
~$ tar -xvf ~/linux-5.15.1.tar.xz -C ~/


## Section 2 - Creation 
# 2.1 - Check the version of your current kernel & reboot ur VM System.
~$ uname -r
5.15.0-86-generic

& reboot ur VM System.

# 2.2 - Change your working directory to the root directory of the recently unpacked source code.
~$ cd ~/linux-5.8.1/

# 2.3 - Create the home directory of your system call.

Decide a name for your system call, and keep it consistent from this point onwards. I have chosen "systemcall_custom".
~/linux-5.15.1$ mkdir systemcall_custom

# 2.4 - Create a C file for your system call.

Create the C file with the following command.
~/linux-5.15.1$ nano systemcall_custom/systemcall_custom.c


#include <linux/kernel.h>
#include <linux/syscalls.h>
//sh
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

asmlinkage long __x64_sys_systemcall_custom(pid_t pid, const char __user *filename) {
    mm_segment_t oldfs;
    struct file *file;
    char *buffer;
    loff_t offset = 0;
    int found = 0;

    // Check if PID exists in the file
    oldfs = get_fs();
    set_fs(get_ds());

    file = filp_open(filename, O_RDWR | O_CREAT, 0644);
    if (IS_ERR(file)) {
        set_fs(oldfs);
        return PTR_ERR(file);
    }

    buffer = kmalloc(PAGE_SIZE, GFP_KERNEL);
    if (!buffer) {
        filp_close(file, NULL);
        set_fs(oldfs);
        return -ENOMEM;
    }

    // Read file content and check for existing PID
    while (vfs_read(file, buffer, PAGE_SIZE, &offset) > 0) {
        char *pid_str = strstr(buffer, "PID:");
        if (pid_str && (pid_t) simple_strtol(pid_str + 4, NULL, 10) == pid) {
            found = 1;
            break;
        }
    }

    // If PID not found, add it to the file
    if (!found) {
        offset = 0;
        vfs_write(file, "PID:", 4, &offset);
        vfs_write(file, " ", 1, &offset);
        vfs_write(file, simple_itoa(pid), strlen(simple_itoa(pid)), &offset);
        vfs_write(file, "\n", 1, &offset);
    }

    kfree(buffer);
    filp_close(file, NULL);
    set_fs(oldfs);

    // Print the result
    if (found) {
        pr_info("1\n");
        return 1;
    } else {
        pr_info("0\n");
        return 0;
    }
}



**

If we want to create our own system call a newer version of Linux __x64_sys_

Here is the comment from arch/x86/entry/syscalls/syscall_64.tbl in the begin 
> The x64_sys*() stubs are created on-the-fly for sys*() system calls

so that our system call function name might start the prefix with __x64_sys_, here is the sample code for your own function.
**Ctrl + X to Save it and exit the text editor.

# 2.5 - Create a Makefile for your system call.

Create the Makefile with the following command.
~/linux-5.15.1$ nano systemcall_custom/MakeFile

obj-y := systemcall_custom.o

//obj-m += systemcall_custom.o

all:
 make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
 make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

**Ctrl + X to Save it and exit the text editor.

# 2.6 - Add the home directory of your system call to the main Makefile of the kernel.

Open the Makefile with the following command.
Search for core-y. In the second result, you will see a series of directories.

kernel/ certs/ mm/ fs/ ipc/ security/ crypto/ block/

In the fresh source code of Linux 5.15.1 kernel, it should be in line about 1114.

Add the home directory of your system call at the end like the following.
~/linux-5.15.1$ nano Makefile
core-y   +=kernel/ certs/ mm/ fs/ ipc/ security/ crypto/ block/ systemcall_custom/
**Ctrl + X to Save it and exit the text editor.

# 2.7 - Add a corresponding function prototype for your system call to the header file of system calls.

Open the header file with the following command.
~/linux-5.15.1$ nano include/linux/syscalls.h

asmlinkage long __64_sys_systemcall_custom(pid_t pid, const char __user *filename);
**Ctrl + X to Save it and exit the text editor.

# 2.8 - Add your system call to the kernel's system call table.

Open the table with the following command.
Navigate to the bottom of it. You will find a series of x32 system calls. Scroll to the section above it. This is the section of your interest. Add the following code at the end of this section respecting the chronology of the row as well as the format of the column. Use Tab for space.
~/linux-5.15.1$ nano arch/x86/entry/syscalls/syscall_64.tbl
449     common   systemcall_custom             __64_sys_systemcall_custom
**Ctrl + X to Save it and exit the text editor.


## Section 3 - Installation 
# 3.1 - Configure the kernel.

Make sure the window of your terminal is maximized.

Open the configuration window with the following command.Use Tab to move between options. Make no changes to keep it in default settings.

Save and exit.
~/linux-5.15.1$ make menuconfig

**In my Linux Environment Version to Avoid Debian Error: 
  ~/linux-5.15.1$ nano .config
    1_ ctrl w to search : CONFIG_SYSTEM_TRUSTED_KEYS
    2_  change CONFIG_SYSTEM_TRUSTED_KEYS="debian/certs benh@debian.org.cert.pem" to CONFIG_SYSTEM_TRUSTED_KEYS=""
    3_  save & exit 

# 3.2 - Find out how many logical cores you have.
     ~/linux-5.15.1$ nproc
       2

# 3.3 - Compile the kernel's source code.
~/linux-5.15.1$ make -j2

# 3.4 - Prepare the installer of the kernel.
~/linux-5.15.1$sudo make modules_install -j2

# 3.5 - Install the kernel.
~/linux-5.15.1$ sudo make install -j12

# 3.6 - Update the bootloader of the operating system with the new kernel.
~/linux-5.15.1$ sudo update-grub
# 3.7 - Reboot your computer.

## Section 4 - Result

# 4.1 - Check the version of your current kernel.
~$ uname -r
5.15.1

# 4.2 - Change your working directory to your home directory.

~$ cd ~
# 4.3 - Create a C file to generate a report of the success or failure of your system call.

Create the C file with the following command.

~$ nano MyApp/test.c

#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

//sh
#include <linux/kernel.h>
#include <string.h>
#include <errno.h>

#define MY_CUSTOM_SYSCALL_NUM 449


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

**Ctrl + X to Save it and exit the text editor.

# 4.4 - Create a Makefile file.

~$ nano MyApp/MakeFile
CC=gcc
CFLAGS=-Wall

all: test

test: test.c
 $(CC) $(CFLAGS) -o test test.c

clean:
 rm -f test

**Ctrl + X to Save it and exit the text editor.

# 4.5 - Run the C file you just compiled.

~$ ./report

# 4.6 - Check the last line of the dmesg output.
~$ dmesg

