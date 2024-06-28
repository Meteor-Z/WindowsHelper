# WindowsHelper

这个是我的个人项目，很大程度是上是模仿彗星小助手和spyxx这两款软件的，因为这两个软件在我的客户端实习中帮助了我很多，当然，再次基础上，我也添加了很多功能，目前还在完善修正。

## Window API

这个是Windows相关的API，相对来说，比较重要，

- enumWindows() 遍历窗口的，通过将句柄传递给每一个窗口，进而将应用程序定义的回调函数，枚举屏幕上的所有顶级窗口，


## Spyxx捕捉消息

这个还是比较重要的，主要使用的是DLL注入的技术，不过有点恶心的是：32位的程序只能监控32位的dll信息，64位的程序也是只能监视64位的dll信息，

```cpp
HHOOK SetWindowsHookEx(
  int       idHook, // 当前挂钩的类型
  HOOKPROC  lpfn, // 钩子函数的指针
  HINSTANCE hmod, // 包含钩子函数的DLL模块的句柄，也就是Handle
  DWORD     dwThreadId // 安装到钩子函数中的哪一个线程的标识符
);
```

我的理解是：SetWindowHookEx是一个钩子函数，设置回调函数然后处理，其实是监控本程序的，然后将SetWindowsHookEx通过DLL注入，注入到某一个程序中，然后就可以直接通过钩子函数获取相关事件，然后再将消息返回回来

## Bug & Feature

- 按钮的提示移动到那里的时候比较慢，反应速度不是很快
- 样式还是需要改进
- 增加一个能看相关信息的，然后这个信息能够进行过滤
- VS中请安装插件 Force UIF-8(with Bom)版本的插件，要不然编码格式有很大的的问题，出现乱码
  - Chinese may be garbled
  - VS, please install the plug-in Force UIF-8 (with Bom) version of the plug-in, otherwise the encoding format has a big problem, appear messy code!
- 相关信息的属性还需要调整，因为有点大，样式不是很好看
- 全是红色全是绿色好难看，这个后期可以进行优化
- 打开文件的时候，应该是高亮，而不是直接到这个文件夹里面，
- 左边编辑的时候，也应该是能复制，但是不能编辑
- 图标有黑边，感觉还可以进行改进一下

有任何Bug，或者改进的地方，都可以直接联系我：QQ：3030218083

## 相关资料

- [Spxx是如何工作的]("https://www.codeproject.com/Articles/1698/MS-Spy-style-Window-Finder")
- [MyLiteSpy]("https://github.com/yinkaisheng/MyLiteSpy/tree/master") 其中的DLL很多都是借鉴于此，教我怎么进行Hook代码的。
