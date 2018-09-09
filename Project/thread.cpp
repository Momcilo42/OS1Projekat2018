#include "thread.h"
#include "global.h"
#include "PCB.h"

void Thread::start()
{
	lock
	if (this->myPCB->state != 1 && this->myPCB->state != 2 && this->myPCB->state != 3)
	{
		this->myPCB->state = 1;
		Scheduler::put(this->myPCB);
	}
	unlock
}

void Thread::waitToComplete()
{
	if((running != this->myPCB) && this->myPCB->state != 3)
	{
		running->state = 2;
		this->myPCB->waitingfor->add(running);
		dispatch();
	}
}

void Thread::sleep(Time timeToSleep)
{
	lock
	if(timeToSleep > 0)
	{
		running->sleepTime = timeToSleep;
		running->state = 2;
		sleeping->add(running);
	}
	unlock
	dispatch();
}

Thread::Thread(StackSize stackSize, Time timeSlice)
{
	lock
	this->myPCB = new PCB(stackSize, timeSlice, this);
	lista->add(this->myPCB);
	unlock
}

void dispatch()
{
	lock
	switchRequested = 1;
	timer();
	unlock
}

Thread::~Thread()
{
	delete this->myPCB;
}
