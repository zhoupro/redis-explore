#include <fcntl.h>
#include <time.h>
#include "atomicvar.h"
#include <unistd.h>
#define LOG_MAX_LEN    1024 /* Default maximum length of syslog messages.*/

typedef long long ustime_t; /* microsecond time type. */
typedef long long mstime_t; /* millisecond time type. */

long long ustime(void);


/* Log levels */
#define LL_DEBUG 0
#define LL_VERBOSE 1
#define LL_NOTICE 2
#define LL_WARNING 3
#define LL_RAW (1<<10) /* Modifier to log without timestamp */


/* Use macro for checking log level to avoid evaluating arguments in cases log
 * should be ignored due to low level. */
#define serverLog(level, ...) do {\
        if (((level)&0xff) < server.verbosity) break;\
        _serverLog(level, __VA_ARGS__);\
    } while(0)


#ifdef __GNUC__
void _serverLog(int level, const char *fmt, ...)
    __attribute__((format(printf, 2, 3)));
#else
void _serverLog(int level, const char *fmt, ...);
#endif
void serverLogRaw(int level, const char *msg);


struct redisServer {
    pid_t pid;                  /* Main process pid. */
    char *masterhost;               /* Hostname of master */
    int sentinel_mode;          /* True if this instance is a Sentinel. */

    char *logfile;                  /* Path of log file */
    int syslog_enabled;             /* Is syslog enabled? */
    int verbosity;                  /* Loglevel in redis.conf */

    time_t timezone;            /* Cached timezone. As set by tzset(). */
    int daylight_active;        /* Currently in daylight saving time. */
    mstime_t mstime;            /* 'unixtime' in milliseconds. */
    ustime_t ustime;            /* 'unixtime' in microseconds. */
    redisAtomic time_t unixtime; /* Unix time sampled every cron cycle. */
};
