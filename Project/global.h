#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "List.h"
#include "IVTEntry.h"

#define lock asm pushf; asm cli;
#define unlock asm popf;

class PCB;

extern unsigned oldTimerOFF, oldTimerSEG; // stara prekidna rutina
extern volatile unsigned counter, switchRequested;
extern List *lista;		//list svih threadova(pcbova)
extern List *sleeping;	//list spavajucih niti

void interrupt timer();
void tick();
void inic();
void restore();
void updateSleep();

#define PREPAREENTRY(numEntry, callOldx)\
void interrupt inter##numEntry(...); \
IVTEntry newEntry##numEntry(numEntry, inter##numEntry); \
void interrupt inter##numEntry(...) {\
	newEntry##numEntry.signal();\
	if (callOldx == 1)\
	newEntry##numEntry.callOld();\
}

#endif  GLOBAL_H_
