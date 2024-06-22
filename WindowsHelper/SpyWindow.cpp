#include "SpyWindow.h"
#include <Windows.h>
#include <QStyleOption>
#include <QPainter>
#include <QHeaderView>
#include <QTableWidgetItem>

SpyWindow::SpyWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

    // layout�����ʼ��
    initAllLayout();
   
    
    initTopButton();

    initLeftButtomWindowLayout();
    initAttributesLayout();
    initFunctionLayout();
    initTableWidget();

	// ���ð�ť������Style
    setAllButtonStyle();
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
    m_LeftButtomLayout = new QVBoxLayout();
    m_LeftButtomWindowGridLayout = new QGridLayout();
    m_AttributesLeftLayout = new QHBoxLayout();
    m_FunctionGridLayout = new QGridLayout();
}

void SpyWindow::setAllLayout() {
    m_MainLayout->addLayout(m_TopLayout);
    
    m_ButtomLayout->addLayout(m_LeftButtomLayout);
    m_ButtomLayout->addWidget(m_WindowTree);

    m_LeftButtomLayout->addLayout(m_LeftButtomWindowGridLayout);
    m_LeftButtomLayout->addLayout(m_AttributesLeftLayout);
    m_LeftButtomLayout->addLayout(m_FunctionGridLayout);
    m_LeftButtomLayout->addWidget(m_InfoTableWidget);
    // �������϶���
    m_LeftButtomLayout->setAlignment(Qt::AlignTop);

    m_AttributesLeftLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    
    
    // ���ڿ���
    m_LeftButtomWindowGridLayout->setAlignment(Qt::AlignTop);
    

    m_MainLayout->addLayout(m_ButtomLayout);

}

void SpyWindow::initLeftButtomWindowLayout() {
    m_IconButton = new QPushButton(tr("̽��ͼƬ"), this);
   

    QLabel* windowHandleLabel = new QLabel(tr("���ھ��"), this);
    windowHandleLabel->setFixedSize(80, 30);

    QLabel* windowTitleLabel = new QLabel(tr("���ڱ���"), this);
    windowTitleLabel->setFixedSize(80, 30);
    QLabel* windowPosLabel = new QLabel(tr("����λ��"), this);
    
    windowPosLabel->setFixedSize(80, 30);
    
    m_WindowHandleLineEdit = new QLineEdit(this);
    m_WindowTitleLineEdit = new QLineEdit(this);
    m_WindowPosLineEdit = new QLineEdit(this);






    m_FlushButton = new QPushButton(this);
    m_FlushButton->setFixedSize(30, 30);


    // ��0��0�п�ʼ��Ȼ��ռ��1��1��
    m_LeftButtomWindowGridLayout->addWidget(m_IconButton, 0, 0, 1, 1);

    m_LeftButtomWindowGridLayout->addWidget(windowHandleLabel, 0, 1, 1, 1);
    m_LeftButtomWindowGridLayout->addWidget(m_WindowHandleLineEdit, 0, 2, 1, 2);
    m_LeftButtomWindowGridLayout->addWidget(m_FlushButton, 0, 4, 1, 1);


    m_LeftButtomWindowGridLayout->addWidget(windowTitleLabel, 1, 1, 1, 1);
    m_LeftButtomWindowGridLayout->addWidget(m_WindowTitleLineEdit, 1, 2, 1, 2);

    m_LeftButtomWindowGridLayout->addWidget(windowPosLabel, 2, 1, 1, 1);
    m_LeftButtomWindowGridLayout->addWidget(m_WindowPosLineEdit, 2, 2, 1, 2);

}


    

void SpyWindow::initAttributesLayout() {
    QLabel* visableLabel = new QLabel(tr("����"), this);
    QLabel* stopMoveLabel = new QLabel(tr("��ֹ"), this);
    QLabel* topWindowLabel = new QLabel(tr("�ö�"), this);
    QLabel* transparentLabel = new QLabel(tr("͸��"), this);

    m_VisableCheckBox= new QCheckBox(this);
    m_StopMoveCheckBox = new QCheckBox(this);
    m_TopWindowCheckBox = new QCheckBox(this);
    m_TransparentCheckBox= new QCheckBox(this);



    m_AttributesLeftLayout->addWidget(visableLabel);
    m_AttributesLeftLayout->addWidget(m_VisableCheckBox);
    m_AttributesLeftLayout->addWidget(stopMoveLabel);
    m_AttributesLeftLayout->addWidget(m_StopMoveCheckBox);
    m_AttributesLeftLayout->addWidget(topWindowLabel);
    m_AttributesLeftLayout->addWidget(m_TopWindowCheckBox);
    m_AttributesLeftLayout->addWidget(transparentLabel);
    m_AttributesLeftLayout->addWidget(m_TransparentCheckBox);


}

