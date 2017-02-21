/*
 * PCB.h
 *
 *  Created on: Mar 9, 2012
 *      Author: shane
 */

#ifndef PCB_H_
#define PCB_H_

#include <string>
#include <vector>
#include <math.h>
#include <stack>
using namespace std;
class PCB
{
private:
	int n;
	int next;
	int compute_time;
	int cur_comp;
	stack<int> memory;

public:
	PCB();
	PCB(int n);
	int get_computet(){return this->compute_time;};
	void set_computet(int t){this->compute_time=t;};
	int get_cur_comp(){return this->cur_comp;};
	void set_cur_comp(int t){this->cur_comp=t;};
	int get_next();
	void set_next(int next);
	stack<int> get_mem(){return this->memory;};
	virtual ~PCB();
};

#endif /* PCB_H_ */
