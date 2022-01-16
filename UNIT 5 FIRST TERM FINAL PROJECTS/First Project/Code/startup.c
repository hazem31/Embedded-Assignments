
#include "stdint.h"

extern int main();

extern unsigned int _E_text ;
extern unsigned int _S_DATA ;
extern unsigned int _E_DATA ;
extern unsigned int _S_bss ;
extern unsigned int _E_bss ;
extern unsigned int _stack_top;

void Reset_Handler() {
    unsigned int Data_size = (unsigned char *)&_E_DATA - (unsigned char *) &_S_DATA;
    unsigned char * P_src = (unsigned char *)&_E_text;
    unsigned char * P_des = (unsigned char *)&_S_DATA;
    for (int i = 0; i < Data_size; i++)
    {
        *P_des = *P_src;
        P_src++;
        P_des++;
    }
    unsigned int bss_size = (unsigned char *)&_E_bss - (unsigned char *) &_S_bss;
    
    P_des = (unsigned char *)&_S_bss;
    
    for (int i = 0; i < bss_size; i++)
    {
        *P_des = 0;
        P_des++;
    }

    main();
}

void NMI_Handler() {
	Reset_Handler();
}

void H_Handler() {
	Reset_Handler();
}

void MM_Fault_Handler() {
	Reset_Handler();
}

void Bus_Fault() {
	Reset_Handler();
}

void Usage_Fault_Handler() {
	Reset_Handler();
}

uint32_t vectors[] __attribute__((section(".vectors"))) = {
    (uint32_t) &_stack_top,
	(uint32_t) &Reset_Handler,
	(uint32_t) &NMI_Handler,
	(uint32_t) &H_Handler,
	(uint32_t) &MM_Fault_Handler,
	(uint32_t) &Bus_Fault,
	(uint32_t) &Usage_Fault_Handler,
};