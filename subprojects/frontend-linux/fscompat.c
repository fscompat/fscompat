#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("fscompat Developers");
MODULE_DESCRIPTION("The fscompat project");
MODULE_VERSION("0.0.1");

static int __init fc_init() {
    return 0;
}

static void __exit fc_exit() {
    return;
}

module_init(fc_init);
module_exit(fc_exit);