void SpyWindow::initFunctionLayout() {
    QLabel* topLevelLable = new QLabel(tr("��������"), this);
    m_TopLevelLineEdit = new QLineEdit(this);
    m_TopLevelPushButton = new QPushButton(this);
    
    QLabel* parentLabel = new QLabel(tr("������"), this);
    m_ParentLineEdit = new QLineEdit(this);
    m_ParentPushButton = new QPushButton(this);

    QLabel* previewLabel = new QLabel(tr("��һ����"), this);
    m_PreviewLineEdit = new QLineEdit(this);
    m_PreviewPushButton = new QPushButton(this);

    QLabel* nextLabel = new QLabel(tr("��һ����"), this);
    m_NextLineEdit = new QLineEdit(this);
    m_NextPushButton = new QPushButton(this);

    QLabel* programPathLabel = new QLabel(tr("����·��"), this);
    m_ProgramPathLineEdit = new QLineEdit(this);
    m_ProgramPathPushButton = new QPushButton(this);


    m_FunctionGridLayout->addWidget(topLevelLable, 0, 0, 1, 1);
    m_FunctionGridLayout->addWidget(m_TopLevelLineEdit, 0, 1, 1, 1);
    m_FunctionGridLayout->addWidget(m_TopLevelPushButton, 0, 2, 1, 1);
    m_FunctionGridLayout->addWidget(parentLabel, 0, 3, 1, 1);
    m_FunctionGridLayout->addWidget(m_ParentLineEdit, 0, 4, 1, 1);
    m_FunctionGridLayout->addWidget(m_ParentPushButton, 0, 5, 1, 1);


    m_FunctionGridLayout->addWidget(previewLabel, 1, 0, 1, 1);
    m_FunctionGridLayout->addWidget(m_PreviewLineEdit, 1, 1, 1, 1);
    m_FunctionGridLayout->addWidget(m_PreviewPushButton, 1, 2, 1, 1);
    m_FunctionGridLayout->addWidget(nextLabel, 1, 3, 1, 1);
    m_FunctionGridLayout->addWidget(m_NextLineEdit, 1, 4, 1, 1);
    m_FunctionGridLayout->addWidget(m_NextPushButton, 1, 5, 1, 1);

    m_FunctionGridLayout->addWidget(programPathLabel, 2, 0, 1, 1);
    m_FunctionGridLayout->addWidget(m_ProgramPathLineEdit, 2, 1, 1, 4);
    m_FunctionGridLayout->addWidget(m_ProgramPathPushButton, 2, 5, 1, 1);







}

