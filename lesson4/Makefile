SOURCES = linux_atomic_compare_and_swap.c  linux_atomic_sync.c  linux_non_atomic_volatile.c linux_atomic_pthread_mutex.c


all: $(SOURCES)
	g++ linux_atomic_compare_and_swap.c -o linux_atomic_compare_and_swap -pthread
	g++ linux_atomic_sync.c -o linux_atomic_sync -pthread
	g++ linux_non_atomic_volatile.c -o linux_non_atomic_volatile -pthread
	g++ linux_atomic_pthread_mutex.c -o linux_atomic_pthread_mutex -pthread

