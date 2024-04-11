#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "event_notifier.h"

typedef void (*fff)(const void*, const void*, size_t);

void event_initialize(Event* event)
{
	event->list = NULL;
	event->count = 0;
}

void event_deinitialize(Event* event)
{
	struct __list *ult = event->list;
	if(ult != NULL) {
		while(ult->next != NULL) {
			ult = ult->next;
		}

		struct __list *prev = ult->previous;
		while(prev != NULL) {
			prev = ult->previous;
			free(ult);
			ult = prev;
		}
	}

	free(event);
}

bool event_subscribe(Event* event, 
		void (*handler)(const Event *, const void*, size_t))
{
	if(event->list == NULL) {
		struct __list *n = (struct __list*)malloc(sizeof(struct __list));
    	n->previous = NULL;
    	n->next = NULL;
    	n->handler = (fff) handler;
		event->list = n;
		event->count ++;

		return true;
	}

	struct __list *ult = event->list;
	while(ult->next != NULL) {
		ult = ult->next;
	}

	struct __list *n = (struct __list*)
		malloc(sizeof(struct __list));

    if (n == NULL) {
        return false;
    }

    n->previous = ult;
    n->next = NULL;
    n->handler = (fff) handler;

    ult->next = n;
 	event->count ++;

    return true;
}

void __unsubscribe(Event *ev, struct __list *l) {
	struct __list *prev = l->previous;
	struct __list *next = l->next;

	if(ev->count == 1) {
		event_initialize(ev);
	}
	else if(prev == NULL) {
		next->previous = NULL;
		ev->list = next;
	}
	else if(next == NULL) {
		prev->next = NULL;
	}
	else {
		prev->next = next;
		next->previous = prev;
	}

	free(l);
	if(ev->count)
		ev->count --;
}

bool event_unsubscribe(Event* event, 
		void (*handler)(const Event *, const void*, size_t))
{
	struct __list *ult = event->list;
	do {
		if(ult->handler == (fff) handler) {
			struct __list *find = ult;
			__unsubscribe(event, find);
			return true;
		}

		ult = ult->next;
	} while(ult != NULL);

    return false;
}

void event_notify(Event* event, const void* data, size_t length)
{
	struct __list *ult = event->list;
	while(ult != NULL) {
		if(ult->handler != NULL) {
			fff hh = ult->handler;
			hh(event, data, length);
		}

		ult = ult->next;
	}
}