void SpyWindow::initTableWidget() {
    m_InfoTableWidget = new QTableWidget(this);
    QStringList headers { "������", "����ֵ", "��ע" };
    m_InfoTableWidget->setColumnCount(headers.count());
    m_InfoTableWidget->setHorizontalHeaderLabels(headers);
    m_InfoTableWidget->verticalHeader()->setHidden(true);
    
    // ������ƽ��ռ������QTableWidget
    m_InfoTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    // ����о��Ժ����д���ļ���
    addTitleRow("������Ϣ");
    addRow(QStringList() << "���ھ��");
    addRow(QStringList() << "��������");
    addRow(QStringList() << "��������");
    addRow(QStringList() << "���ھ��");
    addRow(QStringList() << "��������");
    addRow(QStringList() << "��ʶ(ID)");
    addRow(QStringList() << "���ڳߴ�");
    addRow(QStringList() << "�ͻ���");
    addRow(QStringList() << "������ʽ");
    addRow(QStringList() << "ʵ�����");
    addRow(QStringList() << "�˵����");
    addRow(QStringList() << "���̾��");
    addRow(QStringList() << "��������");
    addRow(QStringList() << "���ڿ���");
    addRow(QStringList() << "���ڽ�ֹ");
    addRow(QStringList() << "�����ö�");
    addRow(QStringList() << "����͸��");
    addRow(QStringList() << "Unicode����");
    
    addTitleRow("��ϵ����");
    
    addRow(QStringList() << "��������");
    addRow(QStringList() << "��������");
    addRow(QStringList() << "��һ����");
    addRow(QStringList() << "��һ����");

    addTitleRow("������");

    addRow(QStringList() << "��������");
    addRow(QStringList() << "����ʽ");
    addRow(QStringList() << "���ڹ���");
    addRow(QStringList() << "ģ����");
    addRow(QStringList() << "�����ֽ�");
    addRow(QStringList() << "���ڸ����ֽ�");
    addRow(QStringList() << "ͼ����");
    addRow(QStringList() << "�����");
    addRow(QStringList() << "������ˢ");

    addTitleRow("����ʽ");
    
    addRow(QStringList() << "CS BYTEALIGNCLIENT" << " " << "");
    addRow(QStringList() << "CS BYTEALIGNWINDOW" << "" << "");
    addRow(QStringList() << "CS CLASSDC" << "" << "");
    addRow(QStringList() << "CS DBLCLKS" << "" << "");
    addRow(QStringList() << "CS GLOBALCLASS" << "" << "");
    addRow(QStringList() << "CS HREDRAW" << "" << "");
    addRow(QStringList() << "CS_IME" << "" << "");
    addRow(QStringList() << "CS NOCLOSE" << "" << "");
    addRow(QStringList() << "CS OWNDC" << "" << "");
    addRow(QStringList() << "CS PARENTDC" << "" << "");
    addRow(QStringList() << "CS SAVEBITS" << "" << "");
    addRow(QStringList() << "SURRTRAW" << "" << "");

    addTitleRow("������ʽ");

    addRow(QStringList() << "WS_POPUP");
    addRow(QStringList() << "WS_CHILDWINDOW");
    addRow(QStringList() << "WS_MINIMIZE");
    addRow(QStringList() << "WS_VISIBLE");
    addRow(QStringList() << "WS_DISABLED");
    addRow(QStringList() << "WS_CLIPSIBLINGS");
    addRow(QStringList() << "WS_CLIPCHILDREN");
    addRow(QStringList() << "WS_MAXIMIZE");
    addRow(QStringList() << "WS_CAPTION");
    addRow(QStringList() << "WS_BORDER");
    addRow(QStringList() << "WS_DLGFRAME");
    addRow(QStringList() << "WS_VSCROLL");
    addRow(QStringList() << "WS_HSCROLL");
    addRow(QStringList() << "WS_SYSMEM");
    addRow(QStringList() << "WS_THICKFRAME");
    addRow(QStringList() << "WS_GROUP");
    addRow(QStringList() << "WS_TABSTOP");
    addRow(QStringList() << "WS_MINIMIZEBOX");
    addRow(QStringList() << "WS_MAXIMIZEBOX");
    addRow(QStringList() << "WS_OVERLAPPEDWINDOW");
    addRow(QStringList() << "WS_POPUPWINDOW");

    addTitleRow("��չ��ʽ");

    addRow(QStringList() << "WS_EX_PARENTNOTIFY");
    addRow(QStringList() << "WS_EX_TOPMOST");
    addRow(QStringList() << "WS_EX_ACCEPTFILES");
    addRow(QStringList() << "WS_EX_TRANSPARENT");
    addRow(QStringList() << "WS_EX_MDICHILD");
    addRow(QStringList() << "WS_EX_TOOLWINDOW");
    addRow(QStringList() << "WS_EX_WINDOWEDGE");
    addRow(QStringList() << "WS_EX_CLIENTEDGE");
    addRow(QStringList() << "WS_EX_CONTEXTHELP");
    addRow(QStringList() << "WS_EX_RIGHT");
    addRow(QStringList() << "WS_EX_RTLREADING");
    addRow(QStringList() << "WS_EX_LEFTSCROLLBAR");
    addRow(QStringList() << "WS_EX_CONTROLPARENT");
    addRow(QStringList() << "WS_EX_STATICEDGE");
    addRow(QStringList() << "WS_EX_APPWINDOW");
    addRow(QStringList() << "WS_EX_OVERLAPPEDWINDOW");
    addRow(QStringList() << "WS_EX_PALETTEWINDOW");
    addRow(QStringList() << "WS_EX_LAYERED");
    addRow(QStringList() << "WS_EX_NOINHERITLAYOUT");
    addRow(QStringList() << "WS_EX_LAYOUTRTL");
    addRow(QStringList() << "WS_EX_COMPOSITED");
    addRow(QStringList() << "WS_EX_NOACTIVATE");
    
        
}

void SpyWindow::setAllButtonStyle() {
    // ���ô�С
    m_IconButton->setFixedSize(50, 50);
    m_TopLevelPushButton->setFixedSize(30, 30);
    m_ParentPushButton->setFixedSize(30, 30);
    m_PreviewPushButton->setFixedSize(30, 30);
    m_NextPushButton->setFixedSize(30, 30);
    m_ProgramPathPushButton->setFixedSize(30, 30);

    // ����ͼƬ
    m_FlushButton->setIcon(QIcon("image/flush_buttom.jpg"));
    m_ProgramPathPushButton->setIcon(QIcon("image/file.jpg"));
    
}



void SpyWindow::setAllCheckBoxSytle() {
    m_VisableCheckBox->setFixedSize(20, 20);
    m_StopMoveCheckBox->setFixedSize(20, 20);
    m_TopWindowCheckBox->setFixedSize(20, 20);
    m_TransparentCheckBox->setFixedSize(20, 20);
}

void SpyWindow::addTitleRow(const QString& title) {
    int rowPosition = m_InfoTableWidget->rowCount();
    m_InfoTableWidget->insertRow(rowPosition);
    QTableWidgetItem* item = new QTableWidgetItem(title);
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);  // ����Ϊ���ɱ༭
    m_InfoTableWidget->setSpan(rowPosition, 0, 1, m_InfoTableWidget->columnCount());  
    m_InfoTableWidget->setItem(rowPosition, 0, item);
}

void SpyWindow::addRow(const QStringList& data) {
    int rowPosition = m_InfoTableWidget->rowCount();
    m_InfoTableWidget->insertRow(rowPosition);
    for (int col = 0; col < data.size(); col++) {
        QString cellData = data[col];
        // ���ֱ�ǩ���б�
        if (col == 0) {
            cellData.prepend("   ");
        }

        QTableWidgetItem* item = new QTableWidgetItem(cellData);
        // ����һ�����óɲ��ɱ༭
        if (col == 0) {
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        }
        m_InfoTableWidget->setItem(rowPosition, col, item);
    }

}

