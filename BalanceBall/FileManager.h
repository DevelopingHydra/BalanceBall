#pragma once

#include "stdafx.h"
#include <memory>
#include <string>

#include "PID_settings.h"
#include "Seesaw_settings.h"

struct LineValues {
	std::string first;
	std::string second;
	std::string third;
};

class FileManager
{
public:
	static FileManager& get_instance() {
		static FileManager instance;
		return instance;
	}

	FileManager(FileManager const&) = delete;
	FileManager(FileManager&&) = delete;

	PID_settings read_settings_PID();
	void write_settings_PID(PID_settings newSettings);

	Seesaw_settings read_settings_seesaw();
	void write_settings_seesaw(Seesaw_settings newSettings);

private:
	FileManager();

	std::string fileSeesawSettings_;
	std::string filePIDSettings_;

	LineValues read_line_values(std::string filename);
};


