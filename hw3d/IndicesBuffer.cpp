#include "IndicesBuffer.h"
#include "GFXExceptionMacros.h"
#include "BindableCodex.h"

namespace Bind
{
	IndicesBuffer::IndicesBuffer(Graphics& gfx, const std::vector<unsigned short>& indices)
		:
		IndicesBuffer(gfx, "?", indices)
	{
	}
	IndicesBuffer::IndicesBuffer(Graphics& gfx, std::string tag, 
									const std::vector<unsigned short>& indices)
		:
		tag(tag),
		count((UINT)indices.size())
	{
		INFOMAN(gfx);

		D3D11_BUFFER_DESC ibd = {};
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.Usage = D3D11_USAGE_DEFAULT;
		ibd.CPUAccessFlags = 0u;
		ibd.MiscFlags = 0u;
		ibd.ByteWidth = UINT(count * sizeof(unsigned short));
		ibd.StructureByteStride = sizeof(unsigned short);
		D3D11_SUBRESOURCE_DATA isd = {};
		isd.pSysMem = indices.data();
		GFX_THROW_INFO(GetDevice(gfx)->CreateBuffer(&ibd, &isd, &pIndexBuffer));
	}
	void IndicesBuffer::Bind(Graphics& gfx) noexcept
	{
		GetContext(gfx)->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
	}

	UINT IndicesBuffer::GetCount() const
	{
		return count;
	}
	std::shared_ptr<IndicesBuffer> IndicesBuffer::Resolve(Graphics& gfx, const std::string& tag,
															const std::vector<unsigned short>& indices)
	{
		assert(tag != "?");
		return Codex::Resolve<IndicesBuffer>(gfx, tag, indices);
	}
	std::string IndicesBuffer::GetUID() const noexcept
	{
		return GenerateUID_(tag);
	}
	std::string IndicesBuffer::GenerateUID_(const std::string& tag)
	{
		using namespace std::string_literals;
		return typeid(IndicesBuffer).name() + "#"s + tag;
	}
}