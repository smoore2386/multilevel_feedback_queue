/*
 * ReadyList.cpp
 *
 *  Created on: Mar 8, 2012
 *      Author: shane
 */

#include <stdio.h>
#include <vector>
#include <deque>
#include <time.h>
#include <math.h>
#include <cstdlib>
#include <map>
#include <iostream>
#include<sys/types.h>
#include "headers/ReadyList.h"

using namespace std;


ReadyList::ReadyList()
{
	// Instantiate the ready list with correct levels
	this->levels.push_back(lev_zero);
	this->levels.push_back(lev_one);
	this->levels.push_back(lev_two);
	this->levels.push_back(lev_three);
}
ReadyList::ReadyList(int t)
{
	this->t = t;
	// Instantiate the ready list with correct levels
	this->levels.push_back(lev_zero);
	this->levels.push_back(lev_one);
	this->levels.push_back(lev_two);
	this->levels.push_back(lev_three);
}
void ReadyList::promote(int current_time)
{
	deque<Job*>::iterator it;
	bool flag = false;
	for(int i =1; i<4;i++)
	{	int x =0;
		it = levels[i].begin();
		while(it != levels[i].end())
		{
			
			if((current_time-(*it)->get_in_rdy()>=150))
			{
				cout <<current_time<<" - "<<(*it)->get_in_rdy()<<endl;
				if((*it)->get_in_rdy()<0){
					cout << (*it)->get_id();
				}
				Job* temp = (*it);
				temp->set_in_rdy(current_time);
				temp->set_curlev(i-1);
				levels[i].erase(levels[i].begin()+x);
				levels[i-1].push_back(temp);
				flag = true;
			}
			if (flag){break;};
			x++;
			it++;
		}
		if (flag){break;};
	}

}

/*
 * Add new job to ready list always to 1st level
 */
void ReadyList::add_new(Job* job)
{
	// push the job to fist level of queue
	levels[1].push_back(job);
	job->set_curlev(1);
	job->set_inqueue(true);
	

}
/*
 * Returns the first job ready to process
 */
Job* ReadyList::get_job()
{
	for(int i = 0; i < 4; i++ )
	{
		if(levels[i].size()>0)
		{
			Job* job = levels[i].front();
			int ts = this->gen_ts(i);
			job->set_ts(ts);
			levels[i].pop_front();
			return job;
		}
	}
	return NULL;
}

/*
 * Return the size of the list
 */
int ReadyList::size()
{
	return levels[0].size() + levels[1].size()+levels[2].size()+levels[3].size();
}

/*
 * Generate time slice for this device
 */
int ReadyList::gen_ts(int i)
{
	int x = pow(2.0,i)*2;
	return x;
}
/*
 * Insert job at specific location
 */
void ReadyList::insert(Job* job, int i)
{

	if(i>3){
		this->levels[0].push_back(job);
		job->set_curlev(0);
	}
	else{
		this->levels[i].push_back(job);
		job->set_curlev(i);	
	}
}
bool ReadyList::check_time(int current_time)
{
	deque<Job*>::iterator it;
	deque<int> ids;
	for(int i =1; i<4;i++)
	{
		it = levels[i].begin();
		while(it != levels[i].end())
		{
			if((current_time-(*it)->get_arr())>=150)
			{
				return true;
			}
			it++;
		}
	}
	return false;
}
/*
 * Destructor
 */
ReadyList::~ReadyList()
{
	//while(!levels.empty())
	//{
	//	while(!lev_zero.empty()||!lev_one.empty()
	//			||!lev_two.empty()||!lev_three.empty())
	//	{
	//		lev_zero.pop_front();
	//		lev_one.pop_front();
	//		lev_two.pop_front();
	//		lev_three.pop_front();
	//	}
	//}

}
