#include "MessageWindow.h"
#include <QHboxLayout>
#include <QTableWidget>
#include <thread>
#include "Hook.h"

MessageWindow::MessageWindow(QWidget *parent, HWND hCaptureWnd)
    : QWidget(parent) {
    ui.setupUi(this);
    QHBoxLayout* tempLayout = new QHBoxLayout(this);
    m_ListWidget = new QListWidget(this);
    tempLayout->addWidget(m_ListWidget);
    initStyle();
    resize(1300, 800);
    setTextEdit();
    m_hCaptureHwnd = hCaptureWnd;

    InstallCBTHook((HWND)this->winId());
    InstallCallWndProcHook((HWND)this->winId(), hCaptureWnd);

    InstallGetMessageHook((HWND)this->winId(), hCaptureWnd);
}

MessageWindow::~MessageWindow() {
}

bool MessageWindow::nativeEvent(const QByteArray& eventType, void* message, long* result) {
    if (eventType == "windows_generic_MSG") {
        MSG* msg = static_cast<MSG*>(message);
        if (msg->message == WM_NotifyCallWndProc || msg->message == WM_NotifyGetMessage) {
            QString msgContent = QString("Received WM_NOTIFY_CALLWNDPROC: hwnd=%1, message=%2")
                .arg(reinterpret_cast<int>(msg->hwnd))
                .arg(msg->lParam);
            m_ListWidget->addItem(new QListWidgetItem(msgContent));
            return true;
        }
    }
    return QWidget::nativeEvent(eventType, message, result);
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
