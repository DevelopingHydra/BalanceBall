#pragma once

#include "IController.h"
#include "PID_settings.h"


class PID : public IController
{
public:
	PID(PID_settings settings);

	// Inherited via IController
	virtual double calculate_angle(double ballLocation, double targetBallPosition) override;
	virtual void reset() override;

private:
	double e = 0;
	double ealt = 0;
	double esum = 0;
	double satLow = -90;
	double satUp = 90;
	double kp = 0.2;
	double ki = 0;
	double kd = 3;
	double ta = 1;

};

