#include "test.h"

void tst_pcb(){
	lista = new List();
	PCB *tst;
	ListItem *itm;
	int i;
	for(i = 0; i < 10; i++)
	{
		tst = new PCB();
		lista->add(tst);
	}
	for(i = 1; i < 3; i++)
	{
		tst = lista->get(i);
		tst->state = 2;
		lista->get(0)->waitingfor->add(tst);
	}
	for(i = 4; i < 6; i++)
	{
		tst = lista->get(i);
		tst->state = 2;
		lista->get(3)->waitingfor->add(tst);
	}
	for(i = 7; i < 9; i++)
	{
		tst = lista->get(i);
		tst->state = 2;
		lista->get(6)->waitingfor->add(tst);
	}
	for(i = 0; i < 10; i++)
	{
		tst = lista->get(i);
		cout<<"PCB "<<tst->id<<"---";
		itm = tst->waitingfor->head;
		while(itm)
		{
			cout<<itm->content->id<<"; ";
			itm = itm->next;
		}
		cout<<"\n";
	}
	tst = lista->get(0);
	while(tst->waitingfor->head != 0)
	{
		tst->waitingfor->head->content->state = 1;
		tst->waitingfor->remove(0);
	}
	for(i = 0; i < 10; i++)
	{
		tst = lista->get(i);
		cout<<"PCB "<<tst->id<<"---";
		itm = tst->waitingfor->head;
		while(itm)
		{
			cout<<itm->content->id<<"; ";
			itm = itm->next;
		}
		cout<<"\n";
	}
}
