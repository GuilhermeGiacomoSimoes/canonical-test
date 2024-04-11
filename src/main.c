#include <stdio.h>

#include "event_notifier.h"

void fun_1(const Event *env, const void* data, size_t length) 
{
	printf("exec fun_1\n");
}

void fun_2(const Event *env, const void* data, size_t length) 
{
	printf("exec fun_2\n");
}

void fun_3(const Event *env, const void* data, size_t length) 
{
	printf("exec fun_3\n");
}

int main()
{
	Event *env = (Event*) malloc(sizeof(Event));
	event_initialize(env);

	printf("\nsubscribe fun_1, fun_2, fun_3\n");
	event_subscribe(env, fun_1);
	event_subscribe(env, fun_2);
	event_subscribe(env, fun_3);

	printf("\nsending notify\n");
	event_notify(env, env, 10);

	printf("\nunsubscribe fun_2\n");
	event_unsubscribe(env, fun_2);

	printf("\nsending notify\n");
	event_notify(env, env, 10);

	printf("\nunsubscribe fun_1\n");
	event_unsubscribe(env, fun_1);

	printf("\nsending notify\n");
	event_notify(env, env, 10);

	printf("\ndeinitialize\n");
	event_deinitialize(env);
	
	return 0;
}
