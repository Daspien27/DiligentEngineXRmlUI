#include "ApplicationBuildParams.h"

application_build_params create_application_build_params()
 {
 using namespace std::string_literals;
 return application_build_params{
	 .application_name = "DiligentEnding x RmlUI"s,
	 .width = 800,
	 .height = 600,
	 .allow_resize = true,
 };
}