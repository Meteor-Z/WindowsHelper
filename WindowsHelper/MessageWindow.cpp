#include "MessageWindow.h"
#include <QHboxLayout>

MessageWindow::MessageWindow(QWidget *parent, HWND hwnd)
    : QWidget(parent), m_CurrentWindowHandler(hwnd) {
    ui.setupUi(this);
    QHBoxLayout* tempLayout = new QHBoxLayout(this);
    m_textEdit = new QTextEdit(this);
    tempLayout->addWidget(m_textEdit);

    resize(1300, 800);
    setTextEdit();
    
    
}

MessageWindow::~MessageWindow() {
}


void MessageWindow::setTextEdit() {
    m_textEdit->setReadOnly(true);
    for (int i = 0; i < 100; i++) {
        m_textEdit->append(QString("测试：第 %1 行").arg(i));
    }
}

bool MessageWindow::injectDLLByHwnd(HWND hwnd, const QString& dllPath) {
    // 不会。，呜呜呜
    return true;
}
