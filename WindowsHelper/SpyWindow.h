#pragma once

#include <QWidget>
#include "ui_SpyWindow.h"

// �������е�С����
class SpyWindow : public QWidget
{
	Q_OBJECT

public:
	SpyWindow(QWidget *parent = nullptr);
	~SpyWindow();

private:
	Ui::SpyWindowClass ui;
};
