//FAYAZ KHAN
#include "hw6.h"
#include <stdio.h>
#include<pthread.h>
#include <sched.h>

int isFloorEmpty(int at_floor, int elevator);

/*Taken from main.c*/
static struct lift
{
    int current_floor;
    int direction;
    int occupancy;
    int pass_id;
    pthread_mutex_t lock;
    pthread_cond_t cond;
    enum {ELEVATOR_ARRIVED=1, ELEVATOR_OPEN=2, ELEVATOR_CLOSED=3} state;
} elevators[ELEVATORS];

/*Taken from main.c*/
static struct lift_pass {
    int id;
    int elevNumb;
    int to_floor;
    int from_floor;
    enum {WAITING, ENTERED, EXITED} state;
    
} passengers[PASSENGERS];

pthread_barrier_t passenger_init_barrier;

int pass_bool = 0;

/*DONE*/
void scheduler_init() {
    
    
    /*Took Prof code and threw it in a while loop */
    int i = 0;
    while(i < ELEVATORS) //initialize each elev
    {
        elevators[i].current_floor=0;
        elevators[i].direction=-1;
        elevators[i].occupancy=0;
        elevators[i].state=ELEVATOR_ARRIVED;
        pthread_mutex_init(&elevators[i].lock,0);
        pthread_cond_init(&elevators[i].cond,0);
        i++;
    }
    
    /*Assign pass to elev*/
    i = 0;
    while(i < PASSENGERS)
    {
        //ELEVATORS == 4
        passengers[i].elevNumb = i % ELEVATORS;
        i++;
    }
    
    pthread_barrier_init(&passenger_init_barrier, NULL, PASSENGERS);
}



void passenger_request(int passenger, int from_floor, int to_floor,
                       void (*enter)(int, int),
                       void(*exit)(int, int))
{
    
    int elevator = passengers[passenger].elevNumb;
    
    //give the passenger some values coming in from outside the function
    passengers[passenger].id = passenger;
    passengers[passenger].from_floor = from_floor;
    passengers[passenger].to_floor = to_floor;
    passengers[passenger].state = WAITING;
    
    int pbw = pthread_barrier_wait(&passenger_init_barrier);
    
    if (pbw == PTHREAD_BARRIER_SERIAL_THREAD)
        pass_bool = 1;
    
    /*Below is Prof. code but using the elevator array*/
    // wait for the elevator to arrive at our origin floor, then get in
    int waiting = 1;
    // this loops is for trying to get into the elevator
    while(waiting) {
        pthread_mutex_lock(&elevators[elevator].lock);// orginally pthread_mutex_lock(&lock);
        
        //Essentially, continued changing code to accomadate the array
        if(elevators[elevator].current_floor == from_floor && elevators[elevator].state == ELEVATOR_OPEN && elevators[elevator].occupancy==0)
        {
            enter(passenger, elevator);
            elevators[elevator].pass_id = passenger;
            elevators[elevator].occupancy++;
            waiting=0;
            
            //Change state to entered
            passengers[passenger].state = ENTERED;
            
            pthread_cond_signal(&elevators[elevator].cond);   //added this
        }
        
        sched_yield(); //found in main.c
        pthread_mutex_unlock(&elevators[elevator].lock); //originally:: pthread_mutex_unlock(&lock);
    }
    
    
    /*Repeat the modification done above; do it to the below portion of the code*/
    
    // wait for the elevator at our destination floor, then get out
    int riding=1;
    
    //This loop is for getting out of the elevator but it keeps on trying over and over again
    while(riding) {
        pthread_mutex_lock(&elevators[elevator].lock);
        
        if(elevators[elevator].current_floor == to_floor && elevators[elevator].state == ELEVATOR_OPEN) {
            exit(passenger, elevator); //before elevator was 0, now specify elevator
            elevators[elevator].occupancy--;
            riding=0;
            
            //----------
            elevators[elevator].pass_id = -1;  //Added to this to show empty
            passengers[passenger].state = EXITED;
            pthread_cond_signal(&elevators[elevator].cond);
            //------------
        }
        
        pthread_mutex_unlock(&elevators[elevator].lock);
    }
}

void elevator_ready(int elevator, int at_floor,
                    void(*move_direction)(int, int),
                    void(*door_open)(int), void(*door_close)(int)){
    
       
    pthread_mutex_lock(&elevators[elevator].lock); //orignally pthread_mutex_lock(&lock);
    
    /*The conditionals are pretty much by the Prof, just need to modify for  the elev and pass struct array
     and add extra conditionals*/
    if(elevators[elevator].state == ELEVATOR_ARRIVED)
    {
        int boolExit = 0;
        if (elevators[elevator].occupancy > 0)
        {
            
            int passenger = elevators[elevator].pass_id;
            if (passenger != -1)
                boolExit = passengers[passenger].to_floor == elevators[elevator].current_floor;
            
        }
        
        
        if (boolExit || (elevators[elevator].occupancy == 0 && isFloorEmpty(at_floor, elevator) == 0))
        {
            door_open(elevator);
            elevators[elevator].state = ELEVATOR_OPEN;
            pthread_cond_wait(&elevators[elevator].cond, &elevators[elevator].lock);
        }
        else
            elevators[elevator].state=ELEVATOR_CLOSED;
        
        
    }/*Below portion remained almost the same except accounting for arrays */
    else if(elevators[elevator].state == ELEVATOR_OPEN)
    {
        door_close(elevator);
        elevators[elevator].state = ELEVATOR_CLOSED;
    }
    else
    {
        
        if(at_floor==0 || at_floor==FLOORS-1)
            elevators[elevator].direction*=-1;
        move_direction(elevator,elevators[elevator].direction);
        elevators[elevator].current_floor=at_floor+elevators[elevator].direction;
        elevators[elevator].state=ELEVATOR_ARRIVED;
    }
    
    pthread_mutex_unlock(&elevators[elevator].lock);
}


int isFloorEmpty(int at_floor, int elevator)
{
    
    int i = 0;
    while(i < PASSENGERS)
    {
        if (passengers[i].from_floor == at_floor && passengers[i].state != EXITED && passengers[i].elevNumb == elevator) {
            return 0;
        }
        i++;
    }
    return 1;
}




