/*
 * IODevice.h
 *
 *  Created on: Mar 8, 2012
 *      Author: shane
 */

#ifndef IODEVICE_H_
#define IODEVICE_H_
#include "Job.h"
#include <queue>

using namespace std;
class IODevice
{

private:
	int _time;
	int type;
	queue< Job* > wait;

public:
	IODevice();
	IODevice(int type);
	IODevice(IODevice &ref);
	Job* remove();
	void do_io();
	int size();
	bool is_idle();
	int get_time(){return this->_time;};
	void add_job(Job* job);
	virtual ~IODevice();
};

#endif /* IODEVICE_H_ */
