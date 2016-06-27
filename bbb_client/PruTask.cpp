#include "PruTask.h"

PruTask::PruTask(string binName)
{
	m_binName = binName;

	prussdrv_init();
	prussdrv_open(PRU_EVTOUT_0);
	
	// Map PRU0 Data RAM0 
	prussdrv_map_prumem(PRUSS0_PRU0_DATARAM, (void**)&m_pruDataRam0);	
	
	// Map PRU's interrupts 
	tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA; // Initialize structure used by prussdrv_pruintc_intc 
	prussdrv_pruintc_init(&pruss_intc_initdata);
}

PruTask::~PruTask()
{
	// Disable PRU and close memory mappings
	prussdrv_pru_disable(PRU_NUM);
	prussdrv_exit();
}


string 	PruTask::getBinName() 	{ return m_binName; }
