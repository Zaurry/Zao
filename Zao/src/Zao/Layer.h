#pragma once
#include "Zao/Event/Event.h"

namespace Zao {

	class ZAO_API Layer {
	public:
		Layer(const std::string& DebugName = "layer");
		virtual ~Layer() {}

		virtual void OnAttach() {} // Called when layer is pushed onto the stack
		virtual void OnDetach() {} // Called when layer is popped off the stack
		virtual void OnEvent(Event& event) {}
		virtual void OnUpdate() {}
	protected:
		const std::string& m_DebugName;
	};


}