/*
 * CPU.h
 *
 *  Created on: Mar 9, 2012
 *      Author: shane
 */

#ifndef CPU_H_
#define CPU_H_
#include <stack>
#include <queue>
#include <vector>
#include "IODevice.h"
#include "Job.h"

using namespace std;
class CPU
{
private:
	bool idle;
	stack <Job*> run_queue;
	int pc;
	queue<Job*> finished_jobs;
	bool fin;
public:
	CPU();
	CPU(CPU & ref);
	int compute(int current_time);
	bool get_fin(){return this->fin;};
	void set_fin(bool b){this->fin =b;};
	void add_job(Job* job){this->run_queue.push(job);};
	bool is_idle(){return this->idle;};
	int finished_size(){return this->finished_jobs.size();};
	void set_idle(bool t){this->idle =t;};
	int size(){return this->run_queue.size();};
	int fin_size(){return this->finished_jobs.size();};
	Job* remove_job();
	void print_finished();

	virtual ~CPU();
};

#endif /* CPU_H_ */
