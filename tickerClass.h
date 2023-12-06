#pragma once
#include <vector>
#include <algorithm>

class Observer {
public:
	virtual void update() = 0;
};

class Ticker {
	std::vector<Observer*> observers;
public:
	void registerObserver(Observer* obs);
	void unregisterObserver(Observer* obs);
	void tick();
};