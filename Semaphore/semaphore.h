// This software may be used in your CECS326 programs

#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define PERMS S_IWUSR|S_IRUSR // 0600 constant, permission to access semaphore

/*
General Notes

wrapper, class,
only using
*/

// internal data structure, required by Linux for syscall
class mysembuf {
public:
	struct sembuf sb;
};

// internal data strcutre, required by Linux for syscall
// need to be checking for existing definition
// union semun { 		// truncated definition
// 	int val; 	// value used with SETVAL
// 	ushort *array; 	// array of values: GETALL and SETALL
// };

class SEMAPHORE {
private:
	int size;
	pid_t semid; // analogous to queue id, used internally
	mysembuf *pset, *vset;

	int init();
	void set_sembuf_p(int, int, int);
	void set_sembuf_v(int, int, int);
public:
	// put item, and take item
	// create a number of semaphores denoted by size
	// precondition: size is larger than zero
	// postcondition: all semaphores are initialized to zero
	SEMAPHORE(int size);
	~SEMAPHORE();

	// NOTE: must call explicitly,
	// deallocates all semaphores created by constructor
	// precondition: existence of SEMAPHORE object
	// postcondition: all semaphores are removed
	int remove();

	// semaphore P operation on semaphore semname
	// precondition: existence of SEMAPHORE object
	// postcondition: semaphore decrements and process may be blocked
	// return value: -1 denotes an error
	int P(int semname);

	// semaphore V operation on semaphore semname
	// precondition: existence of SEMAPHORE object
	// postcondition: semaphore increments and process may be resumed
	// return value: -1 denotes an error
	int V(int semname);
};
