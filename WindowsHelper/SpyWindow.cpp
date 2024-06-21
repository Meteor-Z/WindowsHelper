#include "SpyWindow.h"
#include <Windows.h>
#include <QStyleOption>
#include <QPainter>

SpyWindow::SpyWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

    // layout集体初始化
    initAllLayout();
   
    
    initTopButton();

    initLeftButtomWindowLayout();


	// 设置所有布局
    setAllLayout();
}

SpyWindow::~SpyWindow(){
}

void SpyWindow::paintEvent(QPaintEvent* e) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SpyWindow::initTopButton() {
    m_BasicInfoButton = new QPushButton(tr("复制基本信息"), this);
    m_CommonOperationsButton = new QPushButton(tr("常用操作"), this);
    m_FindWindowlabel = new QLabel(tr("查找窗口"), this);
    m_FindWindowLineEdit = new QLineEdit(this);
    m_TopLayout->addWidget(m_BasicInfoButton);
    m_TopLayout->addWidget(m_CommonOperationsButton);
    
    // 添加一个伸缩项，其实就是中间隔开，效果出来了就行
    m_TopLayout->addStretch();

    m_TopLayout->addWidget(m_FindWindowlabel);
    m_TopLayout->addWidget(m_FindWindowLineEdit);

   
}

void SpyWindow::initAllLayout() {
    m_MainLayout = new QVBoxLayout(this);
    m_TopLayout = new QHBoxLayout();
    m_WindowTree = new QTreeWidget();
    m_ButtomLayout = new QHBoxLayout();
    m_LeftButtomLayout = new QHBoxLayout();
    m_LeftButtomWindowGridLayout = new QGridLayout();
}

void SpyWindow::setAllLayout() {
    m_MainLayout->addLayout(m_TopLayout);
    m_ButtomLayout->addLayout(m_LeftButtomLayout);

    m_ButtomLayout->addWidget(m_WindowTree);
   
    m_LeftButtomLayout->addLayout(m_LeftButtomWindowGridLayout);
    
    // 窗口靠上
    m_LeftButtomWindowGridLayout->setAlignment(Qt::AlignTop);

    m_MainLayout->addLayout(m_ButtomLayout);

}

void SpyWindow::initLeftButtomWindowLayout() {
    m_IconButton = new QPushButton(tr("探测图片"),this);
   
    QLabel* windowHandleLabel = new QLabel(tr("窗口句柄"), this);
    QLabel* windowTitleLabel = new QLabel(tr("窗口标题"), this);
    QLabel* windowPosLabel = new QLabel(tr("窗口位置"), this);

    //QLabel* windowPositionLabel = new QLabel(tr("窗口位置"), this);

    m_WindowHandleLineEdit = new QLineEdit(this);
    m_WindowTitleLineEdit = new QLineEdit(this);

    m_FlushButton = new QPushButton(this);
    m_FlushButton->setIcon(QIcon("image/flush_buttom.jpg"));
    m_FlushButton->setFixedSize(30, 30);


    // 从0行0列开始，然后占了1行1列
    m_LeftButtomWindowGridLayout->addWidget(m_IconButton, 0, 0, 1, 1);

    m_LeftButtomWindowGridLayout->addWidget(windowHandleLabel, 0, 1, 1, 1);
    m_LeftButtomWindowGridLayout->addWidget(m_WindowHandleLineEdit, 0, 2, 1, 2);
    m_LeftButtomWindowGridLayout->addWidget(m_FlushButton, 0, 4, 1, 1);


    m_LeftButtomWindowGridLayout->addWidget(windowTitleLabel, 1, 1, 1, 1);
    m_LeftButtomWindowGridLayout->addWidget(m_WindowTitleLineEdit, 1, 2, 1, 2);


    

    

    
    

    
}

