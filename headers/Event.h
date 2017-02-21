/*
 * Event.h
 *
 *  Created on: Mar 9, 2012
 *      Author: shane
 */

#ifndef EVENT_H_
#define EVENT_H_

class Event
{
private:
	int time;
	int type;

public:
	Event();
	Event(int type,int time);
	void set_time(int time) {this-> time=time;};
	int get_time(){return this->time;};
	void set_type(int type){this->type = type;};
	int get_type(){return this->type;};
	virtual ~Event();
};

#endif /* EVENT_H_ */
