#include "SpyWindow.h"
#include <Windows.h>
#include <QStyleOption>
#include <QPainter>

SpyWindow::SpyWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

    m_MainLayout = new QHBoxLayout();
    m_WindowTree = new QTreeWidget(this);
   
    m_WindowTree->setColumnCount(1);
    QTreeWidgetItem* root = new QTreeWidgetItem(m_WindowTree, QStringList(QString("Root")));
    QTreeWidgetItem* leaf = new QTreeWidgetItem(root, QStringList(QString("Leaf 1")));
    root->addChild(leaf);
    QTreeWidgetItem* leaf2 = new QTreeWidgetItem(root, QStringList(QString("Leaf 1")));
    leaf2->setCheckState(0, Qt::Checked);
    root->addChild(leaf2);
    QList<QTreeWidgetItem*> rootList;
    rootList << root;
    m_WindowTree->insertTopLevelItems(0, rootList);


    m_MainLayout->addWidget(m_WindowTree);
    setLayout(m_MainLayout);
    


	
}

SpyWindow::~SpyWindow(){
}

void SpyWindow::paintEvent(QPaintEvent* e) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
