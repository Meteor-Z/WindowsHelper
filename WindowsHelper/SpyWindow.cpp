#include "SpyWindow.h"
#include <Windows.h>
#include <QStyleOption>
#include <QPainter>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QFont>

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

    setAllButtonStyle();
    setAllSingalSlot();
    setAllLayout();
    QApplication::instance()->installEventFilter(this);
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
    m_ShootButton = new QPushButton(this);
   
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



    // ��0��0�п�ʼ��Ȼ��ռ��1��1��
    m_LeftButtomWindowGridLayout->addWidget(m_ShootButton, 0, 0, 1, 1);

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
    addRow(QStringList() << "��ʶ(ID)");
    addRow(QStringList() << "���ڳߴ�");
    addRow(QStringList() << "�ͻ���");
    addRow(QStringList() << "������ʽ");
    addRow(QStringList() << "ʵ�����");
    addRow(QStringList() << "�˵����");
    addRow(QStringList() << "���̾��");
    addRow(QStringList() << "��������");
    addRow(QStringList() << "���ڿ���");
    addRow(QStringList() << "���ڽ�ֹ" << " " <<"�ô����Ƿ��ܹ������������/���̵�����");
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

    m_FlushButton->setFixedSize(30, 30);
    m_FlushButton->setIcon(QIcon("image/flush_buttom.jpg"));
    m_FlushButton->setToolTip(tr("ˢ����Ϣ"));

    m_ShootButton->setFixedSize(50, 50);
    m_TopLevelPushButton->setFixedSize(30, 30);
    m_ParentPushButton->setFixedSize(30, 30);
    m_PreviewPushButton->setFixedSize(30, 30);
    m_NextPushButton->setFixedSize(30, 30);
    m_ProgramPathPushButton->setFixedSize(30, 30);
   

    // ����ͼƬ
    m_ProgramPathPushButton->setIcon(QIcon("image/file.jpg"));
    m_ShootButton->setIcon(QIcon("image/shoot.png"));

    m_TopLevelPushButton->setIcon(QIcon("image/next.png"));
    m_ParentPushButton->setIcon(QIcon("image/next.png"));
    m_NextPushButton->setIcon(QIcon("image/next.png"));
    m_PreviewPushButton->setIcon(QIcon("image/next.png"));
}



void SpyWindow::setAllCheckBoxSytle() {
    m_VisableCheckBox->setFixedSize(20, 20);
    m_StopMoveCheckBox->setFixedSize(20, 20);
    m_TopWindowCheckBox->setFixedSize(20, 20);
    m_TransparentCheckBox->setFixedSize(20, 20);
}

void SpyWindow::setAllSingalSlot() {
    // �ı�������ʽ��ע�������ǰ�ѹ
    connect(m_ShootButton, &QPushButton::pressed, this, &SpyWindow::changeCursor);
}


