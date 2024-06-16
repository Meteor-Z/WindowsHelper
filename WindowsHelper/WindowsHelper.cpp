#include "WindowsHelper.h"
#include <QHBoxLayout>
#include <qpushbutton.h>
#include <Windows.h>

WindowsHelper::WindowsHelper(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    setWindowTitle(tr("WindowsHelper"));

    m_CentralWidget = ui.centralWidget;

    m_MainLayout = new QVBoxLayout(m_CentralWidget);
    m_ButtonLayout = new QHBoxLayout(m_CentralWidget);
    m_FrameSpyButton = new QPushButton(tr("窗口Spy"));
    m_FramProcessManagementButton = new QPushButton(tr("进程管理"));
    
    initMainWidget();
    setInitFrameButton();

    connect(m_FrameSpyButton, &QPushButton::clicked, this, [&]() {
        m_StackedWidget->setCurrentIndex(0);
        });
    connect(m_FramProcessManagementButton, &QPushButton::clicked, this, [&]() {
        m_StackedWidget->setCurrentIndex(1);
        });
    
    m_CentralWidget->setLayout(m_MainLayout); // 设置主布局
}

WindowsHelper::~WindowsHelper()
{}


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
