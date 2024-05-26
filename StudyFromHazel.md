### 引擎的总架构

![image-20240511164900264](C:\Users\26041\AppData\Roaming\Typora\typora-user-images\image-20240511164900264.png)



#### 事件系统Event

类图

![image-20240512232809372](C:\Users\26041\AppData\Roaming\Typora\typora-user-images\image-20240512232809372.png)

#### 窗口Window

![image-20240526013838305](C:\Users\26041\AppData\Roaming\Typora\typora-user-images\image-20240526013838305.png)

**抽象与接口设计**:

定义了一个纯虚类 `Window`，作为窗口系统的抽象基类，提供统一的接口。使用纯虚函数确保所有继承自 `Window` 的具体窗口类都必须实现这些接口方法。

**事件处理与回调机制**:

定义 `EventCallbackFn` 类型，使用 `std::function<void(Event&)>` 实现灵活的事件回调机制。

**绑定用户指针(glfwSetWindowUserPointer(m_Window, &m_Data))的必要性**

1. **访问更多数据**:
   - 如果你的回调函数需要访问窗口相关的其他数据（例如标题、是否启用了 VSync 等），使用用户指针会更加方便。
2. **复杂的逻辑**:
   - 如果你的应用程序逻辑变得更加复杂，可能需要在回调中访问或修改更多数据。将数据结构与窗口关联起来，可以让回调函数更轻松地访问这些数据。
3. **统一管理**:
   - 在一个大型项目中，将与窗口相关的数据集中在一个结构体中进行管理，能够提高代码的组织性和可维护性。

##### 回调机制*

在Windows系统下，当我们对窗口做出反应时，glfwPollEvents会从操作系统队列中获取事件，并将它们分派给相应的回调函数，调用已经注册的回调函数（通过glfwSetWindowCloseCallback等注册），在回调函数里先创建一个事件（Event），通过m_Data中的EventCallbackFn传递给Application中的OnEvent函数，在OnEvent中的处理事件。

**`std::bind`**: `std::bind` 创建一个绑定的函数对象，将 `Application::OnEvent` 与当前的 `Application` 实例 (`this`) 绑定，并将事件参数 `_1` 传递给它。这允许 `OnEvent` 在回调时正确地访问 `Application` 实例。

### vs 项目构建知识

##### 预编译头（precompiled header）

预编译头是程序设计时把头文件编译为中间格式（如目标文件），以节约在开发过程中编译器反复编译该头文件的开销。zpch.h需要添加到每一个cpp文件中

##### 依赖项（dependencies）

最大好处就是依赖编译, 会先编译依赖的工程，同时会自动link依赖工程生成的lib文件

##### 运行时库（running library）

**MT选项：链接LIB版的C和C++运行库。在链接时就会在将C和C++运行时库集成到程序中成为程序中的代码，程序体积会变大。**
**MTd选项：LIB的调试版。**
**MD选项：使用DLL版的C和C++运行库，这样在程序运行时会动态的加载对应的DLL，程序体积会减小，缺点是在系统没有对应DLL时程序无法运行。**
**MDd选项：表示使用DLL的调试版。**

设置GLFW为MTD才不会报错： unresolved external symbol 。 静态库不能选MDd? Cherno为什么可以？

### 常见错误及其解决方法：

Error	LNK2001	unresolved external symbol "private: static class std::shared_ptr<class spdlog::logger> Zao::Log::s_CoreLogger" (?s_CoreLogger@Log@Zao@@0V?$shared_ptr@Vlogger@spdlog@@@std@@A)	Zao	D:\Github\Zao\Zao\Log.obj	1	

Log.h中声明的成员变量没有在Log.cpp中声明	



程序运行相当于把entrypoint复制到Sandbox中运行,所以如果entrypoint不在Zao.h的最下边，可能报错：找不到定义的参数。



LINK : fatal error LNK1104: cannot open file 'D:\Github\Zao\bin\Debug-windows-x86_64\Zao\Zao.lib' 当Zao项目报错是无法正常生成目标文件，在以后Sandox链接时出现的错误.   别让Zao报错就好。



glfw.lib(context.obj) : error lnk2001: unresolved external symbol "__imp__"wassert  如果函数声明增加了__declspec(dllimport) ，

链接的时候函数名会加上"__imp__"前缀，所以如果链接静态库， 函数的声明不用增加"declspec(dllimport)" 。如果链接动态库，再增加"__declspec(dllimport)"。



