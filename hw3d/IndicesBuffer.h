#pragma once
#include "Bindable.h"
#include "GFXExceptionMacros.h"
#include <memory>

namespace Bind
{
	class IndicesBuffer : public Bindable
	{
	public:
		IndicesBuffer(Graphics& gfx, const std::vector<unsigned short>& indices);
		IndicesBuffer(Graphics& gfx, std::string tag, const std::vector<unsigned short>& indices);
		void Bind(Graphics& gfx) noexcept override;
		UINT GetCount() const;
		static std::shared_ptr<IndicesBuffer> Resolve(Graphics& gfx, const std::string& tag,
			const std::vector<unsigned short>& indices);
		template<typename...Ignore>
		static std::string GenerateUID(const std::string& tag, Ignore&&...ignore)
		{
			return GenerateUID_(tag);
		}
		std::string GetUID() const noexcept override;
	private:
		static std::string GenerateUID_(const std::string& tag);
	protected:
		std::string tag;
		UINT count;
		Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
	};
}