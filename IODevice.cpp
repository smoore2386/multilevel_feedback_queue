/*
 * IODevice.cpp
 *
 *  Created on: Mar 8, 2012
 *      Author: shane
 */

#include <queue>
#include "headers/Job.h"
#include "headers/IODevice.h"


using namespace std;
/*
 * Default constructor for IO Device
 */
IODevice::IODevice(){
	this->type =1;
	this->_time =40;
}
/*
 * Constructor for IO Device
 * @params type - defines which io device we are using
 */
IODevice::IODevice(int type)
{
	this->type = type;
	if (type == 1)
	{
		this->_time = 40;
	}
	else if (type ==2)
	{
		this->_time = 30;
	}
	else if(type ==3)
	{
		this->_time = (-50)*(log(1-rand() / double(RAND_MAX)));
	}
}
/*
 * Do the IO this is done just by adding the time
 * to the jobs respective variable
 */
void IODevice::do_io()
{
	if (this->type==1){wait.front()->set_io1(wait.front()->get_io1()+this->_time);}
	if (this->type==2){wait.front()->set_io2(wait.front()->get_io2()+this->_time);}
	if (this->type==3){wait.front()->set_io3(wait.front()->get_io3()+this->_time);}
}
/*
 * See if the device is idle/ has no processes
 */
bool IODevice::is_idle()
{
	return this->wait.empty();
}
Job* IODevice::remove()
{
	Job* temp = wait.front();
	wait.pop();
	return temp;
}
/*
 * Adds job to wait queue
 */
void IODevice:: add_job(Job* job)
{
	wait.push(job);
}
int IODevice::size()
{
	return wait.size();
}


/*
 * Destructor for Device
 */
IODevice::~IODevice()
{
	while(!wait.empty()){ wait.pop();};
}
