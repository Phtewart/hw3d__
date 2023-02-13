#include "IndicesBuffer.h"

void IndicesBuffer::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
}

UINT IndicesBuffer::GetCount() const
{
	return count;
}
