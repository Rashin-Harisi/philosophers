*This project has been created as part of the 42 curriculum by rabdolho.*

## Description

**Philosophers**, also known as *The Dining Philosophers Problem*, is a classic problem in computer science used to illustrate common issues in concurrent programming.

The problem was originally formulated in 1965 by **Edsger Dijkstra**, and is described as follows:

*X philosophers sit at a round table with bowls of food.
There is one fork between each pair of philosophers.
Each philosopher alternates between eating, sleeping, and thinking.
To eat, a philosopher must hold both the left and right forks.
A fork can only be used by one philosopher at a time.*

---

## Goal of the Project

The goal of this project is to introduce **multithreading** using the `pthread` library.

The following functions are used:

- **pthread_create()** – creates a new thread
- **pthread_join()** – waits for a thread to finish
- **pthread_mutex_init()** – initializes a mutex
- **pthread_mutex_destroy()** – destroys a mutex
- **pthread_mutex_lock()** – locks a mutex
- **pthread_mutex_unlock()** – unlocks a mutex

---

## Concurrency Issues

### Race Conditions

Forks and standard output (`stdout`) are **shared resources**, accessed by multiple threads.  
To prevent inconsistent behavior, mutexes are used to protect these resources.

---

### Deadlock

A deadlock occurs when all philosophers pick up one fork and wait indefinitely for the second one.

To prevent this, the program breaks the circular wait condition by changing the fork acquisition order.  
In this implementation, the last philosopher picks up the forks in the opposite order.

---
## Instruction

### Usage
#### Compilation

```bash
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
** The last argument is optional. And all time values are in milliseconds.

## Resources
* <a href="https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2"> The Dining Philosophers Problem - Medium</a>
* <a href="https://en.wikipedia.org/wiki/Dining_philosophers_problem"> The Dining Philosophers Problem - Wikipedia </a>
* <a href="https://chatgpt.com/"> ChatGpt </a> : Undrestanding the concept of the project / Play role of a tutor.
* <a href="https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2" target="_blank"> Unix Threads in C </a>
* <a href="https://www.youtube.com/watch?v=LOfGJcVnvAk" target="_blank"> Introduction to Threads </a>
