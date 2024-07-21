#include "MessageWindow.h"
#include <QHboxLayout>
#include <QTableWidget>
#include <string.h>
#include <atltime.h>
#include "Hook.h"
#include <windowsx.h>


static QListWidgetItem* GetQListTips(const QString& info, QColor color) {
    QListWidgetItem* item = new QListWidgetItem(info);
    item->setForeground(QBrush(QColor(color)));
    return item;
}
MessageWindow::MessageWindow(QWidget *parent, HWND hCaptureWnd)
    : QWidget(parent) {
    ui.setupUi(this);
    QHBoxLayout* tempLayout = new QHBoxLayout(this);
    m_ListWidget = new QListWidget(this);
    tempLayout->addWidget(m_ListWidget);
    initStyle();
    setTextEdit();
    resize(1300, 800);

    m_hCaptureHwnd = hCaptureWnd;

    if (InstallCBTHook((HWND)this->winId())) {
        m_ListWidget->addItem(GetQListTips("Install CBTHOOK Success", Qt::green));
    } else {
        m_ListWidget->addItem(GetQListTips("Install CBTHOOK Failed", Qt::red));
    }

    if (InstallCallWndProcHook((HWND)this->winId(), hCaptureWnd)) {
        m_ListWidget->addItem(GetQListTips("Install CallWndProcHook Success", Qt::green));
    } else {
        m_ListWidget->addItem(GetQListTips("Install CallWndProcHook Failed", Qt::red));
    }

    // 安装CallWndProc
    if (InstallCallWndProcRetHook((HWND)this->winId(), hCaptureWnd)) {
        m_ListWidget->addItem(GetQListTips("Install CallWndProcRetHook Success", Qt::green));
    } else {
        m_ListWidget->addItem(GetQListTips("Install CallWndProcRetHook Failed", Qt::red));
    }

    // 安装GetMesssage
    if (InstallGetMessageHook((HWND)this->winId(), hCaptureWnd)) {
        m_ListWidget->addItem(GetQListTips("Install GetMessageHook Success", Qt::green));
    } else {
        m_ListWidget->addItem(GetQListTips("Install GetMessageHook Failed", Qt::red));
    }
}

MessageWindow::~MessageWindow() {
}

static QString TimeToQStringTime(DWORD time) {
    CTime cTime(time);
    QString data = QString("%1-%2-%3 %4%5%6").arg(cTime.GetYear()).arg(cTime.GetMonth()).arg(cTime.GetDay())
        .arg(cTime.GetDay()).arg(cTime.GetHour()).arg(cTime.GetMinute());
    return data;
}

static QListWidgetItem* GetListWidgetItem(MSG* msg) {
    QString type = EnumToChar(msg->message);
    QString pos = QString("(%1, %2)").arg(msg->pt.x).arg(msg->pt.y);
    QString time = TimeToQStringTime(msg->time);
    // WM_XXX 这样的类型, 从lParam中获取是因为传递消息的时候是将Msg传入到了这个参数中了，
    QString msgType = QString::fromWCharArray(GetMsgStringW((UINT)msg->lParam));
    
    QString data = QString("type = %4, messageType = %1, pos = %2, time = %3").arg(msgType).arg(pos).arg(time).arg(type);
    QListWidgetItem* item = new QListWidgetItem(data);
    return item;

}

bool MessageWindow::nativeEvent(const QByteArray& eventType, void* message, long* result) {
    if (eventType == "windows_generic_MSG") {
        MSG* msg = static_cast<MSG*>(message);
        if (msg->message == WM_NotifyActivate || msg->message == WM_NotifyFocus ||
            msg->message == WM_NotifyCallWndProc || msg->message == WM_NotifyCallWndProcRet ||
            msg->message == WM_NotifyGetMessage) {
            m_ListWidget->addItem(GetListWidgetItem(msg));
            return true;
        }
    }
    return QWidget::nativeEvent(eventType, message, result);
}

void MessageWindow::closeEvent(QCloseEvent* event) {
    // 卸载相关钩子
    UninstallMessageHook();
    UninstallCallWndProcHook();
    UninstallCallWndProcRetHook();
    UninstallGetMessageHook();

    event->accept();
}

void MessageWindow::initStyle() {
}

void MessageWindow::setTextEdit() {
}



