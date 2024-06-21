#include "SpyWindow.h"
#include <Windows.h>
#include <QStyleOption>
#include <QPainter>

SpyWindow::SpyWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

    // layout�����ʼ��
    initAllLayout();
   
    
    initTopButton();

    initLeftButtomWindowLayout();


	// �������в���
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
    m_BasicInfoButton = new QPushButton(tr("���ƻ�����Ϣ"), this);
    m_CommonOperationsButton = new QPushButton(tr("���ò���"), this);
    m_FindWindowlabel = new QLabel(tr("���Ҵ���"), this);
    m_FindWindowLineEdit = new QLineEdit(this);
    m_TopLayout->addWidget(m_BasicInfoButton);
    m_TopLayout->addWidget(m_CommonOperationsButton);
    
    // ���һ���������ʵ�����м������Ч�������˾���
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
    
    // ���ڿ���
    m_LeftButtomWindowGridLayout->setAlignment(Qt::AlignTop);

    m_MainLayout->addLayout(m_ButtomLayout);

}

void SpyWindow::initLeftButtomWindowLayout() {
    m_IconButton = new QPushButton(tr("̽��ͼƬ"),this);
   
    QLabel* windowHandleLabel = new QLabel(tr("���ھ��"), this);
    QLabel* windowTitleLabel = new QLabel(tr("���ڱ���"), this);
    QLabel* windowPosLabel = new QLabel(tr("����λ��"), this);

    //QLabel* windowPositionLabel = new QLabel(tr("����λ��"), this);

    m_WindowHandleLineEdit = new QLineEdit(this);
    m_WindowTitleLineEdit = new QLineEdit(this);

    m_FlushButton = new QPushButton(this);
    m_FlushButton->setIcon(QIcon("image/flush_buttom.jpg"));
    m_FlushButton->setFixedSize(30, 30);


    // ��0��0�п�ʼ��Ȼ��ռ��1��1��
    m_LeftButtomWindowGridLayout->addWidget(m_IconButton, 0, 0, 1, 1);

    m_LeftButtomWindowGridLayout->addWidget(windowHandleLabel, 0, 1, 1, 1);
    m_LeftButtomWindowGridLayout->addWidget(m_WindowHandleLineEdit, 0, 2, 1, 2);
    m_LeftButtomWindowGridLayout->addWidget(m_FlushButton, 0, 4, 1, 1);


    m_LeftButtomWindowGridLayout->addWidget(windowTitleLabel, 1, 1, 1, 1);
    m_LeftButtomWindowGridLayout->addWidget(m_WindowTitleLineEdit, 1, 2, 1, 2);


    

    

    
    

    
}

