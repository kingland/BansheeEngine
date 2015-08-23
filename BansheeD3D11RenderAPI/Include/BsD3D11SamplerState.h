#pragma once

#include "BsD3D11Prerequisites.h"
#include "BsSamplerState.h"

namespace BansheeEngine
{
	/**
	 * @brief	DirectX 11 implementation of a sampler state. Wraps a DX11
	 *			sampler state object.
	 */
	class BS_D3D11_EXPORT D3D11SamplerStateCore : public SamplerStateCore
	{
	public:
		~D3D11SamplerStateCore();
		ID3D11SamplerState* getInternal() const { return mSamplerState; }

	protected:
		friend class D3D11RenderStateCoreManager;

		D3D11SamplerStateCore(const SAMPLER_STATE_DESC& desc);

		/**
		 * @copydoc SamplerStateCore::createInternal
		 */
		void createInternal() override;

		ID3D11SamplerState* mSamplerState;
	};
}