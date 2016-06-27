/*	 
* In-situ-Microscopy BeagleBone Black client 
*/

#include <unistd.h>
#include <iostream>
#include "PruTask.h"

#define PRU_NUM	0   // using PRU0 for these examples

int main (void)
{
   if(getuid()!=0){
      cout << "You must run this program as root. Exiting." << endl;
      exit(EXIT_FAILURE);
   }

//	PruTask* t = new PruTask("bla.bin");
//	cout << t->getBinName() << endl;

   // Initialize structure used by prussdrv_pruintc_intc
   // PRUSS_INTC_INITDATA is found in pruss_intc_mapping.h
   tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;

   // Allocate and initialize memory
   prussdrv_init ();
   prussdrv_open (PRU_EVTOUT_0);

   // Map PRU0 Data RAM0
   unsigned int* pruDataMem;
   prussdrv_map_prumem(PRUSS0_PRU0_DATARAM, (void**)&pruDataMem);

   // Pulse delay
   // Write a byte into PRU0 Data RAM0. Offset = 0 Bytes, Data Bytes = 4
   unsigned int pulsedelay = 0x000186A0;//0x00000032; // 50 (dec) => 500ns
   pruDataMem[0] = pulsedelay;

   // Pause delay
   // Write a byte into PRU0 Data RAM0. Offset = 4 Bytes, Data Bytes = 4
   unsigned int pausedelay = 0x05F5E100;//0x000003E8; // 1000 (dec) => 10us
   pruDataMem[1] = pausedelay;

   // Map PRU's interrupts
   prussdrv_pruintc_init(&pruss_intc_initdata);

   // Load and execute the PRU program on the PRU
   prussdrv_exec_program (PRU_NUM, "./pulse.bin");

   // Wait for event completion from PRU, returns the PRU_EVTOUT_0 number
   int n = prussdrv_pru_wait_event (PRU_EVTOUT_0);
   cout << "EBB PRU program completed, event number " << n << endl;

   // Disable PRU and close memory mappings
   prussdrv_pru_disable(PRU_NUM);
   prussdrv_exit ();
   return EXIT_SUCCESS;
}
