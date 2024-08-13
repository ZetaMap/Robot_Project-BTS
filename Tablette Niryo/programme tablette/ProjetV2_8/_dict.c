#include "hmiworks.h"

PVAR __var_table[1];
int table_init_flag = 0;

void hmi_var_table_init()
{
table_init_flag = 1;
}

int __var_count() { return 0; }

void passDataThruBindingOnChange()
{
}

