#pragma once
#include <cstdint>
#include "AutoRef.h"
namespace sf
{
	namespace ref
	{
		namespace regacy
		{
			//���t�@�����X�^(regacy)
			class Ref
			{
			public:
				Ref();

				/// <summary>
				/// ���t�@�����X�̎擾
				/// </summary>
				/// <returns></returns>
				const uintptr_t& GetRef()const { return ref; }

			private:
				const uintptr_t ref;
			};
		}
	}
}