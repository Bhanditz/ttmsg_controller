#ifndef COMMON_IMPORTED
#define COMMON_IMPORTED

#include<stdint.h>

/* default, printf, etc */
#include<stdio.h>
/* gettimeofday() */
#include<sys/time.h>
/* time structs */
#include<time.h>
/* close() */
#include<unistd.h>

/* USER-DEFINED SETTINGS */
#define PORT 2468
#define SLAVE_IP "127.0.0.1"
#define NETMAP_INTERFACE "eth0"
#define NUM_OF_TIMES 2  /* num of times to run protocol */

#define FIXED_BUFFER 16
#define HELLO "Hello World!"

#ifndef likely /* For branch predictions */
    #define likely(x)   __builtin_expect(!!(x), 1)
    #define unlikely(x) __builtin_expect(!!(x), 0)
#endif

#define TO_NSEC(t) (((long)t[0] * 1000000000L) + t[1])

#define ERROR(err)						        \
	do {										\
		char msg[128];							\
		sprintf(msg, "[FILE:%s|FUNCTION:%s|LINE:%d] %s",	\
		  __FILE__, __FUNCTION__, __LINE__, err);  \
		perror(msg);						 	\
		printf("Exitting...\n");				\
        } while (0)

static void get_time(int in[2]) {
    if(in != NULL) {
        /* check for nanosecond resolution support */
        #ifndef CLOCK_REALTIME
            struct timeval tv = {0};
            gettimeofday(&tv, NULL);
            in[0] = (int) tv.tv_sec;
            in[1] = (int) tv.tv_usec * 1000;
        #else
            struct timespec ts = {0};
            clock_gettime(CLOCK_REALTIME, &ts);
            in[0] = (int) ts.tv_sec;
            in[1] = (int) ts.tv_nsec;
        #endif
    }
}

#define ALLOC(type, var) type* var = (type*)calloc(1, sizeof(type))
#define CVT(type, dest, src) type dest = (type)src

static uint64_t time_to_uint64(int in[2])
{
    uint64_t a = in[0];
    uint64_t b = in[1];
    return b + a * 1000000000ULL;
}
static void time_from_uint64(int out[2], uint64_t t)
{
    out[0] = t / 1000000000ULL;
    out[1] = t - ((uint64_t)out[0]) * 1000000000ULL;
}

static const unsigned long long TIME_SLOT_LEN_MS = 1000ULL;
#endif
