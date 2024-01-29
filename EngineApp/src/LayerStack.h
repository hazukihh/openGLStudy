#pragma once

#include "PCH.h"
#include "Layer.h"
namespace Engine
{
	class LayerStack
	{
	private:
		std::vector<Layer*> m_LayerStack;
		//std::vector<Layer*>::iterator m_LayerInsertIt;
		unsigned int m_LayerInsertIndex = 0;

	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_LayerStack.begin(); }
		std::vector<Layer*>::iterator end() { return m_LayerStack.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_LayerStack.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_LayerStack.rend(); }

		std::vector<Layer*>::const_iterator begin() const { return m_LayerStack.begin(); }
		std::vector<Layer*>::const_iterator end()	const { return m_LayerStack.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_LayerStack.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_LayerStack.rend(); }


	};

}



