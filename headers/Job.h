/*
 * Job.h
 *
 *  Created on: Mar 9, 2012
 *      Author: shane
 */

#ifndef JOB_H_
#define JOB_H_

#include "PCB.h"

class Job
{
private:
	int n;
	int id;
	PCB* pcb;
	int ts;
	int cur_lev;
	int total_time;
	int io1_time;
	int io2_time;
	int io3_time;
	bool in_queue;
	int completion_time;
	int arrival_time;
	int in_rdy;

public:
	Job();
	Job(int id);
	Job(Job & ref);

	PCB* get_pcb(){return this->pcb;};
	int get_n() {return this->n;};
	int get_id(){return this->id;};
	void set_id(int id){this->id = id;};
	int get_ts(){return this->ts;};
	void set_inqueue(bool in_queue){this->in_queue = in_queue;};
	bool get_inqueue(){return this->in_queue;};
	void set_ts(int ts){ this->ts =ts;};
	int get_curlev(){return this->cur_lev;};
	void set_curlev(int lev){this->cur_lev=lev;};
	int get_totalt(){return this->total_time;};
	void set_totalt(int tt){this->total_time=tt;};
	int get_io1(){return this->io1_time;};
	void set_io1(int io){this->io1_time=io;};
	int get_io2(){return this->io2_time;};
	void set_io2(int io){this->io2_time=io;};
	int get_io3(){return this->io3_time;};
	void set_io3(int io){this->io3_time=io;};
	void set_arr(int a){this->arrival_time=a;};
	int get_arr(){return this->arrival_time;};
	int get_complete(){return this->completion_time;};
	void set_complete(int c){this->completion_time =c;};
	int get_in_rdy(){return this->in_rdy;};
	void set_in_rdy(int c){this->in_rdy =c;};
	void to_string(int p);
	virtual ~Job();
};

#endif /* JOB_H_ */
