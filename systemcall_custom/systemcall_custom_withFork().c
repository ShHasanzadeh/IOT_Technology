#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

asmlinkage long __64_sys_systemcall_custom(pid_t pid, const char __user *filename) {
    mm_segment_t oldfs;
    struct file *file;
    char *buffer;
    loff_t offset = 0;
    int found = 0;

    // Check if PID exists in the file
    oldfs = get_fs();
    set_fs(get_ds());

    // Fork a new process
    if (fork() == 0) {
        // Child process
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
            pr_info("Child Process: 1\n");
            return 1;
        } else {
            pr_info("Child Process: 0\n");
            return 0;
        }
    } else {
        // Parent process
        pr_info("Parent Process\n");
        return 0;
    }
}