#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/sched/signal.h>

static int my_proc_show(struct seq_file *m,void *v){
	seq_printf(m, "Carne: 201603014\n");
    seq_printf(m, "Nombre: Sebastian Sanchez Tuchez\n");
	seq_printf(m, "SO: Fedora Workstation\n\n\n");
    seq_printf(m, "[PID]\t\tCOMANDO\t\tESTADO\n");
    struct task_struct *task;
    for_each_process(task) {
        seq_printf(m, "[%d]\t\t%s\t\t%li \n", task->pid, task->comm, task->state);
    }
	return 0;
}

static ssize_t my_proc_write(struct file* file,const char __user *buffer,size_t count,loff_t *f_pos){

}

static int my_proc_open(struct inode *inode,struct file *file){
	return single_open(file,my_proc_show,NULL);
}

static struct file_operations my_fops={
	.owner = THIS_MODULE,
	.open = my_proc_open,
	.release = single_release,
	.read = seq_read,
	.llseek = seq_lseek,
	.write = my_proc_write
};

static int __init cpumod_init(void){
	struct proc_dir_entry *entry;
	entry = proc_create("cpu_201603014", 0777, NULL, &my_fops);
	if(!entry){
		return -1;	
	}else{
		printk(KERN_INFO "Sebastian Sanchez Tuchez\n");
	}
	return 0;
}

static void __exit cpumod_exit(void){
	remove_proc_entry("cpu_201603014", NULL);
	printk(KERN_INFO "Sistemas Operativos 1\n");
}

module_init(cpumod_init);
module_exit(cpumod_exit);
MODULE_LICENSE("GPL");
