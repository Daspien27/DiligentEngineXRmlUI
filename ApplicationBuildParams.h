#pragma once

#include <string>

struct application_build_params {
	std::string application_name;
	int width = 800;
	int height = 600;
	bool allow_resize = false;
};

extern application_build_params create_application_build_params(); // Client is expected to implement