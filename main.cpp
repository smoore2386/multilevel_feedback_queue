/*
 * 	@Author Shane Moore 112858958
 *  @Subject Introduction to Operating Systems
 *
 * 	Multi Level Feedback Queue
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <queue>
#include <math.h>
#include <iostream>

#include "headers/ReadyList.h"
#include "headers/Job.h"
#include "headers/CPU.h"
#include "headers/EventQueue.h"

using namespace std;
/*
* function that generates random num
*/
double ranom()
{

	return rand() / double(RAND_MAX);
}
/*
 * Main Entry of program
 */

int main()
{
	//seed for our random number
	srand(time(0));
	
	int x = ranom();

	//Keep track of the ids of our jobs
	int id_counter = 1;

	int current_time,event_type;
	
	//Ready List
	ReadyList* ready = new ReadyList();

	// long term scheduler
	queue<Job*> job_scheduler; 

	// holds events
	EventQueue* events = new EventQueue();

	//gives what our current event is
	Event* current_event = NULL;	
	
	// CPU
	CPU* cpu = new CPU();
	
	// Create our IO devices and push them to the list
	vector<IODevice*> devices;
	devices.push_back(new IODevice(1));
	devices.push_back(new IODevice(2));
	devices.push_back(new IODevice(3));

	bool first = true;
	// Push the 50 jobs into the long term scheduler
	for (int i =0; i <50;i++){
		
		job_scheduler.push(new Job());
	}

	int i=0;
	// Main loop for Event Queue
	while(true)
	{
		
		
		// Get the current event and times
		current_event = events->get_event();
		current_time = current_event->get_time();
		event_type = current_event->get_type();
		int mult_lev = cpu->size()+ready->size()+devices[0]->size()+devices[1]->size()+devices[2]->size();
		if (i< 100){
			// print first 100 events
			cout << "Event Number: " << event_type<<" Current Time: " <<current_time;
			cout << ", Jobs in Queue, Run: "<< cpu->size() <<", Ready: " << ready->size();
			cout <<", Device 1: " <<devices[0]->size()<<", Device 2: "<< devices[1]->size();
			cout << ", Device 3: "<<devices[2]->size();
		
			cout << "Level of Multiprogramming: " << mult_lev<<endl;
			
			i++;
		}
		// current event 1 is the arrival of new job
		if (current_event->get_type()==1)
		{
			Job* temp = job_scheduler.front();
			
			// 2.create and store job in mem auto done with PCB
			temp->set_id(id_counter);
			// 3. Storing job into job table is irrelevant as our pcb will keep track of everything

			// Increment for next id
			id_counter++;
			
			// 5. if more jobs needed determine time of arrival of nex tjob and insert a new node in the event queue with event type = 1 time = arrival time of next job
				
			if(job_scheduler.size()>1)
			{
				//compute arrival of next job and put in queue
				int next_time = (-8)*(log(1-ranom()));
				temp->set_arr(next_time+current_time);	
				events->add_event(new Event(1,current_time+next_time));
			}
			if (first)
				{
					events->add_event(new Event(2,0));
					first = false;
				}
			
		} // Event 2 Schedule the job
		else if(current_event->get_type()==2)
		{
			if(mult_lev < 8&&!job_scheduler.empty()){
				Job* temp = job_scheduler.front();
				temp->set_in_rdy(current_time);
				ready->add_new(temp);
				
				job_scheduler.pop();
			}

			//Using th escheduling algorithm determine next cpu.compute(ready.get_job())
			Job* to_cpu = ready->get_job();
			cpu->add_job(to_cpu);
			int n =cpu->compute(current_time);
			//check to see if we have a finished job
			if(cpu->get_fin())
			{
				if(cpu->fin_size()==50){
					break;
				}
				cpu->set_fin(false);
				//events->add_event(new Event(1,current_time));
				events->add_event(new Event(2,current_time));
			}
			else if (n==3)
			{
				// okay so here which mean we finished our time slice 
				events->add_event(new Event(3,current_time+to_cpu->get_ts()));
			}
			else if(n==0||n==1||n==2)
			{
				// we are finished doing compute for this part now to io
				Job* temp = cpu->remove_job();
				devices[n]->add_job(temp);
				// temp number to calculate next current time
				int q = temp->get_pcb()->get_cur_comp();
				// reset the current compute time
				events->add_event(new Event(n+4,current_time+q));	
			}
		}
		else if(current_event->get_type()==3)
		{
			
			//completion of time slice
			// 1. Save PC of the running program(taken care of in cpu)
			Job* temp  = cpu->remove_job();
			// 2. Move job from run queue to ready queue
			temp->set_in_rdy(current_time);
			ready->insert(temp,temp->get_curlev()+1);
			// 3. Schedule the next job
			events->add_event(new Event(2,current_time));
		}
		else if(current_event->get_type()==4)
		{	// Device number 1
			devices[0]->do_io();
			Job* temp = devices[0]->remove();
			temp->set_in_rdy(current_time+40);
			ready->insert(temp,0);
			events->add_event(new Event(2,current_time+40));

		}
		else if(current_event->get_type()==5)
		{	
			devices[1]->do_io();
			Job* temp = devices[1]->remove();
			temp->set_in_rdy(current_time+30);
			ready->insert(temp,0);
			events->add_event(new Event(2,current_time+30));
		}
		else if(current_event->get_type()==6)
		{	
			devices[2]->do_io();
			Job* temp = devices[2]->remove();
			temp->set_in_rdy(current_time+devices[2]->get_time());
			ready->insert(temp,0);
			events->add_event(new Event(2,current_time+devices[2]->get_time()));
		}
		else if(current_event->get_type()==7)
		{
			ready->promote(current_time);	
		}
		//here we check if we need to input 7
		bool check = ready->check_time(current_time);
		if(check)
		{
			events->add_event(new Event(7,current_time));
		}
		if (current_time<0){
			break;}
		
	}



	cpu->print_finished();
	delete cpu;
	delete ready;
	devices.clear();
	delete events;
	return 0;
}
