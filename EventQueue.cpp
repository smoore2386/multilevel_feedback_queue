/*
 * EventQueue.cpp
 *
 *  Created on: Mar 8, 2012
 *      Author: shane
 */


#include <queue>

#include "headers/EventQueue.h"

using namespace std;

/*
 * Default Constructor
 */
EventQueue::EventQueue()
{
	this->events.push(new Event(1,0));
}
/*
 * Add event to event Queue
 * @param event - event to be added
 */
void EventQueue::add_event(Event* event)
{
	events.push(event);
}
/*
 * Get top of event queue
 *
 * @return Event* top of queue
 */
Event* EventQueue::get_event()
{

	if(!events.empty())
	{
		Event* event = events.front();
		events.pop();
		return event;
	}
	return NULL;
}

EventQueue::~EventQueue()
{
	while(!events.empty())
	{
		events.pop();
	}
}
