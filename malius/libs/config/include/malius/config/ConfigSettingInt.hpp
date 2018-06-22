#pragma once
#include <malius/core/lang.hpp>

#include <limits>

// Reference: https://blog.molecular-matters.com/2011/06/27/config-values/

namespace ma
{
    namespace config
    {
        class ConfigSettingInt
        {
        public:
            /// Registers an integer setting
            MA_INLINE ConfigSettingInt(const char* name, const char* synopsis, int initialValue)
             : m_next(nullptr),
               m_name(name),
               m_synopsis(synopsis),
               m_value(initialValue),
               m_min(std::numeric_limits<int>::min()),
               m_max(std::numeric_limits<int>::max())
            {
                AddToList();
            };

            /// Registers an integer setting, constraining it to the range [minValue, maxValue]
            MA_INLINE ConfigSettingInt(const char* name, const char* synopsis, int initialValue, int minValue, int maxValue)
             : m_name(name),
               m_synopsis(synopsis),
               m_value(initialValue),
               m_min(minValue),
               m_max(maxValue)
            {
                AddToList();
            };

            /// Assigns an integer value to the setting
            ConfigSettingInt& operator=(int value);

            /// Returns the setting's value as integer
            MA_INLINE operator int(void) const { return m_value; };

            /// Tries to find a setting, returns a nullptr if no setting could be found
            //static ConfigSettingInt* FindSetting(const char* name);

        private:
            void AddToList(void);

            ConfigSettingInt* m_next;
            const char* m_name;
            const char* m_synopsis;
            int m_value;
            int m_min;
            int m_max;
        };

        //extern ConfigSettingInt g_verbosity;
    }
}