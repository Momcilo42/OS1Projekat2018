#include "IVTEntry.h"

IVTEntry* IVTEntry::IVTable[256] = {0};

IVTEntry::IVTEntry(IVTNo number, sIntr old)
{
	if(number < 256)
	{
		this->number = number;
		this->event = 0;
		IVTEntry::IVTable[number] = this;
		this->old = 0;
#ifndef BCC_BLOCK_IGNORE
		this->old = getvect(this->number);
		setvect(this->number, old);
#endif
	}
}

IVTEntry::~IVTEntry()
{
	delete[] IVTEntry::IVTable;
}

void IVTEntry::signal()
{
	if(this->event)this->event->signal();
}

void IVTEntry::callOld()
{
	if(this->old)
	{
#ifndef BCC_BLOCK_IGNORE
		setvect(this->number, this->old);
		this->old = 0;
#endif
	}

}

