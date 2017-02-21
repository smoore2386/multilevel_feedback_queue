/*
 * Event.cpp
 *
 *	Defines Event for event queue for multi level feedback queue
 *  Created on: Mar 9, 2012
 *      Author: shane
 */

#include "headers/Event.h"
/*
 * Default Constructor
 */
Event::Event()
{
	this->time =0;
	this->type = 1;

}
/*
 * Argumented Constructor
 *
 * @params type - the type of event
 * @params time - the current time of event
 */
Event::Event(int type,int time)
{
	this->time=time;
	this->type=type;
}
/*
 * Destructor
 */
Event::~Event()
{
	// TODO Auto-generated destructor stub
}
