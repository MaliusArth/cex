#include <malius/config/ConfigSettingInt.hpp>
#include <malius/log/Logger.hpp>

namespace ma
{
    namespace config
    {

        /// The above is the implementation for integer settings 
        /// (there are similar implementations for floats and bools as well). 
        /// Each config value holds 
        /// * the value�s name (which is used for looking-up values by name, 
        ///   e.g. in scripts, in-game console, when loading config files), 
        /// * and the value�s synopsis, 
        /// * as well as the value itself, 
        /// * along with minimum and maximum values. 
        /// Min and max values can be specified in the constructor, 
        /// making it possible to declare e.g. a config value 
        /// for the different verbosity levels in log, 
        /// which are restricted to [0, 2].

        //ConfigSettingInt g_verbosity("Verbosity", "Defines the verbosity level of logging operations", 0, 0, 2);

        /// The assignment operator and the cast operator to int allow a config value to be used like a real integer
        //void test(void)
        //{
        //    // coding using the config value
        //    if (log::g_verbosity > 1)
        //    {
        //        // whatever
        //    }
        //}

        /// As you can see, adding new config values takes only a single line of code. And recompilation times are kept to a minimum, because only .cpp files need to be changed. If any config value needs to be accessed from a different translation unit, you can either access it by name (which is more error-prone), or declare it as being extern.

        /// The assignment operator automatically makes sure that the value still lies in its designated range:
        ConfigSettingInt& ConfigSettingInt::operator=(int value)
        {
            if (value < m_min)
            {
                 MA_WARNING("Config", "Could not set value %d for setting \"%s\" because it is smaller than the minimum. It will be set to %d.", value, m_name, m_min);
                value = m_min;
            }
            else if (value > m_max)
            {
                 MA_WARNING("Config", "Could not set value %d for setting \"%s\" because it is greater than the maximum. It will be set to %d.", value, m_name, m_max);
                value = m_max;
            }

            m_value = value;
            return *this;
        }

        /// So far, we have fulfilled pretty much all of the initial requirements, except the last bullet point : Adding new config values in code should not need dynamic memory allocation.This is very crucial for me, because I absolutely despise those lazy - initialized singletons and platform - dependent hacks you will need if you want to store e.g.pointers to config values in a static std::vector.Otherwise, you will be hit by C++�s static initialization order fiasco.That is, if different config values are defined in different translation units, there�s no standards - compliant way to make sure they all are constructed in a certain order.
        /// 
        /// So if you want to store everything in a static std::vector, a singleton, or someplace else, you have to rely on lazy - initialized singletons, or platform - dependent hacks, or both.Otherwise you can�t be sure that the memory system is already started, the vector has already been constructed, etc.I worked on codebases which did all of the above, and it was not nice.
        /// 
        /// But we really want to be able to only add a single line to a.cpp file, and have our new config value ready, without resorting to any of the above, and without allocating memory via new, malloc, or similar.So how do we do it ?
        /// 
        /// This is were the �ConfigSettingInt* m_next� member comes into play.Essentially, this is a link to the next value in an intrusive linked list.Both constructors make a call to AddToList(), which does the following :

        namespace
        {
            static ConfigSettingInt* head = nullptr;
            static ConfigSettingInt* tail = nullptr;
        }


        //ConfigSettingInt* ConfigSettingInt::FindSetting(const char* name)
        //{

        //    return nullptr;
        //}

        void ConfigSettingInt::AddToList(void)
        {
            if (head)
            {
                tail->m_next = this;
                tail = this;
            }
            else
            {
                head = this;
                tail = this;
            }
        }

        /// The subtle difference between a static std::vector and the static pointers here is, that those pointers are of integral type, and will therefore be stored in either the.bss or .sdata segment, which means they will already be initialized long before any pre - main constructor or similar is called.So AddToList() does nothing more than adding the globally declared config value to a global linked - list.No matter in which.cpp file you add config values, and no matter in which order they are initialized, you will always have a linked - list of all ConfigSettingInt of your whole application, easily accessible and implemented in a standards - compliant way.
        /// 
        /// No dynamic memory allocation, minimal pre - main work, no singletons, no hacks, no nothing.Win!
        /// 
        /// To give credit where credit is due, I first saw this trick of using intrusive linked lists like this in one of the earlier Doom or Quake SDKs, courtesy of id Software.



        // if (g_renderBackground)
        // {
        //     // render models & meshes belonging to the background here
        //     �
        // }

        /// You could change the value of �g_renderBackground� using e.g.in - game menus, or a built - in console like in the id engines, or through script code.It behaves as if you would change a global boolean variable.

        /// I try to keep engine restarts to an absolute minimum, therefore all things that are considered �data� by the engine (config values, assets, etc.) can be reloaded at run-time without having to restart the engine. In the case of config variables, this is achieved by loading files containing values of such variables at run-time, simply replacing them. In conjunction with a directory watcher, values are automatically updated once the file is saved.

        // g_isWindowed
        // or screen resolution




        /// What I do is that e.g.�g_verbosity = 1� would mean it has to be a ConfigSettingInt, whereas �g_someValue = 10.0� means it would have to be a float.That is, every setting that contains a decimal point or a digit followed by the character �f� is considered to be a float - setting.

        /// If you really want it to be generic in the sense that you can iterate all settings, looking for a particular name, then yes, I would also introduce some kind of polymorphic class on top of this.But I would always leave the current implementation as it is, and only add a simple polymorphic wrapper / adapter class on top of this implementation.

    }
}
