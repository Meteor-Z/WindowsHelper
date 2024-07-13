#include "MessageWindow.h"
#include <QHboxLayout>
#include <QTableWidget>
#include <Hook.h>

MessageWindow::MessageWindow(QWidget *parent, HWND hwnd)
    : QWidget(parent) {
    ui.setupUi(this);
    QHBoxLayout* tempLayout = new QHBoxLayout(this);
    m_ListWidget = new QListWidget(this);
    tempLayout->addWidget(m_ListWidget);
    initStyle();
    resize(1300, 800);
    setTextEdit();

    // 发送的窗口Hwnd
    g_hNotifyWnd = (HWND)this->winId();
    // 捕获的窗口Hwnd
    g_hCaptureWnd = hwnd;

    
    
    

    
    
}

MessageWindow::~MessageWindow() {
}


void MessageWindow::initStyle() {
}
void MessageWindow::setTextEdit() {
    for (int i = 0; i < 100; i++) {
        m_ListWidget->addItem(new QListWidgetItem(QString("%1行").arg(i)));
    }
}

bool MessageWindow::injectDLLByHwnd(HWND hwnd, const QString& dllPath) {
    // 不会。，呜呜呜
    return true;
}
