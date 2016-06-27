/*
* Simplifying Assumption: PruTask represents a PRU0 program (no PRU0 / PRU1 distinction  yet) 
*/

#ifndef PRU_TASK
#define PRU_TASK

#define PRU_NUM 0

#include <string>
#include <prussdrv.h>
#include <pruss_intc_mapping.h>

using namespace std;

class PruTask
{
	private:
	string m_binName;
	unsigned int* m_pruDataRam0;

   	public:
	PruTask(string);
	~PruTask();
	string getBinName();
};

#endif
