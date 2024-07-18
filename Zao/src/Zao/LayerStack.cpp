#include "zpch.h"
#include "LayerStack.h"

namespace Zao {
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_LayerStack) {
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer) {
			m_LayerStack.emplace(m_LayerStack.begin() + m_LayerStackIndex, layer);
			m_LayerStackIndex++;
	}

	void LayerStack::PushOverLay(Layer* layer) {
			m_LayerStack.emplace_back(layer);
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_LayerStack.begin(), m_LayerStack.end(), layer);
		if (it != m_LayerStack.end()) {
			m_LayerStack.erase(it);
			m_LayerStackIndex--;
		}
	}

	void LayerStack::PopOverLay(Layer* layer) {
		auto it = std::find(m_LayerStack.begin(), m_LayerStack.end(), layer);
		if (it != m_LayerStack.end()) {
			m_LayerStack.erase(it);
		}
	}
}
