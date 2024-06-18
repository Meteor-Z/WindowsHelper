#pragma once

#include <QWidget>
#include <qtreewidget.h>
#include "ui_SpyWindow.h"
#include "QHBoxLayout"

// �������е�С����
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
	QTreeWidget* m_WindowTree{}; // ���ڵ�Tree
	QHBoxLayout* m_MainLayout{}; // ���Ҳ���

};
