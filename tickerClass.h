#pragma once
#include <vector>
#include <algorithm>
#include <string>

class Observer {
public:
	virtual void update() = 0;
	virtual std::string currentStatus() = 0;
};

class Ticker {
	std::vector<Observer*> observers;
	unsigned int tickNumber = 0;
public:
	void registerObserver(Observer* obs);
	void unregisterObserver(Observer* obs);
	void tick();

};