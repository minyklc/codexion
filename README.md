*This project has been created as part of the 42 curriculum by msuizu*

## **--- Description ---**

codexion is a C project that orchestrates multiple coders competing each other
for limited USB dongles using POSIX threads, mutexes, and
smart scheduling, the aim is to master resource synchronization before burnout strikes…

## **--- Instructions ---**

`norminette`

`make`

`./codexion 200 10000 60 60 60 3 0 fifo` (should work)

`./codexion 2 70 20 20 20 3 10 edf` (should burn out)

`./codexion 2 1000 20 20 20 3 100 fifo` (should run without coder compiling)

`./codexion 0 1000000 20 20 20 3 10 edf` (should display error message)

`make fclean`

## **--- Resources ---**

[thread & mutex](https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/)

[multithreading](https://www.geeksforgeeks.org/c/multithreading-in-c/)

[cond variable](https://circuitlabs.net/pthreads-condition-variables-for-signaling-between-threads/#google_vignette)

## **--- Blocking cases handled ---**

deadlock prevention: even and odd coder take respectivly right or left dongle in first
starvation prevention: with scheduler fifo / edf
cooldown handling: used usleep function
precise burnout detection: a thread monitor that loops on thread every 1ms
log serialization: used a log mutex when needed

## **--- Thread synchronization mechanisms ---**

a stack of coders is created, with inside a pointer to the starting args, general mutex for log and time,
and right and left pointers which stand for the dongles next to the coder. each dongle owns a mutex and
a conditional variable and the queue that represents coders waiting for the dongle. the monitor has access
to all coders, while coders can't access to another coder's state.
