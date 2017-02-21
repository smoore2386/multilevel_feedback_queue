/*
 * ReadyList.h
 *
 *  Created on: Mar 8, 2012
 *      Author: shane
 */

#ifndef READYLIST_H_
#define READYLIST_H_
#include <map>
#include "Job.h"

using namespace std;

class ReadyList
{
private:
	// t value time slice set with
	int t;
	//vector with appropriate levels
	vector<deque<Job*> > levels;
	deque<Job*> lev_zero;
	deque<Job*> lev_one;
	deque<Job*> lev_two;
	deque<Job*> lev_three;
public:
	//default constructor
	ReadyList();
	ReadyList(int t);
	void promote(int current_time);
	void add_new(Job* job);
	Job* get_job();
	void insert(Job* job, int i);
	int gen_ts(int i);
	int size();
	bool check_time(int current_time);
	void long_wait(int current);
	
	~ReadyList();
};

#endif /* READYLIST_H_ */
