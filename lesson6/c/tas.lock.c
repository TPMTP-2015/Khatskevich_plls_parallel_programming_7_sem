volatile char _lock_byte;

inline char TAS(char v) { return __sync_lock_test_and_set(&_lock_byte, v); } 
inline void SET(char v) { _lock_byte = v; }

void lock() {
	while(TAS(1)) { }
}

void unlock() {
	SET(0);
}