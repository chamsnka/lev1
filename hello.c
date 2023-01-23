//header files
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/sched.h>

static int hello_init(void)
{
 pr_info("inserting the module\n");
 printk("pid:%d name:%s\n",current->pid,current->comm);
 //printk("ppid:%d name:%s\n",current->pid_t,current->comm);
 printk(KERN_DEBUG "%s:%s:%d\n",__FILE__,__func__,__LINE__); 
	return 0;
}
static void hello_exit(void)
{
 printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);
 pr_info("module removed successfully");
}
//macros to init and exit 
module_init(hello_init);
module_exit(hello_exit);
//module auther
MODULE_AUTHOR("chandar");
MODULE_DESCRIPTION("EXAM HELLO World module");
MODULE_LICENSE("GPL");

