/*
 * PCB.cpp
 *
 *  Created on: Mar 9, 2012
 *      Author: shane
 */
#include <vector>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "headers/PCB.h"
#include <stack>
/*
 * Default Constructor
 */
PCB::PCB()
{
	this->n = 0;
	this->compute_time = 0;
}
/*
 * Argumented constructor
 *
 * @params n the Job n value for timing
 */
PCB::PCB(int n)
{
	this->n=n;
	double x = rand() / double(RAND_MAX);
	this->compute_time = ((-20) * (log(1-x)));
	this->cur_comp= compute_time;
	
	for(int i =(2*n)+1; i >0;i--)
	{
		memory.push(i);
	}
}
int PCB::get_next(){
	//get the front number and return it to know which instr we are on
	int temp = memory.top();
	memory.pop();
	return temp;
}
void PCB::set_next(int next)
{
	memory.push(next);
}
/*
 * Destructor
 */
PCB::~PCB()
{

}
