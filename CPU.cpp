/*
 * 	@Author Shane Moore
 *  @Subject Intro to Operating Systems
 *
 *	 CPU.cpp
 *
 *	Defines the CPU for the Multilevel feedback Queue
 *
 *  Created on: Mar 9, 2012
 *
 */
#include <string>
#include <iostream>
#include "headers/CPU.h"

/*
 * Default Constructor for the CPU
 */
CPU::CPU()
{
	this->pc =0;
	this->idle = true;
	this->fin = false;
}
/*
 * Copy Constructor
 */
CPU::CPU(CPU & ref)
{
	this->idle = ref.idle;
	this->pc = ref.pc;
	this->run_queue = ref.run_queue;
}
/*
 * This method defines the computation of the simulated process in memory
 */
int CPU::compute(int current_time)
{
	// get the job and set idle
	this->idle = false;
	
	if(run_queue.empty()){return 88;};
	// time slice and the current statement we are on
	int ts = run_queue.top()->get_ts();
	PCB* pcb = run_queue.top()->get_pcb();

	int curr_stmt = run_queue.top()->get_pcb()->get_next();
	while(true){
		
		if(run_queue.top()->get_pcb()->get_mem().empty())
		{
			// this path is executed if there are no more statements to be executed
			Job* temp = run_queue.top();
			//set complete time of job
			if(pcb->get_cur_comp()==0){
				temp->set_complete(current_time);
			}
			else
			{
				//set complete time of job
				temp->set_complete(current_time+pcb->get_cur_comp());
			}
			// Add jobs to finish list
			finished_jobs.push(temp);
			this->set_fin(true);
			run_queue.pop();
			return 9;
		}
		if(curr_stmt%2==0)
		{
			// generate random number to send to iodevice and return it to main program
			int randNum = (rand() % 3) ;
			// so now we know this is idle
			this->set_idle(true);
			return randNum;
		}
		else
		{
			
			if(pcb->get_computet()==0){
				curr_stmt= pcb->get_next();
			}
			else if(ts-(pcb->get_cur_comp()) <= 0)
			{
				//if it is less than zero then we will finish a time slice
				this->set_idle(true);
				// set total time which is old total time plus timeslice
				run_queue.top()->set_totalt(run_queue.top()->get_totalt()+ts);

				//set our current comp time to the difference of current comp time and ts
				int diff = pcb->get_cur_comp()-ts;
				pcb->set_cur_comp(diff);
				// set the next statement to the current statement
				pcb->set_next(curr_stmt);
				return 3;
			}
			else if(ts-(run_queue.top()->get_pcb()->get_cur_comp())>0){
				//we are here because we compute with time left over in timeslice
				// set total time
				run_queue.top()->set_totalt(run_queue.top()->get_totalt()+(pcb->get_cur_comp()));
				//reset our current compute time				
				//set cpu to idle
				this->set_idle(true);
				
				// get current stmt which should be even and hence a io event
				curr_stmt = run_queue.top()->get_pcb()->get_next();
			}
		}
		
	}
	return NULL;	
}
/*
 * Remove Job from the CPU
 *
 * @return Job* pointer to job
 */
Job* CPU::remove_job()
{	//compute where we are in the program counter for the job
	Job* job = run_queue.top();
	run_queue.pop();
	return job;
}
void CPU::print_finished()
{
	cout << "ID  | Arr  |  Tot  | IO1   |  IO2  |  IO3   |  Com   |   Tur  |    Wai  |    Res"<<endl;
	cout<< "================================================================================"<<endl;
	while(!finished_jobs.empty())
	{
		Job* temp = finished_jobs.front();
		temp->to_string(1);
		finished_jobs.pop();
	}
	cout<< "================================================================================"<<endl;
}
/*
 * Destructor for the CPU
 */
CPU::~CPU() {
	if(!run_queue.empty())
	{
		run_queue.pop();
	}
	while(!finished_jobs.empty())
	{
		finished_jobs.pop();
	}

}
