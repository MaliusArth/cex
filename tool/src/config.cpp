// #include <malius/config/ConfigSettingInt.hpp>
#include <malius/log/Logger.hpp>

namespace ma
{
	namespace log
	{
		// extern config::ConfigSettingInt g_verbosity = 2;
		::ma::config::ConfigSettingInt g_verbosity("Verbosity",
				"Defines the verbosity level of logging operations", 0, 0, 2);
	}
}