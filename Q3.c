#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/unistd.h>

MODULE_LICENCE("GPL");
MODULE_AUTHOR("leif");
MODULE_DESCRIPTION("Process reading K_module");
MODULE_VERSION("0.01");

int p=0;
module_param(p,int,0);

struct pid *struct_pid;
struct task_struct *t;

static int __init showprocess_init(void)
{
    struct_pid=find_get_pid(p);
    t=get_pid_task(struct_pid,PIDTYPE_PID);

    printk(KERN_INFO "PARENT: %s\n",t->parent->comm);
    printk(KERN_INFO "Current Task: %s\n",t->comm);
    printk(KERN_INFO "PID: %d\n",t->pid);
    printk(KERN_INFO "UID: %d\n",t->cred->uid.val);
    printk(KERN_INFO "PGUID: %d\n",t->group_leader->pid);
    printk(KERN_INFO "STATE: %s\n",t->state);

    return 0;
}

static void __exit showprocess_exit(void){
        printk(KERN_INFO "Goodbye Fellas\n");
}

module_init(showprocess_init);
module_exit(showprocess_exit)
