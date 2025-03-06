#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include <stdexcept>	//runtime_error���g������

#pragma comment(lib,"directxtk.lib")
#pragma comment(lib,"d3d11.lib")

#define SAFE_RELEASE(p)	if(p!=nullptr){p->Release();p=nullptr;}
#define STR(p) #p

namespace sf
{
	namespace dx
	{
		//D3D���N���X
		class D3D
		{
		public:
			virtual void Release() = 0;
		};
	}
}
