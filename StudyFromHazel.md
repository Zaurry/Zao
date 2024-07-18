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



#### 图层Layer

事件从上往下传给每一层，只要有一个layer消费掉了event，该事件就不在往下传递了。

##### Layer 类

`Layer` 类表示游戏引擎中的一个层。层用于将引擎中的不同功能或组件分离，比如渲染、UI、输入处理等。虚函数允许派生类定义具体的行为，例如当层被附加/分离、每帧更新或收到事件时执行的操作。

##### LayerStack 类

`LayerStack` 类管理多个层，允许灵活地添加、移除和遍历层。这对于动态管理不同组件及其交互非常重要。层可以堆叠在一起，具有推入/弹出常规层和覆盖层的能力。

- **PushLayer/PushOverlay**：将新层或覆盖层添加到栈中。
- **PopLayer/PopOverlay**：从栈中移除特定层或覆盖层。
- **Begin/End**：提供遍历层的迭代器，便于按顺序更新或渲染所有层。

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

在premake中增加buildoption使项目建立时重写运行时库。这种方法只能编译时重写运行时库，而不是直接设置运行时库。

##### 传递函数

`std::function` 提供了更高级别的抽象，适用于更广泛的用例，而 `void (*function)()` 则更轻量级，适用于特定的情况。



### 常见错误及其解决方法：

```
Error	LNK2001	unresolved external symbol "private: static class std::shared_ptr<class spdlog::logger> Zao::Log::s_CoreLogger" (?s_CoreLogger@Log@Zao@@0V?$shared_ptr@Vlogger@spdlog@@@std@@A)	Zao	D:\Github\Zao\Zao\Log.obj	1	
```

Log.h中声明的成员变量没有在Log.cpp中声明	



程序运行相当于把entrypoint复制到Sandbox中运行,所以如果entrypoint不在Zao.h的最下边，可能报错：找不到定义的参数。



```
LINK : fatal error LNK1104: cannot open file 'D:\Github\Zao\bin\Debug-windows-x86_64\Zao\Zao.lib'
```

 当Zao项目报错是无法正常生成目标文件，在以后Sandox链接时出现的错误.   别让Zao报错就好。



```
glfw.lib(context.obj) : error lnk2001: unresolved external symbol "__imp__"wassert
```

  如果函数声明增加了__declspec(dllimport) ，链接的时候函数名会加上"__imp__"前缀，所以如果链接静态库， 函数的声明不用增加"declspec(dllimport)" 。如果链接动态库，再增加"__declspec(dllimport)"。



```
Severity	Code	Description	Project	File	Line	Suppression State	Details

Error	C2360	initialization of 'e' is skipped by 'case' label	Zao	D:\Github\Zao\Zao\src\Platform\WindowsWindow.cpp	63
```

The initialization of identifier can be skipped in a switch statement. You cannot jump past a declaration with an initializer unless the declaration is enclosed in a block. (Unless it is declared within a block, the variable is within scope until the end of the switch statement.

可以在 switch 语句中跳过 的 identifier 初始化。除非声明包含在块中，否则无法跳过具有初始值设定项的声明。（除非在块中声明，否则该变量在 switch 语句结束之前都在范围内。



在Sandbox程序中找不到Event等在Zao里的类，他妈的指名命名空间(namespace)啊，操了。



```
跨模块内存管理 ‘__acrt_first_block == header’异常
```

![image-20240609002009910](C:\Users\26041\AppData\Roaming\Typora\typora-user-images\image-20240609002009910.png)

在完成Layer以后，发生多个事件就报错。

1、解决方案各项目优先使用默认的MD方式链接运行库，可以减少跨模块内存管理出现问题；
2、如果非用MT方式不可，则可使用全局变量或一次性分配最大内存来避免跨模块内存管理异常；

详细解释:https://blog.csdn.net/u010634308/article/details/108241520





