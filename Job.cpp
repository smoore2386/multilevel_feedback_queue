/*
 * 	@Author Shane Moore
 *  @Subject Intro to Operating Systems
 *
 *	 Job.cpp
 *	Defines a Job for the Multilevel feedback Queue
 *  Created on: Mar 9, 2012
 *
 */
#include <stdlib.h>
#include <string>
#include <iostream>
#include "headers/Job.h"

/*
 * Default Constructor for a Job
 */
Job::Job()
{
	this->n = -8*log(1-(float)rand()/(float)RAND_MAX); //code to getnerate random
	if(n==0){
		this->n =1;
	}
	this->id = 0;
	this->pcb = new PCB(n);
	this->ts = 0;
	this->io1_time =0;
	this->io2_time =0;
	this->io3_time =0;
	this->cur_lev =0;
	this->total_time =0;
	this->completion_time=0;
	this->arrival_time=0;

}
/*
 * Constructor where the id is passed
 */
Job::Job(int id)
{
	this->n = -8*log(1-(float)rand()/(float)RAND_MAX); //code to getnerate random
	this->id = id;
	this->pcb = new PCB(n);
	this->ts = 0;
	this->io1_time =0;
	this->io2_time =0;
	this->io3_time =0;
	this->total_time=0;
	this->cur_lev = 0;
	this->in_rdy=0;

}
/*
 * Copy Constructor
 */
Job::Job(Job & ref)
{
	this->n = ref.n;
	this->id=ref.id;
	this->pcb=ref.pcb;
	this->ts = ref.ts;
	this->io1_time =ref.io1_time;
	this->io2_time =ref.io2_time;
	this->io3_time = io3_time;
	this->in_queue = ref.in_queue;
	this->cur_lev = ref.cur_lev;
}
void Job::to_string(int p)
{
	if(p ==1)
	{
		cout <<this->get_n()<<"||||";
		cout << this->get_id()<<"  |";
		cout << this->arrival_time<<"   "<<"|  ";
		cout << this->total_time<<"   "<<"|  ";
		cout << this->io1_time<<"   "<<"|  ";
		cout << this->io2_time<<"   "<<"|  ";
		cout << this->io3_time<<"   "<<"|  ";
		cout << this->completion_time<<"   "<<"|  ";
		//turn around
		int turn = this->completion_time-this->arrival_time;
		cout << turn <<"   "<<"|  ";
		cout <<this->get_complete()-this->get_totalt()<<"   "<<"|  ";
		//response ratio
		float rr = (float)turn/this->get_totalt();
		cout<< rr<<"   "<<endl;
	}
	else if( p==2){
		cout << this->get_id()<<"  |";
		cout << this->arrival_time<<"   "<<"|  ";
		cout << this->total_time<<"   "<<"|  ";
		cout << this->io1_time<<"   "<<"|  ";
		cout << this->io2_time<<"   "<<"|  ";
		cout << this->io3_time<<"   "<<"|  ";
		cout << this->completion_time<<"   "<<"|  ";
		//turn around
		int turn = this->completion_time-this->arrival_time;
		cout << turn <<"   "<<"|  ";
		cout <<this->get_complete()-this->get_totalt()<<"   "<<"|  ";
		//response ratio
		float rr = (float)turn/(this->get_totalt()+this->get_io1()+this->get_io2()+this->get_io3());
		cout<< rr<<"   "<<endl;
	}
}
/*
 * Destructor for Job
 */
Job::~Job()
{
	delete pcb;

}
