#include "TransformCBuf.h"

namespace Bind
{
	TransformCbuf::TransformCbuf(Graphics& gfx, const Drawable& parent)
		:
		parent(parent)
	{
		if (!pVcbuf)
		{
			pVcbuf = std::make_unique<VertexConstantBuffer<Transforms>>(gfx);
		}
	}

	void TransformCbuf::Bind(Graphics& gfx) noexcept
	{
		const auto modelView = parent.GetTransformXM()* gfx.GetCamera();
		const Transforms tf =
		{
			DirectX::XMMatrixTranspose(modelView),
			DirectX::XMMatrixTranspose(
				modelView *
				gfx.GetCamera() *
				gfx.GetProjection()
			)
		};
		pVcbuf->Update(gfx, tf);
		pVcbuf->Bind(gfx);
	}

	std::unique_ptr<VertexConstantBuffer<TransformCbuf::Transforms>> TransformCbuf::pVcbuf;
}