#include "global.h"
#include "PCB.h"

class BusyWait : public PCB
{
public:
	BusyWait() : PCB()
	{
		this->state = 2;
#ifndef BCC_BLOCK_IGNORE
		this->stack[stackSize - 5] = 0x200;						//PSWI enable
		this->stack[stackSize - 6] = FP_SEG(this->job);
		this->stack[stackSize - 7] = FP_OFF(this->job);
		this->ss = FP_SEG(stack + stackSize - 16);
		this->sp = FP_OFF(stack + stackSize - 16);
		this->bp = FP_OFF(stack + stackSize - 16);
#endif
	}
	static void job(){while(1);}
};

class Starting : public PCB
{
public:
	Starting() : PCB()
	{
#ifndef BCC_BLOCK_IGNORE
		this->stack[stackSize - 5] = 0x200;						//PSWI enable
		this->stack[stackSize - 6] = FP_SEG(this->jobby);
		this->stack[stackSize - 7] = FP_OFF(this->jobby);
		this->ss = FP_SEG(stack + stackSize - 16);
		this->sp = FP_OFF(stack + stackSize - 16);
		this->bp = FP_OFF(stack + stackSize - 16);
#endif
	}
	static void jobby(){}
};

unsigned oldTimerOFF, oldTimerSEG; 	// stara prekidna rutina
volatile unsigned tss, tsp, tbp;
volatile unsigned counter, switchRequested;
List *lista;						//lista svih threadova(pcbova)
List *sleeping;						//lista spavajucih niti
PCB *running;						//trenutno pokrenuta nit
BusyWait* busywait;						//nit za uposleno cekanje
PCB* starting;

void interrupt timer()
{
	if (!switchRequested && (counter>0))
	{
	updateSleep();
	counter--;
	}
	if ((counter == 0 && running->timeSlice != 0) || switchRequested)
	{
#ifndef BCC_BLOCK_IGNORE
		asm {
			mov tss, ss
			mov tsp, sp
			mov tbp, bp
		}
#endif
		running->ss = tss;
		running->sp = tsp;
		running->bp = tbp;
		if ((running->state == 1) && (running != busywait) && (running != starting))
			Scheduler::put(running);
		running = Scheduler::get();
		if (!running && !lista->head) running = starting;
		if (!running) running = busywait;
		tss = running->ss;
		tsp = running->sp;
		tbp = running->bp;
		counter = running->timeSlice;
#ifndef BCC_BLOCK_IGNORE
		asm {
			mov ss, tss
			mov sp, tsp
			mov bp, tbp
		}
#endif
	}
#ifndef BCC_BLOCK_IGNORE
	if(!switchRequested) asm int 0x60;
#endif
	switchRequested = 0;
}

void inic()
{
	counter = 10;
	switchRequested = 0;
	lista = new List();
	sleeping = new List();
	starting = new Starting();
	busywait = new BusyWait();
	running = starting;
#ifndef BCC_BLOCK_IGNORE
	asm{
		cli
		push es
		push ax

		mov ax,0   //  ; inicijalizuje rutinu za tajmer
		mov es,ax

		mov ax, word ptr es:0022h //; pamti staru rutinu
		mov word ptr oldTimerSEG, ax
		mov ax, word ptr es:0020h
		mov word ptr oldTimerOFF, ax

		mov word ptr es:0022h, seg timer	 //postavlja
		mov word ptr es:0020h, offset timer //novu rutinu

		mov ax, oldTimerSEG	 //	postavlja staru rutinu
		mov word ptr es:0182h, ax //; na int 60h
		mov ax, oldTimerOFF
		mov word ptr es:0180h, ax

		pop ax
		pop es
		sti
	}
#endif
}

void restore()
{
	dispatch();
	delete lista;
	delete sleeping;
	delete busywait;
#ifndef BCC_BLOCK_IGNORE
	asm {
		cli
		push es
		push ax

		mov ax,0
		mov es,ax


		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax

		pop ax
		pop es
		sti
	}
#endif
}

void updateSleep() {
	lock
	ListItem *itm = sleeping->head;
	int i = 0;
	while (itm)
	{
		if (itm == 0) break;
		itm->content->sleepTime--;
		if (itm->content->sleepTime == 0)
		{
			itm->content->state = 1;
			Scheduler::put(itm->content);
			sleeping->remove(i--);
		}
		itm = itm->next;
		i++;
	}
	unlock
}
