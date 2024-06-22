#include "WindowsHelper.h"
#include <QHBoxLayout>
#include <qpushbutton.h>
#include <Windows.h>

WindowsHelper::WindowsHelper(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    setWindowTitle(tr("WindowsHelper"));
    // 设置初始值大小
    resize(1700, 1300);

    m_CentralWidget = ui.centralWidget;

    m_MainLayout = new QVBoxLayout(m_CentralWidget);
    m_ButtonLayout = new QHBoxLayout();
    m_FrameSpyButton = new QPushButton(tr("窗口Spy"));
    m_FramProcessManagementButton = new QPushButton(tr("进程管理"));
    
    setInitFrameButton();
    initMainWidget();

    connect(m_FrameSpyButton, &QPushButton::clicked, this, [&]() {
        m_StackedWidget->setCurrentIndex(0);
        SpyWindow* temp = static_cast<SpyWindow*>(m_StackedWidget->currentWidget());
        temp->show();
        });
    connect(m_FramProcessManagementButton, &QPushButton::clicked, this, [&]() {
        m_StackedWidget->setCurrentIndex(1);
        
        });
    
    m_CentralWidget->setLayout(m_MainLayout); // 设置主布局
}

WindowsHelper::~WindowsHelper() {
}


void WindowsHelper::setInitFrameButton() {
    m_FrameSpyButton->setFixedSize(85, 75);
    m_FramProcessManagementButton->setFixedSize(85, 75);
    m_ButtonLayout->addWidget(m_FrameSpyButton);
    m_ButtonLayout->addWidget(m_FramProcessManagementButton);
    m_ButtonLayout->addStretch(1);
    // 水平靠上
    m_ButtonLayout->setAlignment(Qt::AlignTop);
    
    

}

void WindowsHelper::initMainWidget() {
    m_StackedWidget = new QStackedWidget(m_CentralWidget);

    m_SpyWindowWidget = new SpyWindow();
    QWidget* demoWidgetTwo = new QWidget();

    demoWidgetTwo->setStyleSheet("background-color: blue;");

    m_StackedWidget->addWidget(m_SpyWindowWidget);
    m_StackedWidget->addWidget(demoWidgetTwo);

    m_MainLayout->addLayout(m_ButtonLayout);
    m_MainLayout->addWidget(m_StackedWidget);
    
}
