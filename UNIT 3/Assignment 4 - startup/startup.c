
#include <stdint.h>
void Reset_Handler();

extern int main();

void Default_Handler() {
	Reset_Handler();
}

void NMI_Handler() __attribute__((weak, alias("Default_Handler")));
void H_Handler() __attribute__((weak, alias("Default_Handler")));


static unsigned long Stack_top[256];


void (* const g_p_fn_Vectros[])() __attribute__((section(".vectors"))) = {
	
	(void (*)()) ((unsigned long)Stack_top + sizeof(Stack_top)),
	&Reset_Handler,
	&NMI_Handler,
	&H_Handler
};


extern unsigned int _E_text ;
extern unsigned int _S_DATA ;
extern unsigned int _E_DATA ;
extern unsigned int _S_bss ;
extern unsigned int _E_bss ;


void Reset_Handler() {
	unsigned int Data_size = (unsigned char *)&_E_DATA - (unsigned char *)&_S_DATA;
	unsigned char * P_src = (unsigned char *)&_E_text;
	unsigned char * P_dst = (unsigned char *)&_S_DATA;
	for (int i = 0; i < Data_size; ++i)
	{
		*((unsigned char *)P_dst++) = *((unsigned char *)P_src++);
	}

	unsigned int bss_size = (unsigned char *)&_E_bss  - (unsigned char *)&_S_bss;
	P_dst = (unsigned char *)&_S_bss;
	for (int i = 0; i < bss_size; ++i)
	 {
	 	*((unsigned char *)P_dst++) = (unsigned char)0;
	 } 
	main();
}


