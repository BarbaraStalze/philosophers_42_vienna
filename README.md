*This project has been created as partC of the 42 curriculum by bastalze.*

# philosophers

## Description
### General description
There is an n amount of philosophers sitting around a table in a circle and there is an n amount of chopsticks on the table - one between each pair of philosophers. In order to eat each philosopher needs to hold two chopsicks.
They eat, then sleep, then think.
They have a fixed amount of time for eating, sleeping and until they die if they don't start eating or if this amount of time has passed since they last started eating.
They should avoid dying. In case a minimum amount of times eaten is passed as an argument they shouldn't die before all are done.
### Goal
The project tought me about threads, data races, timing of processes and mutexes.
### Detailed description
The first and last philosopher sit next to each other. Also the first sits next to the second the second next to the third and so on (if there are more than 3 of course).
The message of the death of a philosopher appears maximum 10 milliseconds after his actual death.
There is a separate thread for each philosopher and one for the observer.
Mutexes are used in order to avoid data races and mixed output messages.
In order to avoid a deadlock (each philosopher holding one chopstick and all starving) each oddly numbered philosopher takes first the chopsick to his left and then the one to his right. Each even philospher first takes the one to his right.

## Instructions
To run the program go to the root directory philosophers/ and there you run `make` and then ./philo with the arguments like discribed below.

### Arguments
This program takes 5 to 6 arguments:
1. Number of philosphers
2. Time to die in milliseconds - a philosopher dies if he hasn't started eating or within that time since the start of the program or since he last started eating
3. Time to eat in milliseconds - philosopher has to hold two chopsicks during that time
4. Time to sleep in milliseconds
5. Optionally: number of times each philosopher must eat - as soon as all philosophers have eaten at least this amount of time, the program stops
If the minimum number of how many time a philosopher must eat isn't specified the simulation stops as soon as one philosopher dies.

### Output
The program will write to the standard output:
Which timestamp (in milliseconds) which philosopher... 
- has taken a fork
- starts eating
- starts sleeping
- starts thinking
- has died

## Resources
### References
#### Manual pages:
- usleep
- gettimeofday
- pthread_create
- pthread_detach
- pthread_join
- pthread_mutex_destroy
- pthread_mutex_lock
- [gettimeofday on geeksforgeeks] (https://www.geeksforgeeks.org/c/measure-execution-time-with-high-precision-in-c-c/)
- [pthread functions on geeksforgeeks] (https://www.geeksforgeeks.org/c/thread-functions-in-c-c/)
- [Mutex lock for Linux Thread Synchronization] (https://www.geeksforgeeks.org/linux-unix/mutex-lock-for-linux-thread-synchronization/)
- [Usleep in Linux](https://linuxvox.com/blog/linux-usleep/)
- [Using gettimeofday for Computing Execution Time](https://devgex.com/en/article/00035289)


### Peers
I talked to Kian and Myron about their approaches. They told me that using a string with bools that shows if a fork is used would be counted as communication between philosophers which isn't allowed. Kian inspired my waiting_for_all. Felix inspired my way of not printing messages after someone died. Stefan inspred me in the way how he has a flexible amount of sleep depending on how far away from the time to change state is and his neat way of using defines for the messages.

### AI Usage Statement
- discussion of concepts and ideas
- 
