#include "PID.h"

PID::PID(PID_settings settings) :
	kd{ settings.D },
	ki{ settings.I },
	kp{ settings.P }
{
}

double PID::calculate_angle(double ballLocation, double targetBallPosition)
{
	double y = 0;
	e = targetBallPosition - ballLocation;

	if ((y > satLow) && (y < satUp))
	{
		esum = esum + e; //anti-windup
	}
	y = (kp * e); //P-ANTEIL
	y += (ki * ta * esum); //I-ANTEIL
	if (ta != 0)
		y += (kd * (e - ealt) / ta); //D-ANTEIL
	ealt = e;

	if (y < satLow)
	{
		y = satLow;
	}
	else if (y > satUp)
	{
		y = satUp;
	}

	return y;
}

void PID::reset()
{
	this->e = 0;
	this->esum = 0;
	this->ealt = 0;
}
