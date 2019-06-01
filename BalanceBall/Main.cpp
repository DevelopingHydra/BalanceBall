#include "stdafx.h"
#include "GUI.h"
#include <iostream>

int main(void) {
	try {
		GUI gui;
		gui.show();
	}
	catch (std::exception e) {
		std::cout << std::endl << std::endl << "AN ERROR OCCURED" << std::endl;
		return 1;
	}

	return 0;
}
