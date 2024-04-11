CC ?= clang

all: run

run: ex.o 
	./ex.o

ex.o: src/event_notifier.c src/main.c 
	$(CC) src/event_notifier.c src/main.c -o ex.o

test: source_test.o
	./source_test.o

source_test.o: test/test.c src/event_notifier.c src/event_notifier_test.c
	$(CC) test/test.c src/event_notifier.c src/event_notifier_test.c -o source_test.o

clean:
	find . -name "*.o" -exec rm -rf {} +

help:
	@echo "-- HELP --"
	@echo
	@echo "To compile a example work: make"
	@echo
	@echo "To execute a unit tests: make test"
	@echo
