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
	void initTopButton();

	// 初始化所有布局的信息，
	void initAllLayout();
	// 设置所有的布局信息
	void setAllLayout();

	// 初始化左下角的那关于窗口信息的Layout
	void initLeftButtomWindowLayout();

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


	QHBoxLayout* m_LeftButtomLayout{}; // 左下角的Layout


	QGridLayout* m_LeftButtomWindowGridLayout{}; // 左下角窗口相关的的Layout 

	QPushButton* m_IconButton{}; // 瞄准的图标,其实我也不知道这个怎么实现的。。

	QLineEdit* m_WindowHandleLineEdit{}; // 窗口句柄
	QLineEdit* m_WindowTitleLineEdit{}; // 窗口标签
	QLineEdit* m_WindowPosLineEdit{}; // 窗口位置
	QPushButton* m_FlushButton{}; // 刷新Button


	
	
	
	
	

};
