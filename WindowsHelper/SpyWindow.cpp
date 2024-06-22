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

    // layout集体初始化
    initAllLayout();
   
    
    initTopButton();

    initLeftButtomWindowLayout();
    initAttributesLayout();
    initFunctionLayout();
    initTableWidget();

	// 设置按钮的所有Style
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
    // 设置向上对齐
    m_LeftButtomLayout->setAlignment(Qt::AlignTop);

    m_AttributesLeftLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    
    
    // 窗口靠上
    m_LeftButtomWindowGridLayout->setAlignment(Qt::AlignTop);
    

    m_MainLayout->addLayout(m_ButtomLayout);

}

void SpyWindow::initLeftButtomWindowLayout() {
    m_IconButton = new QPushButton(tr("探测图片"), this);
   

    QLabel* windowHandleLabel = new QLabel(tr("窗口句柄"), this);
    windowHandleLabel->setFixedSize(80, 30);

    QLabel* windowTitleLabel = new QLabel(tr("窗口标题"), this);
    windowTitleLabel->setFixedSize(80, 30);
    QLabel* windowPosLabel = new QLabel(tr("窗口位置"), this);
    
    windowPosLabel->setFixedSize(80, 30);
    
    m_WindowHandleLineEdit = new QLineEdit(this);
    m_WindowTitleLineEdit = new QLineEdit(this);
    m_WindowPosLineEdit = new QLineEdit(this);






    m_FlushButton = new QPushButton(this);
    m_FlushButton->setFixedSize(30, 30);


    // 从0行0列开始，然后占了1行1列
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
    QLabel* visableLabel = new QLabel(tr("可视"), this);
    QLabel* stopMoveLabel = new QLabel(tr("禁止"), this);
    QLabel* topWindowLabel = new QLabel(tr("置顶"), this);
    QLabel* transparentLabel = new QLabel(tr("透明"), this);

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
    QLabel* topLevelLable = new QLabel(tr("顶级窗口"), this);
    m_TopLevelLineEdit = new QLineEdit(this);
    m_TopLevelPushButton = new QPushButton(this);
    
    QLabel* parentLabel = new QLabel(tr("父窗口"), this);
    m_ParentLineEdit = new QLineEdit(this);
    m_ParentPushButton = new QPushButton(this);

    QLabel* previewLabel = new QLabel(tr("上一窗口"), this);
    m_PreviewLineEdit = new QLineEdit(this);
    m_PreviewPushButton = new QPushButton(this);

    QLabel* nextLabel = new QLabel(tr("下一窗口"), this);
    m_NextLineEdit = new QLineEdit(this);
    m_NextPushButton = new QPushButton(this);

    QLabel* programPathLabel = new QLabel(tr("程序路径"), this);
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
    QStringList headers { "属性名", "属性值", "备注" };
    m_InfoTableWidget->setColumnCount(headers.count());
    m_InfoTableWidget->setHorizontalHeaderLabels(headers);
    m_InfoTableWidget->verticalHeader()->setHidden(true);
    
    // 设置铺平，占满整个QTableWidget
    m_InfoTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    // 这个感觉以后可以写在文件中
    addTitleRow("基本信息");
    addRow(QStringList() << "窗口句柄");
    addRow(QStringList() << "窗口类型");
    addRow(QStringList() << "窗口类型");
    addRow(QStringList() << "窗口句柄");
    addRow(QStringList() << "窗口类名");
    addRow(QStringList() << "标识(ID)");
    addRow(QStringList() << "窗口尺寸");
    addRow(QStringList() << "客户区");
    addRow(QStringList() << "窗口样式");
    addRow(QStringList() << "实例句柄");
    addRow(QStringList() << "菜单句柄");
    addRow(QStringList() << "进程句柄");
    addRow(QStringList() << "窗口字体");
    addRow(QStringList() << "窗口可视");
    addRow(QStringList() << "窗口禁止");
    addRow(QStringList() << "窗口置顶");
    addRow(QStringList() << "窗口透明");
    addRow(QStringList() << "Unicode窗口");
    
    addTitleRow("关系窗口");
    
    addRow(QStringList() << "所属窗口");
    addRow(QStringList() << "顶级窗口");
    addRow(QStringList() << "上一窗口");
    addRow(QStringList() << "下一窗口");

    addTitleRow("窗口类");

    addRow(QStringList() << "窗口类名");
    addRow(QStringList() << "类样式");
    addRow(QStringList() << "窗口过程");
    addRow(QStringList() << "模块句柄");
    addRow(QStringList() << "附加字节");
    addRow(QStringList() << "窗口附加字节");
    addRow(QStringList() << "图标句柄");
    addRow(QStringList() << "光标句柄");
    addRow(QStringList() << "背景画刷");

    addTitleRow("类样式");
    
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

    addTitleRow("窗口样式");

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

    addTitleRow("扩展样式");

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
    // 设置大小
    m_IconButton->setFixedSize(50, 50);
    m_TopLevelPushButton->setFixedSize(30, 30);
    m_ParentPushButton->setFixedSize(30, 30);
    m_PreviewPushButton->setFixedSize(30, 30);
    m_NextPushButton->setFixedSize(30, 30);
    m_ProgramPathPushButton->setFixedSize(30, 30);

    // 设置图片
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
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);  // 设置为不可编辑
    m_InfoTableWidget->setSpan(rowPosition, 0, 1, m_InfoTableWidget->columnCount());  
    m_InfoTableWidget->setItem(rowPosition, 0, item);
}

void SpyWindow::addRow(const QStringList& data) {
    int rowPosition = m_InfoTableWidget->rowCount();
    m_InfoTableWidget->insertRow(rowPosition);
    for (int col = 0; col < data.size(); col++) {
        QString cellData = data[col];
        // 区分标签和列表
        if (col == 0) {
            cellData.prepend("   ");
        }

        QTableWidgetItem* item = new QTableWidgetItem(cellData);
        // 将第一列设置成不可编辑
        if (col == 0) {
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        }
        m_InfoTableWidget->setItem(rowPosition, col, item);
    }

}

