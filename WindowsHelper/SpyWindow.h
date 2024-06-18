#pragma once

#include <QWidget>
#include <qtreewidget.h>
#include "ui_SpyWindow.h"
#include "QHBoxLayout"

// 主窗口中的小窗口
class SpyWindow : public QWidget
{
	Q_OBJECT

public:
	SpyWindow(QWidget *parent = nullptr);
	~SpyWindow();

protected:
	void paintEvent(QPaintEvent* e) override;

private:
	Ui::SpyWindowClass ui;
	QTreeWidget* m_WindowTree{}; // 窗口的Tree
	QHBoxLayout* m_MainLayout{}; // 左右布局

};
