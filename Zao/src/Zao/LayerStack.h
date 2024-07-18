#pragma once
#include "Layer.h"

namespace Zao {

	class ZAO_API LayerStack {
	public:
		LayerStack()
			:m_LayerStackIndex(0) {}

		virtual ~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* layer);
		void PopLayer(Layer* layer);
		void PopOverLay(Layer* layer);

		inline std::vector<Layer*>::iterator Begin() { return m_LayerStack.begin(); }
		inline std::vector<Layer*>::iterator End() { return m_LayerStack.end(); }
	private:
		std::vector<Layer*> m_LayerStack;
		unsigned int m_LayerStackIndex;
	};


}