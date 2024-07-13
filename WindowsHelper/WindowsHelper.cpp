#include "WindowsHelper.h"
#include <QHBoxLayout>
#include <qpushbutton.h>
#include <QMessageBox>
#include <Windows.h>
#include <QTextEdit>

WindowsHelper::WindowsHelper(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    initAllMenu();
    setWindowIcon(QIcon("image/logo.jpg"));
    setWindowTitle(tr("WindowsHelper"));
    // 设置初始值大小，
    resize(1700, 1300);

    m_CentralWidget = ui.centralWidget;

    m_MainLayout = new QVBoxLayout(m_CentralWidget);
    m_ButtonLayout = new QHBoxLayout();
    m_FrameSpyButton = new QPushButton(tr("窗口Spyxx"));
    m_FramProcessManagementButton = new QPushButton(tr("进程管理"));
    
    setInitFrameButton();
    initMainWidget();

    connect(m_FrameSpyButton, &QPushButton::clicked, this, [&]() {
        m_StackedWidget->setCurrentIndex(0);
        //SpyWindow* temp = static_cast<SpyWindow*>(m_StackedWidget->currentWidget());
        //temp->show();
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
    m_ProcessWindowWidget = new ProcessWindow();

    m_StackedWidget->addWidget(m_SpyWindowWidget);
    m_StackedWidget->addWidget(m_ProcessWindowWidget);

    m_MainLayout->addLayout(m_ButtonLayout);
    m_MainLayout->addWidget(m_StackedWidget);
    
}

void WindowsHelper::initAllMenu() {
    m_MenuBar = new QMenuBar(this);
    setMenuBar(m_MenuBar);

    QAction* aboutAction = new QAction("关于", this);
    m_MenuBar->addAction(aboutAction);

    // 点击显示对应的
    connect(aboutAction, &QAction::triggered, this, []() {
        QDialog* dialog = new QDialog();
        QVBoxLayout* layout = new QVBoxLayout(dialog);

        QLabel* githubLabel = new QLabel(dialog);
        githubLabel->setText("项目地址：<a href=\"https://github.com/Meteor-Z/WindowsHelper\"> https://github.com/Meteor-Z/WindowsHelper</a>");

        // 启用交互式链接
        githubLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
        githubLabel->setOpenExternalLinks(true);

        QLabel* userLable = new QLabel(dialog);
        userLable->setText("作者：<a href=\"https://github.com/Meteor-Z\"> Meteor-Z</a>");

        // 启用交互式链接
        userLable->setTextInteractionFlags(Qt::TextBrowserInteraction);
        userLable->setOpenExternalLinks(true);
        QLabel* otherlLabel = new QLabel("本软件开源，欢迎交流issuse/Bug", dialog);

        layout->addWidget(githubLabel);
        layout->addWidget(userLable);
        layout->addWidget(otherlLabel);
        QSize size = layout->sizeHint();
        dialog->setFixedSize(size);
        dialog->exec();
        });
    
}
