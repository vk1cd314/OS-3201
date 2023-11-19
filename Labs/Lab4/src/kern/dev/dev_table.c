#include <dev_table.h>

dev_table device_list[64];
uint32_t device_count = 0;

void init_dev_table(void){
    //initialize device_list.tref = 0
    for (int i = 0; i < 64; i++){
        device_list[i].t_ref = 0;
    }

    //init device_list[device_count]
    __strcpy(device_list[device_count].name, "USART2");
    device_list[device_count].t_ref += 1;
    device_list[device_count].t_access = O_RDONLY;
    device_list[device_count].op_addr = USART2;
    device_count++;

    //init device_list[device_count] (usart2)
    __strcpy(device_list[device_count].name, "USART2");
    device_list[device_count].t_ref += 1;
    device_list[device_count].t_access = O_WRONLY;
    device_list[device_count].op_addr = USART2;
    device_count++;

    //init device_list[device_count] (stderr)
    __strcpy(device_list[device_count].name, "STDERR");
    device_list[device_count].t_ref += 1;
    device_list[device_count].t_access = O_WRONLY;
    device_list[device_count].op_addr = 0;
    device_count++;

}
void print_device_list(void){
	kprintf("\n\n______________________\n\n");
	for (int i = 0;i < device_count;i++){
		kprintf("device name = %s\n",device_list[i].name);
		kprintf("device t_ref = %d\n",device_list[i].t_ref);
		kprintf("device t_access = %d\n",device_list[i].t_access);
		kprintf("device op_addr = %x\n",device_list[i].op_addr);
		kprintf("\n");
	}
}