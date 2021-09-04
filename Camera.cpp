#include "Camera.h"

void Camera::setX(double x) {
	xPosition = x;
}

void Camera::setY(double y) {
	yPosition = y;
}

double Camera::getY() {
	return yPosition;
}

double Camera::getX() {
	return xPosition;
}