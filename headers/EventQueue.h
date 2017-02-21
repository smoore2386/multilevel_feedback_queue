/*
 * EventQueue.h
 *
 *  Created on: Mar 8, 2012
 *      Author: shane
 */

#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_

#include "Event.h"
using namespace std;

class EventQueue {

private:
	queue <Event* > events;

public:
	EventQueue();
	Event* get_event();
	void add_event(Event* event);
	int get_size(){return events.size();};
	bool empty(){return events.empty();};
	virtual ~EventQueue();
};

#endif /* EVENTQUEUE_H_ */
