#pragma once
class PID
{
public:
	PID();

	double calculateAngle(double ballLocation, double targetBallPosition);
	void reset();

private:
	double e = 0;
	double ealt = 0;
	double esum = 0;
	double satLow = -90;
	double satUp = 90;
	double kp = .2f;
	double ki = 0;
	double kd = 3;
	double ta = 1;
};

