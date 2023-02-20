#pragma once
#include "Bindable.h"
#include "GFXExceptionMacros.h"

namespace Bind
{
	class IndicesBuffer : public Bindable
	{
	public:
		IndicesBuffer(Graphics& gfx, const std::vector<unsigned short>& indices);	
		void Bind(Graphics& gfx) noexcept override;
		UINT GetCount() const;
	protected:
		UINT count;
		Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
	};
}