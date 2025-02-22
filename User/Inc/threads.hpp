#ifndef THREADS_HPP_
#define THREADS_HPP_

#include "user.hpp"

void ThreadsStart();

/* Defines */

/* Periodic threads */
void Heartbeat(void);

/* Regular threads */
void SendTelemetry(void);

/* Timers */
extern osTimerId_t heartbeat_timer;

/* Event flags */

/* Mutexes */
extern osMutexId_t can_frames_mutex;

/* Callbacks */
// CAN frame received callback/s


/* Object Declarations */

#endif  /* THREADS_HPP_ */
