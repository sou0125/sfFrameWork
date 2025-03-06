#include "Image.h"
#include "DirectX11.h"

void sf::ui::Image::Draw()
{
	dx::DirectX11* dx11 = dx::DirectX11::Instance();

	if (material.texture.isNull())
	{
		material.SetGPU(dx11->GetMainDevice());
	}
	else
	{
		material.texture->SetGPU(0, dx11->GetMainDevice());
		material.SetGPU(dx11->GetMainDevice(), true);
	}

	WorldMatrixBuffer mtx;
	mtx.mtx = GetMatrix();
	mtx.mtx = DirectX::XMMatrixTranspose(mtx.mtx);
	dx11->wBuffer.SetGPU(mtx, dx11->GetMainDevice());

	dx11->GetMainDevice().GetContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
	dx11->vsNone.SetGPU(dx11->GetMainDevice());
	dx11->gs2d.SetGPU(dx11->GetMainDevice());
	dx11->ps2d.SetGPU(dx11->GetMainDevice());

	dx11->GetMainDevice().GetContext()->Draw(1, 0);
}
