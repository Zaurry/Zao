#pragma once

#include "Zao/Layer.h"
#include "Zao/Event/ApplicationEvent.h"
#include "Zao/Event/MouseEvent.h"
#include "Zao/Event/KeyEvent.h"


namespace Zao {


class ZAO_API ImGuiLayer : public Layer {
public:
	ImGuiLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnEvent(Event& event) override;
	void OnUpdate() override;
private:
	bool MouseButtionPressed(MouseButtonPressedEvent& e);
	bool MouseButtionReleased(MouseButtonReleasedEvent& e);
	bool KeyPressed(KeyPressedEvent& e);
	bool KeyReleased(KeyReleasedEvent& e);
	bool KeyTyped(KeyTypedEvent& e);
	bool MouseScrolled(MouseScrolledEvent& e);
	bool MouseMoved(MouseMovedEvent& e);
	bool WindowResize(WindowResizeEvent& e);
private:
	float m_Time = 0.0f;
	char m_Buffer[1024] = {};
};


}