#pragma once
class Camera
{
public:
	Camera(int x, int y) {
		xPosition = x;
		yPosition = y;
	};

	void setX(double x);
	void setY(double y);

	double getX();
	double getY();

private:
	double xPosition;
	double yPosition;
};
