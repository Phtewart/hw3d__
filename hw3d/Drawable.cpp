#include "Drawable.h"
#include "GFXExceptionMacros.h"
#include "IndicesBuffer.h"
#include <cassert>
#include <typeinfo>

using namespace Bind;

void Drawable::Draw(Graphics& gfx) const
{
	for (auto& b : binds)
	{
		b->Bind(gfx);
	}
	gfx.DrawIndexed(pIndexBuffer->GetCount());
}

void Drawable::AddBind(std::shared_ptr<Bindable> bind)
{
	// special case for index buffer
	if (typeid(*bind) == typeid(IndicesBuffer))
	{
		assert("Binding multiple index buffers not allowed" && pIndexBuffer == nullptr);
		pIndexBuffer = &static_cast<IndicesBuffer&>(*bind);
	}
	binds.push_back(std::move(bind));
}

