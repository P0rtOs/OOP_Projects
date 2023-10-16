#pragma once

class Point {
	private:
		int pointId;
		double pointX, pointY;

	public:
		Point();
		~Point();
		int getPointId();
		double getPointX();
		double getPointY();
		void setPointX(double x);
		void setPointY(double y);

};