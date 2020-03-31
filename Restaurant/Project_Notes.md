# Data Structures to be used

* 6 Linked Lists for Cooks , Vegan - VIP- Normal / Free - Busy

* There will be output for every time stamp , if there's more than one order finished at the same timestep , they will be sent to a priority queue 
and be printed by ascending order based on ST (They all have the same FT) and then get started

* Order Queues =  VIP - Priority Queue | Normal and Vegan - Normal Queues

# Project Notes

* All Cooks of the same type have the same cooking speed and same break duration

* Every timestep , you'll loop over busy cooks  and for each cook , you'll check whether the cook has finished the order or not
* if 
1. Finished : check if he has a break or on a break
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1. if free - Return cook to free cook list
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2. if on break - change status to break and keep him in busy linked

2. Not finished : increment the time taken for the cook to finish 
  
   After checking if they finished or not Assign new orders.






