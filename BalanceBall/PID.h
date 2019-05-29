#pragma once
class PID
{
public:
	PID();
	~PID();

	double calculateAngle(double ballLocation, double targetBallPosition);

private:
	double e = 0;
	double ealt = 0;
	double esum = 0;
	double satLow = -90;
	double satUp = 90;
	double kp = 1;
	double ki = 0;
	double kd = 0;
	double ta = 1;
};

