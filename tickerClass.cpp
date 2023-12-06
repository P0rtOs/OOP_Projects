#include "tickerClass.h"

void Ticker::registerObserver(Observer* obs) {
	observers.push_back(obs);
}

void Ticker::unregisterObserver(Observer* obs) {
	observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}

void Ticker::tick() {
	for (Observer* obs : observers) {
		obs->update();
	}
}


// TODO: Вписать тиккер клас в менеджер приложения, зарегистрировать всех обсерверов, которые должны тикаться