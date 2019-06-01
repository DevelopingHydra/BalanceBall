#pragma once

#include "stdafx.h"

class IController {
public:
	virtual double calculate_angle(double ballLocation, double targetBallPosition) = 0;
	virtual void reset() = 0;
};