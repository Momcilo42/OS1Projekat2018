#include "List.h"

ListItem::ListItem(PCB* item)
{
	this->content = item;
	this->previous = 0;
	this->next = 0;
}

ListItem::~ListItem()
{
}

List::List()
{
	this->head = 0;
	this->tail = 0;
}

List::~List()
{
	while(this->head != 0)
	{
		ListItem *itm = this->head;
		this->head = this->head->next;
		delete itm;
	}
}

void List::add(PCB* t)
{
	ListItem *l = new ListItem(t);
	if(this->tail == 0)
	{
		this->head = l;
		this->tail = this->head;
	}
	else
	{
		this->tail->next = l;
		l->previous = this->tail;
		this->tail = this->tail->next;
	}
}

void List::remove(int i)
{
	ListItem *current, *pre, *post;
	current = this->head;
	if(current == 0) return;		//prazna lista
	while(i-- && current->next)current = current->next;
	if(current == 0) return;		//nenadjeno u listi
	pre = current->previous;
	post = current->next;
	if(current == this->head)this->head = this->head->next;
	if(current == this->tail)this->tail = this->tail->previous;
	if(pre != 0)pre->next = post;
	if(post != 0)post->previous = pre;
	delete current;
}

PCB* List::get(int i)
{
	ListItem *current = this->head;
	while(i-- && (current->next != 0)) current = current->next;
	return current->content;
}
