#pragma once

class Point {
	private:
		int pointId;
		double pointX, pointY;

	public:
		Point();
		Point(int pointId, double pointX, double pointY);
		~Point();
		int getPointId();
		double getPointX();
		double getPointY();
		void setPointId(int Id);
		void setPointX(double x);
		void setPointY(double y);

};