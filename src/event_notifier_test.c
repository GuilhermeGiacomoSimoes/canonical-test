#include "event_notifier.h"
#include <stdbool.h> 
#include <stdio.h> 

#include "../test/test.h"

void func_test_0_handler(const Event *event, 
		const void* data, size_t length) 
{
	EXPECT_EQ(2, event->count, "the count should be 1");
}

void func_test_1_handler(const Event *event, 
		const void* data, size_t length) 
{
	EXPECT_EQ(2, event->count, "the count should be 1");
}

void func_test_2_handler(const Event *event, 
		const void* data, size_t length) 
{
	EXPECT_EQ(2, event->count, "the count should be 2");
}

void func_test_3_handler(const Event *event, 
		const void* data, size_t length) 
{
	EXPECT_EQ(2, event->count, "the count should be 2");
}

void func_test_4_handler(const Event *event, 
		const void* data, size_t length) 
{
	EXPECT_EQ(2, event->count, "the count should be 2");
}

void event_initialize_test() 
{	
	Event ev;
	event_initialize(&ev);
	EXPECT_EQ(ev.count, 0, "count should be 0");
}

void event_subscribe_test() 
{
	Event ev;
	event_initialize(&ev);

	const bool result_1 = event_subscribe(&ev, func_test_1_handler);
	const bool result_2 = event_subscribe(&ev, func_test_2_handler);
	const bool result_3 = event_subscribe(&ev, func_test_3_handler);

	EXPECT_TRUE(result_1, "result 1 should be true");
	EXPECT_TRUE(result_2, "result 2 should be true");
	EXPECT_TRUE(result_3, "result 3 should be true");
}

void event_notify_test()
{
	Event ev;
	event_initialize(&ev);

	event_subscribe(&ev, func_test_0_handler);
	event_subscribe(&ev, func_test_1_handler);
	event_notify(&ev, &ev, sizeof(ev));
}

void event_unsubscribe_test() 
{
	Event ev;
	event_initialize(&ev);

	event_subscribe(&ev, func_test_2_handler);
	const bool result = event_unsubscribe(&ev, func_test_2_handler);
	EXPECT_TRUE(result, "result of unsubscribe sould be true");
}

void event_notify_with_usubscribe() 
{
	Event ev;
	event_initialize(&ev);

	event_subscribe(&ev, func_test_2_handler);
	event_subscribe(&ev, func_test_3_handler);
	event_subscribe(&ev, func_test_4_handler);

	event_unsubscribe(&ev, func_test_4_handler);

	event_notify(&ev, &ev, sizeof(ev));
}

int main() 
{
	event_initialize_test();
	event_subscribe_test();
	event_notify_test();
	event_unsubscribe_test();
	event_notify_with_usubscribe();

	return 0;
}
