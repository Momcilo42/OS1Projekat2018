#ifndef _PCB_H_
#define _PCB_H_

#include <iostream.h>
#include <dos.h>
#include "thread.h"
#include "List.h"
#include "SCHEDULE.H"
#include "global.h"
#include "kernelsm.h"
#include "kernelev.h"

class PCB
{
public:
	unsigned *stack;
	unsigned long stackSize, timeSlice;
	unsigned id;
	static unsigned lastid;
	unsigned sp, ss, bp;
	unsigned sleepTime;
	int state; // 1=ready; 2=blocked; 3=complete;
	Thread *myThread;	//okruzujuci thread
	KernelSem *blockedOn;
	List *waitingfor;

	PCB(StackSize stackSize = 4096, Time timeSlice = 2, Thread* thisThread = 0);
	~PCB();
	static void wrapper();
};

extern PCB* running;

#endif
