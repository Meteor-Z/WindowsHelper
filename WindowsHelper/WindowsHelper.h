#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_WindowsHelper.h"

class WindowsHelper : public QMainWindow
{
    Q_OBJECT

public:
    WindowsHelper(QWidget *parent = nullptr);
    ~WindowsHelper();

private:
    Ui::WindowsHelperClass ui;
};
