#include "MessageWindow.h"
#include <QHboxLayout>
#include <QTableWidget>

MessageWindow::MessageWindow(QWidget *parent, HWND hwnd)
    : QWidget(parent), m_CurrentWindowHandler(hwnd) {
    ui.setupUi(this);
    QHBoxLayout* tempLayout = new QHBoxLayout(this);
    m_TableWidget = new QTableWidget(this);
    tempLayout->addWidget(m_TableWidget);
    initStyle();
    resize(1300, 800);
    setTextEdit();
    
    
}

MessageWindow::~MessageWindow() {
}


void MessageWindow::initStyle() {
    m_TableWidget->setRowCount(1);  // 设置行数
    m_TableWidget->setColumnCount(1);  // 设置列数

    // 添加一行文字
    m_TableWidget->setItem(0, 0, new QTableWidgetItem("This is a single line of text"));

}

void MessageWindow::setTextEdit() {
    for (int i = 0; i < 100; i++) {
        m_TableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1 行").arg(i)));
    }
}

bool MessageWindow::injectDLLByHwnd(HWND hwnd, const QString& dllPath) {
    // 不会。，呜呜呜
    return true;
}
