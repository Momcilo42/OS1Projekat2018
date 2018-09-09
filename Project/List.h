#ifndef LIST_H_
#define LIST_H_

#include<iostream.h>

class PCB;

class ListItem
{
public:
	PCB *content;
	ListItem *previous, *next;
	ListItem(PCB *item = 0);
	~ListItem();
};

class List
{
public:
	ListItem *head, *tail; //tail poslednji zauzeti
	List();
	~List();
	void add(PCB *t);
	void remove(int i);
	PCB* get(int i);
};

#endif /* LIST_H_ */
