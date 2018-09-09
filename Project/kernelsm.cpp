#include "kernelsm.h"

KernelSem::KernelSem(int init)
{
	lock
	this->value = init;
	this->blocked = new List();
	unlock
}

KernelSem::~KernelSem()
{
	lock
	delete this->blocked;
	unlock
}

int KernelSem::wait(int toBlock)
{
	lock
	if(!toBlock && (this->value <= 0))
	{
		unlock
		return -1;
	}
	if(--this->value < 0)
	{
		running->state = 2;
		running->blockedOn = this;
		this->blocked->add(running);
		unlock
		dispatch();
		return 1;
	}
	unlock
	return 0;
}

void KernelSem::signal() {
	lock
	if(++this->value <= 0){
		PCB *t = this->blocked->get(0);
		this->blocked->remove(0);
		t->state = 1;
		t->blockedOn = 0;
		Scheduler::put(t);
	}
	unlock
}
