# philosophers
Solve the dining philosophers problem. (multi threading)

The following rules have to be respected:
• One or more philosophers sit at a round table.  
&emsp;There is a large bowl of spaghetti in the middle of the table.  
• The philosophers alternatively eat, sleep or think.  
&emsp;While they are eating, they are not thinking nor sleeping;
&emsp;while thinking, they are not eating nor sleeping;  
&emsp;and, of course, while sleeping, they are not eating nor thinking.  
• There are also forks on the table. There are as many forks as philosophers.  
• Because serving and eating spaghetti with only one fork is very inconvenient, a  
&emsp;philosopher takes their right and their left forks to eat, one in each hand.  
• When a philosopher has finished eating, they put their forks back on the table and  
&emsp;start sleeping. Once awake, they start thinking again. The simulation stops when  
&emsp;a philosopher dies of starvation.  
• Every philosopher needs to eat and should never starve.  
• Philosophers don’t speak with each other.  
• Philosophers don’t know if another philosopher is about to die.  
• No need to say that philosophers should avoid dying!  

• My program should take the following arguments:  
&emsp;number_of_philosophers   time_to_die   time_to_eat   time_to_sleep   [number_of_times_each_philosopher_must_eat]  
&emsp;◦ number_of_philosophers: The number of philosophers and also the number  
&ensp;&emsp;of forks.  
&emsp;◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die  
&ensp;&emsp;milliseconds since the beginning of their last meal or the beginning of the  
&ensp;&emsp;simulation, they die.  
&emsp;◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat.  
&ensp;&emsp;During that time, they will need to hold two forks.  
&emsp;◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.  
&emsp;◦ number_of_times_each_philosopher_must_eat (optional argument): If all  
&ensp;&emsp;philosophers have eaten at least number_of_times_each_philosopher_must_eat  
&ensp;&emsp;times, the simulation stops. If not specified, the simulation stops when a  
&ensp;&emsp;philosopher dies.  
• Each philosopher has a number ranging from 1 to number_of_philosophers.  
• Philosopher number 1 sits next to philosopher number number_of_philosophers.  
&emsp;Any other philosopher number N sits between philosopher number N - 1 and philoso-  
&emsp;pher number N + 1.  

This is an example with the following input"./philo 6 410 200 200 3  
![push_swap](https://github.com/cyberKev42/philosophers/blob/main/philosophers_cycle.png)
