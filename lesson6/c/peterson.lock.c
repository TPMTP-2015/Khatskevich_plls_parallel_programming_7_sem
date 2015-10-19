char flag[2] = {0, 0};
int victim;

void lock() {
	int i,j;
	i = omp_get_thread_num();
	j = 1 - i;
	flag[i] = 1;
	__sync_synchronize();
	victim = i;
	while (flag[j] && victim == i) { }
}

void unlock() {
	flag[omp_get_thread_num()] = 0;
}