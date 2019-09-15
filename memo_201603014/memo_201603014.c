#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/sysinfo.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/swap.h>

static int my_proc_show(struct seq_file *m, void *v){
    struct sysinfo i;
    si_meminfo(&i);
    long available;
    available = si_mem_available();
    //double porcentaje = (available * 1.0) / (i.totalram * 1.00) * 100.0; 
	seq_printf(m, "Carne: 201603014\n");
    seq_printf(m, "Nombre: Sebastian Sanchez\n");
    seq_printf(m, "SO: Fedora Workstation\n");
    seq_printf(m, "Memoria Total:\t\t%lu KB\n", i.totalram * 4);
    seq_printf(m, "Memoria Disponible:\t%lu KB\n", available * 4);
    seq_printf(m, "Memoria Libre:\t\t%lu KB\n", i.freeram * 4);
    //seq_printf(m, "Porcentaje:\t\t%.f2", porcentaje); 
	return 0;
}

static ssize_t my_proc_write(struct file* file,const char __user *buffer,size_t count,loff_t *f_pos){
    return 0;
}

static int my_proc_open(struct inode *inode,struct file *file){
	return single_open(file, my_proc_show, NULL);
}

static struct file_operations my_fops={
	.owner = THIS_MODULE,
	.open = my_proc_open,
	.release = single_release,
	.read = seq_read,
	.llseek = seq_lseek,
	.write = my_proc_write
};

static int __init memo_init(void){
	struct proc_dir_entry *entry;
	entry = proc_create("memo_201603014",0777,NULL,&my_fops);
	if(!entry){
		return -1;	
	}else{
		printk(KERN_INFO "201603014\n");
	}
	return 0;
}

static void __exit memo_exit(void){
	remove_proc_entry("memo_201603014",NULL);
	printk(KERN_INFO "Sistemas Operativos 1\n");
}



module_init(memo_init);
module_exit(memo_exit);
MODULE_LICENSE("GPL");
