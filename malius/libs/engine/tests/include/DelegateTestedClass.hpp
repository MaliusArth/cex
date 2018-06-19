// Filename: DelegateTestClass.hpp
// Created by: Malius Arth
// Date created: 23.07.2016 (DD.MM.YYYY)

#pragma once

namespace ma
{
	namespace test
	{
		namespace events
		{
			inline void FuncVoid0Args(void)
			{
				// do something
			}

			inline void FuncVoid0Args_2(void)
			{
				// do something
			}

			inline void FuncVoid1Arg(int a)
			{
				// do something
			}

			inline void FuncVoid2Args(float a, float b)
			{
				// do something
			}

			inline int FuncInt0Args(void)
			{
				return -1;
			}

			inline int FuncInt1Arg(int a)
			{
				return a + 10;
			}

			inline float FuncFloat2Args(float a, float b)
			{
				return a - b;
			}

			struct DelegateTestedClass
			{
				DelegateTestedClass() {}

				void FuncVoid0Args(void)
				{
					// do something
				}

				void FuncVoid0Args(void) const
				{
					// do something
				}

				static void FuncVoid0ArgsStatic(void)
				{
					// do something
				}

				void FuncVoid1Arg(int arg)
				{
					// do something
				}

				void FuncVoid1Arg(int arg) const
				{
					// do something
				}

				static void FuncVoid1ArgStatic(int arg)
				{
					// do something
				}

				void FuncVoid2Args(float a, float b)
				{
					// do something
				}

				void FuncVoid2Args(float a, float b) const
				{
					// do something
				}

				static void FuncVoid2ArgsStatic(float a, float b)
				{
					// do something
				}

				int FuncInt0Args(void)
				{
					return 7 - seven;
				}

				int FuncInt0Args(void) const
				{
					return 1;
				}

				static int FuncInt0ArgsStatic(void)
				{
					return 7;
				}

				int FuncInt1Arg(int a)
				{
					return a + 20;
				}

				int FuncInt1Arg(int a) const
				{
					return a + 30;
				}

				static int FuncInt1ArgStatic(int a)
				{
					return a + 70;
				}

				float FuncFloat2Args(float a, float b)
				{
					return a + b;
				}

				float FuncFloat2Args(float a, float b) const
				{
					return a * b;
				}

				static float FuncFloat2ArgsStatic(float a, float b)
				{
					return a / b;
				}

			private:
				int seven = 7;
			};
		}
	}
}
