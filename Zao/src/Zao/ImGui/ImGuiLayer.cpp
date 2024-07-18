#include "zpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/Opengl/imguiOpenglRenderer.h"

#include "Zao/Application.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

//#define BUILD_ENABLE_DEBUG

namespace Zao {
	ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer") {}

	void ImGuiLayer::OnAttach() {
		// Setup Dear ImGui context
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// 在初始化 ImGui 的时候设置键映射
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;


		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		// Setup Platform/Renderer backends
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnEvent(Event& event) {
		#ifdef BUILD_ENABLE_DEBUG
		ZAO_CORE_TRACE("Imgui: {0}", event.ToString());
		#endif

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(ZAO_BIND_EVENT_FN(ImGuiLayer::MouseButtionPressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(ZAO_BIND_EVENT_FN(ImGuiLayer::MouseButtionReleased));
		dispatcher.Dispatch<KeyPressedEvent>(ZAO_BIND_EVENT_FN(ImGuiLayer::KeyPressed));
		dispatcher.Dispatch<KeyReleasedEvent>(ZAO_BIND_EVENT_FN(ImGuiLayer::KeyReleased));
		dispatcher.Dispatch<KeyTypedEvent>(ZAO_BIND_EVENT_FN(ImGuiLayer::KeyTyped));
		dispatcher.Dispatch<MouseScrolledEvent>(ZAO_BIND_EVENT_FN(ImGuiLayer::MouseScrolled));
		dispatcher.Dispatch<MouseMovedEvent>(ZAO_BIND_EVENT_FN(ImGuiLayer::MouseMoved));
		dispatcher.Dispatch<WindowResizeEvent>(ZAO_BIND_EVENT_FN(ImGuiLayer::WindowResize));
	}

	void ImGuiLayer::OnUpdate() {
		ImGuiIO& io = ImGui::GetIO();

		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;


		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		ImGui::Begin("Text input");
		ImGui::InputText("input", m_Buffer, 1024);

		ImGui::End();


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	bool ImGuiLayer::MouseButtionPressed(MouseButtonPressedEvent& e) {
		int button = e.GetMouseButton();
		ImGuiIO& io = ImGui::GetIO();
		if (button >= 0 && button < 3)
			io.MouseDown[button] = true;

		return false;

	}

	bool ImGuiLayer::MouseButtionReleased(MouseButtonReleasedEvent& e) {
		int button = e.GetMouseButton();
		ImGuiIO& io = ImGui::GetIO();
		if (button >= 0 && button < 3)
			io.MouseDown[button] = false;

		return false;
	}

	bool ImGuiLayer::KeyPressed(KeyPressedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return false;
	}

	bool ImGuiLayer::KeyReleased(KeyReleasedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return false;
	}

	bool ImGuiLayer::KeyTyped(KeyTypedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter(e.GetKeyCode());
		return false;
	}
	

	bool ImGuiLayer::MouseScrolled(MouseScrolledEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();
		return false;
	}

	bool ImGuiLayer::MouseMoved(MouseMovedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());
		return false;
	}

	bool ImGuiLayer::WindowResize(WindowResizeEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight()); //设置显示大小
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f); //作用是使得在高DPI显示器上显示正常？
		glViewport(0, 0, e.GetWidth(), e.GetHeight()); //设置视口大小
		return false;
	}

}