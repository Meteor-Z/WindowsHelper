#pragma once

// VS窗口乱码问题的解决
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8") // 该指令仅支持VS环境
#endif

#include <Windows.h>
#include <QVector>
#include <QVariantMap>


struct BasicInfo {
    QString key{}; // 属性值
    QString comment{}; // 备注
    
};

struct StyleInfo {
    QString key{}; // 属性值
    DWORD style{}; // 对应的DWORD, 如 WM_SIZE
    QString commnet{}; // 对应的注释
};

// 这个是类样式
static const QVector<StyleInfo> ClassInfoVec{
    {"CS_BYTEALIGNCLIENT", CS_BYTEALIGNCLIENT, "对齐窗口的字节边界上的客户区"},
    {"CS_BYTEALIGNWINDOW", CS_BYTEALIGNWINDOW, "对齐字节边界上的窗口"},
    {"CS_CLASSDC", CS_CLASSDC, "分配一个设备上下文共享在类的所有窗口"},
    {"CS_DBLCLKS", CS_DBLCLKS, "当用户双击鼠标时向窗口程序发送一个双击"},
    {"CS_GLOBALCLASS", CS_GLOBALCLASS, "指定窗口类是一个应用程序全局类"},
    {"CS_HREDRAW", CS_HREDRAW, "若移动或改变了窗口宽度，则刷新整个窗口"},
    {"CS_IME", CS_IME, "输入法窗口"},
    {"CS_NOCLOSE", CS_NOCLOSE, "禁止系统菜单上的关闭命令"},
    {"CS_OWNDC", CS_OWNDC, "为该类中每个窗口分配一个单独的设备描述表"},
    {"CS_PARENTDC", CS_PARENTDC, "在父窗口中定义一个子窗口的剪切区，以便于重绘"},
    {"CS_SAVEBITS", CS_SAVEBITS, "在一个窗口中保存屏幕图像，以便于该窗口被删除或覆盖"},
    {"CS_VREDRAW", CS_VREDRAW, "若移动或改变了窗口高度，则刷新整个窗口"}
};

// 窗口样式
static const QVector<StyleInfo> WMInfoVec{
    { "WS_POPUP", WS_POPUP, "弹出式窗口(不能与WS_CHTLDWIHDOW"},
    {"WS_CHILDWINDOW",WS_CHILDWINDOW, "子窗口(不能与WS_FOPUP合用)"},
    {"WS_MIHIMIZE", WS_MINIMIZE, "最小化状态"},
    {"WS_VISIBLE",WS_VISIBLE, "可见状态"},
    {"WS_DISABLED", WS_DISABLED,"不可用状态"},
    {"WS_CLIPSIBLIHGS", WS_CLIPSIBLINGS,"使窗口排除子窗口之间的相对区域"},
    {"WS_CLIPCHILDREN", WS_CLIPCHILDREN,"当在父窗口内绘图时,排除子窗口区域"},
    {"WS_MAXIMIZE", WS_MAXIMIZE,"具有最大化按钮,须指定WS_SYSTEM样式"},
    {"WS_CAPTION", WS_CAPTION,"有标题框和边框(和WS_TILED样式相同)"},
    {"WS_BORDER", WS_BORDER,"有单边框"},
    {"WS_DLGFRAME", WS_DLGFRAME,"带对话框边框样式,不带标题框"},
    {"WS_VSCROLL",WS_VSCROLL, "有垂直滚动条"},
    {"WS_HSCROLL", WS_HSCROLL, "有水平滚动条"},
    {"WS_SYSMENU", WS_SYSMENU, "标题框上带有窗口菜单(须指定WS_CAPTI"},
    {"WS_THICKFRAME", WS_THICKFRAME, "有可调边框(与WS_SIZEBOX样式相同)"},
    {"WS_GROUP", WS_GROUP, "组样式,每个组的第一个控件具有WS_TABS"},
    {"WS_TABSTOP",WS_TABSTOP,"可接受TAB键焦点"},
    {"WS_MINIMIZEBOX",WS_MINIMIZEBOX,"有最小化按钮"},
    {"WS_MAXIMIZEBOX",WS_MAXIMIZEBOX,"有最大化按钮"},
    {"WS_OVERLAPPEDWINDOW",WS_OVERLAPPEDWINDOW, "具有层叠,标题框,系统菜单,可调边框,系"},
    {"WS_POPUPWINDOW", WS_POPUPWINDOW, "具有单边框,弹出式,系统菜单样式"},
};

// 扩展样式
static const QVector<StyleInfo> WMExtraInfoVec{
    {"WS_EX_DLGMODALFRAME", WS_EX_DLGMODALFRAME, "带双层边框"},
    {"WS_EX_NOPARENTNOTIFY", WS_EX_NOPARENTNOTIFY, "创建 / 销毁时不通知父窗口"},
    {"WS_EX_TOPMOST", WS_EX_TOPMOST, "窗口置顶(停留在所有非最高层窗口的上面)"},
    {"WS_EX_ACCEPTFILES", WS_EX_ACCEPTFILES, "可接受文件拖放"},
    {"WS_EX_TRANSPARENT", WS_EX_TRANSPARENT, "透明样式,在同属窗口已重画时该窗口才可重画"},
    {"WS_EX_MDICHILD", WS_EX_MDICHILD, "MI子窗口样式"},
    {"WS_EX_TOOLWINDOW", WS_EX_TOOLWINDOW, "工具条窗口样式"},
    {"WS_EX_WINDOWEDGE", WS_EX_WINDOWEDGE, "带凸起边缘的边框"},
    {"WS_EX_CLIENTEDGE", WS_EX_CLIENTEDGE, "带阴影约的边缘"},
    {"WS_EX_CONTEXTHELP", WS_EX_CONTEXTHELP, "有上下文帮助样式,标题栏包含一个问号标志"},
    {"WS_EX_RIGHT", WS_EX_RIGHT, "右对齐"},
    {"WS_EX_RTLREADING", WS_EX_RTLREADING, "窗口文本从右到左显示"},
    {"WS_EX_LEFTSCROLLBAR", WS_EX_LEFTSCROLLBAR, "垂直滚动条在窗口左边界"},
    {"WS_EX_CONTROLPARENT", WS_EX_CONTROLPARENT, "允许用户使用TAB键在窗口的子窗口间切换"},
    {"WS_EX_STATICEDGE", WS_EX_STATICEDGE, "当窗口为不可用状态时创建一个三维边缘"},
    {"WS_EX_APPWINDOW", WS_EX_APPWINDOW, "当窗口可见时将一个顶层窗口放置在任务栏上"},
    {"WS_EX_OVERLAPPEDWINDOW", WS_EX_OVERLAPPEDWINDOW, "带凸起边缘的边框，边缘有阴影多"},
    {"WS_EX_PALETTEWINDOW", WS_EX_PALETTEWINDOW, "带立体边框,有工具条窗口样式,窗口在顶层"},
    {"WS_EX_LAYERED", WS_EX_LAYERED, "分层或透明窗口,该样式可使用混合特效"},
    {"WS_EX_NOINHERITLAYOUT", WS_EX_NOINHERITLAYOUT, "子控件不继承窗体或控件的布局"},
    {"WS_EX_LAYOUTRTL", WS_EX_LAYOUTRTL, "窗体或控件将具有从右向左的布局(因而会被镜像)"},
    {"WS_EX_COMPOSITED", WS_EX_COMPOSITED, "用双缓冲从下到上绘制窗口的所有子孙"},
    {"WS_EX_NOACTIVATE", WS_EX_NOACTIVATE, "处于顶层但不激活"}
};