void SpyWindow::addTitleRow(const QString& title) {
    int rowPosition = m_InfoTableWidget->rowCount();
    m_InfoTableWidget->insertRow(rowPosition);
    QTableWidgetItem* item = new QTableWidgetItem(title);

    // �Ӵ�
    QFont font = item->font();
    font.setBold(true);
    item->setFont(font);

    // ������Ϣ���ҽ��������óɲ��ɱ༭
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
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

void SpyWindow::changeCursor() {
    
    setCursor(QCursor(QPixmap("image/shoot.png")));
    m_ShootButton->setIcon(QIcon(""));
    m_ShootButtonIsPress = true;
    
}

void SpyWindow::restoreCursor() {
    m_ShootButton->setIcon(QIcon("image/shoot.png"));
    setCursor(Qt::ArrowCursor);
    m_ShootButtonIsPress = false;
}

void SpyWindow::getWindowHandleByPoint(const QPoint& pos) {
    
    m_CurrentWindowHandle = WindowFromPoint({pos.x(), pos.y()});
    std::wstring className(256, L'\0');
    int resultLength = GetClassName(m_CurrentWindowHandle, &className[0], className.size());
    
    if (resultLength == 0) {
        DWORD error = GetLastError();
        // ������
    } else {
        className.resize(resultLength);
    }
    // ����ȷʵ�ǻ�ȡ���ˣ�����Ҫ����һ��
    //MessageBox(nullptr, className.c_str(), className.c_str(), 0);

    updateHwndInfo();

}

bool SpyWindow::eventFilter(QObject* obj, QEvent* event) {
    // �����ǵõ������ť�Ƿ����ˣ�Ȼ��õ���Ӧ���±꣬Ȼ��ͨ������õ��õ���Ӧ����Ϣ
    if (m_ShootButtonIsPress && event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            restoreCursor();
            QPoint pos = QCursor::pos();
            getWindowHandleByPoint(pos);
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void SpyWindow::updateHwndInfo() {
    if (!m_CurrentWindowHandle) {
        return;
    }

    // д��ѭ��������ʡ�¡��������ڸ�һ�£��е��鷳������
    for (int row = 0; row < m_InfoTableWidget->rowCount(); row++) {
        QTableWidgetItem* propertyItem = m_InfoTableWidget->item(row, 0);
        if (!propertyItem) {
            continue;
        }

        QString key = propertyItem->text().trimmed();
        if (key == "���ھ��") {
            QString valueBase10 = QString::number(reinterpret_cast<quintptr>(m_CurrentWindowHandle));
            QString valueBase16 = QString::number(reinterpret_cast<quintptr>(m_CurrentWindowHandle), 16);
            m_InfoTableWidget->setItem(row, 1, new QTableWidgetItem(valueBase10));
            m_InfoTableWidget->setItem(row, 2, new QTableWidgetItem(valueBase16));
            
        }

        if (key == "��������") {
            std::wstring className(256, L'\0');
            int resultLength = GetClassName(m_CurrentWindowHandle, &className[0], className.size());
            if (resultLength != 0) {
                QString value = QString::fromStdWString(className.substr(0, resultLength));
                m_InfoTableWidget->setItem(row, 1, new QTableWidgetItem(value));
            }
        }

        if (key == "���ڳߴ�") {
            RECT rect{};
            if (GetWindowRect(m_CurrentWindowHandle, &rect)) {
                int width = rect.right - rect.left;
                int height = rect.bottom - rect.top;
                QString windowSize = QString("%1 x %2").arg(width).arg(height);
                QString detailedSize = QString("left:%1, right:%2, top:%3, bottom: %4").arg(rect.left).arg(rect.right).arg(rect.top).arg(rect.bottom);
                // �ܸо����ﲻ�ԣ���spyxx�Ĳ��ԡ�����������������
                m_InfoTableWidget->setItem(row, 1, new QTableWidgetItem(windowSize));
                m_InfoTableWidget->setItem(row, 2, new QTableWidgetItem(detailedSize));

            }
        }

        if (key == "�ͻ���") {
            RECT rect{};
            if (GetClientRect(m_CurrentWindowHandle, &rect)) {
                int width = rect.right - rect.left;
                int height = rect.bottom - rect.top;
                QString windowSize = QString("%1 x %2").arg(width).arg(height);
                QString detailedSize = QString("left:%1, right:%2, top:%3, bottom: %4").arg(rect.left).arg(rect.right).arg(rect.top).arg(rect.bottom);
                // �ܸо����ﲻ�ԣ���spyxx�Ĳ��ԡ�����������������
                m_InfoTableWidget->setItem(row, 1, new QTableWidgetItem(windowSize));
                m_InfoTableWidget->setItem(row, 2, new QTableWidgetItem(detailedSize));

            }
        }

        if (key == "���̾��") {
            // ����PID
            DWORD dwPid = -1;
            GetWindowThreadProcessId(m_CurrentWindowHandle, &dwPid);
            HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
            QString value = QString::number(dwPid);
            m_InfoTableWidget->setItem(row, 1, new QTableWidgetItem(value));
        }

        if (key == "���ڿ���") {
            bool isVisible = IsWindowVisible(m_CurrentWindowHandle);
            
            QTableWidgetItem* item = new QTableWidgetItem();

            if (isVisible) {
                item->setBackground(QBrush(QColor(Qt::green)));
            } else {
                item->setBackground(QBrush(QColor(Qt::red)));
            }
            m_InfoTableWidget->setItem(row, 1, item);
        }

        if (key == "���ڽ�ֹ") {
            bool isEnable = IsWindowEnabled(m_CurrentWindowHandle);

            QTableWidgetItem* item = new QTableWidgetItem();

            if (isEnable) {
                item->setBackground(QBrush(QColor(Qt::red)));
            } else {
                item->setBackground(QBrush(QColor(Qt::green)));
            }
            m_InfoTableWidget->setItem(row, 1, item);
        }

        if (key == "���ھ��") {
                
        }

        

    }
   


}
