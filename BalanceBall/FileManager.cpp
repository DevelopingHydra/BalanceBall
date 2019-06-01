#include "FileManager.h"

#include <filesystem>
#include <fstream>

using namespace std;

FileManager::FileManager()
{
	string cwd = experimental::filesystem::current_path().string();
	this->filePIDSettings_ = cwd + "/../resources/settings_pid.txt";
	this->fileSeesawSettings_ = cwd + "/../resources/settings_seesaw.txt";
}

LineValues FileManager::read_line_values(std::string filename)
{
	string line;
	ifstream file{ filename };

	if (file.is_open()) {
		getline(file, line);
		file.close();
	}
	else {
		throw runtime_error{ "Unable to open settings file for PID" };
	}

	// now extract information
	size_t currentDelimiter = line.find(';');
	size_t nextDelimiter;
	string first = line.substr(0, currentDelimiter);
	nextDelimiter = line.find(';', currentDelimiter + 1);
	string second = line.substr(currentDelimiter + 1, nextDelimiter - currentDelimiter - 1);
	currentDelimiter = nextDelimiter;
	nextDelimiter = line.find(';', currentDelimiter + 1);
	string third = line.substr(currentDelimiter + 1, nextDelimiter - currentDelimiter);

	LineValues values{};
	values.first = first;
	values.second = second;
	values.third = third;

	return values;
}

PID_settings FileManager::read_settings_PID()
{
	LineValues values = this->read_line_values(this->filePIDSettings_);

	PID_settings settings{};
	settings.P = stod(values.first);
	settings.I = stod(values.second);
	settings.D = stod(values.third);

	return settings;
}

Seesaw_settings FileManager::read_settings_seesaw()
{
	LineValues values = this->read_line_values(this->fileSeesawSettings_);

	Seesaw_settings settings{};
	settings.max_alpha = stof(values.first);
	settings.max_diff_alpha = stof(values.second);
	settings.width = stof(values.third);

	return settings;
}


