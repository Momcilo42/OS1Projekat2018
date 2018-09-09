#include "PCB.h"

#define lock asm pushf;asm cli;
#define unlock asm popf;

unsigned PCB::lastid = 1;

PCB::~PCB()
{
	delete this->stack;
	delete this->waitingfor;
}

PCB::PCB(StackSize stacks, Time times, Thread* threads)
{
	this->id = lastid++;
	this->state = 0;
	this->sleepTime = 0;
	this->waitingfor = new List();
	this->stackSize = stacks/sizeof(unsigned);
	this->timeSlice = times;
	this->myThread = threads;
	this->blockedOn = 0;
	this->stack = new unsigned[stackSize];

	this->ss = 0;
	this->sp = 0;
	this->bp = 0;

#ifndef BCC_BLOCK_IGNORE
	this->stack[stackSize - 1] = FP_SEG(this->myThread);
	this->stack[stackSize - 2] = FP_OFF(this->myThread);
	this->stack[stackSize - 5] = 0x200;						//PSWI enable
	this->stack[stackSize - 6] = FP_SEG(PCB::wrapper);
	this->stack[stackSize - 7] = FP_OFF(PCB::wrapper);
	this->ss = FP_SEG(stack + stackSize - 16);
	this->sp = FP_OFF(stack + stackSize - 16);
	this->bp = FP_OFF(stack + stackSize - 16);
#endif
}

void PCB::wrapper()
{
	running->myThread->run();
	while(running->waitingfor->head != 0)
	{
		running->waitingfor->head->content->state = 1;
		Scheduler::put(running->waitingfor->head->content);
		running->waitingfor->remove(0);
	}
	running->state = 3;
	ListItem *itm;
	itm = lista->head;
	int i = 0;
	while(itm)
	{
		if(itm->content->id == running->id)break;
		itm = itm->next;
		i++;
	}
	if(itm)lista->remove(i);
	dispatch();
}
