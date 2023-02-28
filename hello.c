
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CHANDAR");
MODULE_DESCRIPTION("hello world kernel module");

static int __init hello_init(void)
{
	struct task_struct *task, *parent_task;
	task = current;
	parent_task = task->parent;

	printk(KERN_INFO "HELLO,WORLD!");
	printk(KERN_INFO, "Current process name = %s and pid is %d\n", task->comm, task->pid);
	printk(KERN_INFO, "Parent process name = %s and pid is %d\n", parent_task->comm, parent_task->pid);

	while(task->pid != 0)
	{
		task = task -> parent;
		printk(KERN_INFO "Process in tree: name= %s, pid= %d\n", task->comm, task->pid);
	}

	return 0;
}


static void __exit hello_exit(void)
{
	printk(KERN_INFO "Goodbye, world!\n");
}
module_init(hello_init);
module_exit(hello_exit);
