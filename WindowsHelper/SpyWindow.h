#pragma once

// VS窗口乱码问题的解决
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")// 该指令仅支持VS环境
#endif

#include <Windows.h>
#include <QWidget>
#include <QPushButton>
#include <QTreeWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <qTableWidget>
#include <QStringList>
#include <QMouseEvent>
#include "ui_SpyWindow.h"


// 主窗口中的小窗口
class SpyWindow : public QWidget
{
	Q_OBJECT

public:
	SpyWindow(QWidget *parent = nullptr);
	~SpyWindow();

protected:
// 重写此方法，主要是图层的遍历
	void paintEvent(QPaintEvent* e) override;
private:
	// 最上层的一系列信息
	void initTopButton();

	// 初始化所有布局的信息，
	void initAllLayout();
	// 设置所有的布局信息
	void setAllLayout();

	// 初始化左下角的那关于窗口信息的Layout
	void initLeftButtomWindowLayout();

	// 初始化窗口属性的哪一行
	void initAttributesLayout();

	// 初始化功能区
	void initFunctionLayout();

	// 初始化表格
	void initTableWidget();

	// 设置所有Button的样式
	void setAllButtonStyle();
	
	// 设置所有CheckBox的样式 
	void setAllCheckBoxSytle();

	// 设置所有的信号槽
	void setAllSingalSlot();

	// 在TableWidget里面添加标题
	void addTitleRow(const QString& title);


	// 添加信息，不过后期可以直接从文件中读取
	void addRow(const QStringList& data);


	// 信号槽，改变当前的鼠标样式
	void changeCursor();


	// 回复鼠标的样式，并且存储当前窗口的句柄
	void restoreCursor();

	// 通过当前点来设置坐标
	void setWindowHandleByPoint(const QPoint& pos);

	// 全局的事件过滤器
	bool eventFilter(QObject* obj, QEvent* event) override;

	// 更新窗口信息的消息
	void updateHwndInfo();

	// 判断窗口是否置顶
	bool isWndTopMost(HWND hwnd);

private:
	Ui::SpyWindowClass ui;
	QTreeWidget* m_WindowTree{}; // 窗口的Tree
	QVBoxLayout* m_MainLayout{}; // 上下布局的主布局
	
	QHBoxLayout* m_TopLayout{}; // 上面按钮的布局
	QHBoxLayout* m_ButtomLayout{}; // 下面左右的Layout

	QPushButton* m_BasicInfoButton{};// 基本信息
	QPushButton* m_CommonOperationsButton{}; // 常用操作
	QLabel* m_FindWindowlabel{}; // 查看窗口
	QLineEdit* m_FindWindowLineEdit{}; // 输入框，查找


	QVBoxLayout* m_LeftButtomLayout{}; // 左下角的Layout


	QGridLayout* m_LeftButtomWindowGridLayout{}; // 左下角窗口相关的的Layout 

	QPushButton* m_ShootButton{}; // 瞄准的图标,其实我也不知道这个怎么实现的。。
	bool m_ShootButtonIsPress{false}; // 是否已经按下了

	QLineEdit* m_WindowHandleLineEdit{}; // 窗口句柄
	QLineEdit* m_WindowTitleLineEdit{}; // 窗口标签
	QLineEdit* m_WindowPosLineEdit{}; // 窗口位置
	QPushButton* m_FlushButton{}; // 刷新Button

	QCheckBox* m_VisableCheckBox{}; // 可视化
	QCheckBox* m_StopMoveCheckBox{}; // 禁止
	QCheckBox* m_TopWindowCheckBox{}; // 置顶
	QCheckBox* m_TransparentCheckBox{}; // 透明

	QHBoxLayout* m_AttributesLeftLayout{}; // 靠左的属性Buttom

	QGridLayout* m_FunctionGridLayout{}; // 左下角功能区的布局

	QLineEdit* m_TopLevelLineEdit{}; // 顶级窗口
	QPushButton* m_TopLevelPushButton{}; // 探测顶级窗口

	QLineEdit* m_ParentLineEdit{}; // 父窗口
	QPushButton* m_ParentPushButton{}; // 探测父窗口

	QLineEdit* m_PreviewLineEdit{}; // 上一窗口
	QPushButton* m_PreviewPushButton{}; // 探测上一个窗口

	QLineEdit* m_NextLineEdit{}; // 下一窗口
	QPushButton* m_NextPushButton{}; // 探测下一个窗口

	QLineEdit* m_ProgramPathLineEdit{}; // 程序路径
	QPushButton* m_ProgramPathPushButton{}; // 打开程序路径

	QTableWidget* m_InfoTableWidget{}; // 表格，显示窗口信息

	HWND m_CurrentWindowHandle{}; // 当前的句柄，也就是当前用鼠标指出来的句柄



	
	
	
	
	

};
