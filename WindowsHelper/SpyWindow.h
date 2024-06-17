#pragma once

#include <QWidget>
#include "ui_SpyWindow.h"

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
};
