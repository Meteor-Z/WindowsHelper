#include <Windows.h>
#include "SpyWindow.h"
#include <QStyleOption>
#include <QPainter>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QFont>
#include <QFileDialog>
#include <QPixmap>
#include <Utils.h>
#include <Psapi.h>
#include <QDesktopServices>
#include <QtWinExtras/qwinfunctions.h>
#include <QMenu>

SpyWindow::SpyWindow(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    // layout集体初始化
    initAllLayout();

    updateWindowTree();
    
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
    m_WindowTree = new QTreeWidget(this);
    m_TopLayout = new QHBoxLayout();
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
    m_ShootButton = new QPushButton(this);
   
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



    // 从0行0列开始，然后占了1行1列
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
    addRow(QStringList() << "窗口禁止" << " " <<"该窗口是否能够接收来自鼠标/键盘的输入");
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
    
    for (const auto& item : ClassInfoVec) {
        addRow(QStringList() << item.key << " " << item.commnet);
    }

    addTitleRow("窗口样式");

    for (const auto& item : WMInfoVec) {
        addRow(QStringList() << item.key << " " << item.commnet);
    }

    addTitleRow("扩展样式");

    for (const auto& item : WMExtraInfoVec) {
        addRow(QStringList() << item.key << " " << item.commnet);
    }
    
        
}

void SpyWindow::setAllButtonStyle() {

    m_FlushButton->setFixedSize(30, 30);
    m_FlushButton->setIcon(QIcon("image/flush_buttom.jpg"));
    m_FlushButton->setToolTip(tr("刷新信息"));

    m_ShootButton->setFixedSize(50, 50);
    m_TopLevelPushButton->setFixedSize(30, 30);
    m_ParentPushButton->setFixedSize(30, 30);
    m_PreviewPushButton->setFixedSize(30, 30);
    m_NextPushButton->setFixedSize(30, 30);
    m_ProgramPathPushButton->setFixedSize(30, 30);
   

    // 设置图片
    m_ProgramPathPushButton->setIcon(QIcon("image/file.jpg"));
    m_ProgramPathPushButton->setToolTip(tr("打开文件所在位置"));
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
    // 改变鼠标的样式，注意这里是按压
    connect(m_ShootButton, &QPushButton::pressed, this, &SpyWindow::changeCursor);
    connect(m_ProgramPathPushButton, &QPushButton::clicked, [this]() {
        QString path = m_ProgramPathLineEdit->text();
        int lastIndex = path.lastIndexOf('\\');
        path = path.left(lastIndex);
        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
        });
    connect(m_FlushButton, &QPushButton::clicked, [this]() {
        updateHwndInfo();
        });

    // 点击QTreeWidgetItem，然后显示相关信息
    connect(m_WindowTree, &QTreeWidget::itemPressed, [this](QTreeWidgetItem* item, int column) {
        if (qApp->mouseButtons() == Qt::LeftButton) {
            HWND hwnd = reinterpret_cast<HWND>(item->text(column).split(' ')[0].toULongLong());
            m_CurrentWindowHandle = hwnd;
            updateHwndInfo();
            updateWindowTree();
        }

        if (qApp->mouseButtons() == Qt::RightButton) {
            QMenu* menu = new QMenu(this);
            QAction* message = new QAction(tr("消息监听"), this);
            menu->addAction(message);
            if (item) {
                menu->exec(QCursor::pos());
            }
        }
    });
}


void SpyWindow::addTitleRow(const QString& title) {
    int rowPosition = m_InfoTableWidget->rowCount();
    m_InfoTableWidget->insertRow(rowPosition);
    QTableWidgetItem* item = new QTableWidgetItem(title);

    // 加粗
    QFont font = item->font();
    font.setBold(true);
    item->setFont(font);

    // 设置信息并且将整行设置成不可编辑
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
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
        if (col == 0) {
            item->setFlags(item->flags() & ~Qt::ItemIsEditable); // 移除可编辑的按钮
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

void SpyWindow::setWindowHandleByPoint(const QPoint& pos) {
    
    m_CurrentWindowHandle = WindowFromPoint({pos.x(), pos.y()});
    std::wstring className(256, L'\0');
    int resultLength = GetClassName(m_CurrentWindowHandle, &className[0], static_cast<int>(className.size()));
    
    updateHwndInfo();

}

bool SpyWindow::eventFilter(QObject* obj, QEvent* event) {
    // 这里是得到这个按钮是否按下了，然后得到对应的下标，然后通过坐标得到得到对应的信息
    // 但是感觉这里有Bug，因为有的时候反应很慢
    if (m_ShootButtonIsPress && event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            restoreCursor();
            QPoint pos = QCursor::pos();
            setWindowHandleByPoint(pos);
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void SpyWindow::updateHwndInfo() {
    if (!m_CurrentWindowHandle) {
        return;
    }
   
    LONG_PTR style = GetWindowLongPtr(m_CurrentWindowHandle, GWL_STYLE);
    LONG_PTR exStyle = GetWindowLongPtr(m_CurrentWindowHandle, GWL_EXSTYLE);

    // 得到绿色的QTableWidgetItem
    auto getGreenQTableWidgetItem = []() {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setBackground(QBrush(QColor(0, 170, 0)));
        return item;
        };

    // 得到红色的QTableWidgetItem
    auto getRedQTableWidgetItem = []() {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setBackground(QBrush(QColor(250, 0, 0)));
        return item;
        };

    m_WindowHandleLineEdit->setText(QString::number(reinterpret_cast<quintptr>(m_CurrentWindowHandle)));
    m_WindowTitleLineEdit->setText(getWindowTitleByHwnd(m_CurrentWindowHandle));
    m_ProgramPathLineEdit->setText(getProgramPathByHwnd(m_CurrentWindowHandle));
     
    // 写成循环，这样省事。。。后期改一下，有点麻烦。。。
    for (int row = 0; row < m_InfoTableWidget->rowCount(); row++) {
        QTableWidgetItem* propertyItem = m_InfoTableWidget->item(row, 0);
        if (!propertyItem) {
            continue;
        }

        QString key = propertyItem->text().trimmed();

        if (key == "窗口句柄") {
            QString valueBase10 = QString::number(reinterpret_cast<quintptr>(m_CurrentWindowHandle));
            QString valueBase16 = QString::number(reinterpret_cast<quintptr>(m_CurrentWindowHandle), 16);
            m_InfoTableWidget->setItem(row, 1, new QTableWidgetItem(valueBase10));
            m_InfoTableWidget->setItem(row, 2, new QTableWidgetItem(valueBase16));
           
        } else if (key == "窗口类名") {
            std::wstring className(256, L'\0');
            int resultLength = GetClassName(m_CurrentWindowHandle, &className[0], static_cast<int>(className.size()));
            if (resultLength != 0) {
                QString value = QString::fromStdWString(className.substr(0, resultLength));
                m_InfoTableWidget->setItem(row, 1, new QTableWidgetItem(value));
            }
        } else if (key == "窗口尺寸") {
            RECT rect{};
            if (GetWindowRect(m_CurrentWindowHandle, &rect)) {
                int width = rect.right - rect.left;
                int height = rect.bottom - rect.top;
                QString windowSize = QString("%1 * %2").arg(width).arg(height);
                QString detailedSize = QString("左边:%1, 右边:%2, 上边:%3, 下边: %4").arg(rect.left).arg(rect.right).arg(rect.top).arg(rect.bottom);
                // 总感觉这里不对，和spyxx的不对。。。不过先这样吧
                m_InfoTableWidget->setItem(row, 1, new QTableWidgetItem(windowSize));
                m_InfoTableWidget->setItem(row, 2, new QTableWidgetItem(detailedSize));

                m_WindowPosLineEdit->setText(windowSize + QString("; ") + detailedSize);

            }
        } else if (key == "客户区") {
            RECT rect{};
            if (GetClientRect(m_CurrentWindowHandle, &rect)) {
                int width = rect.right - rect.left;
                int height = rect.bottom - rect.top;
                QString windowSize = QString("%1 x %2").arg(width).arg(height);
                QString detailedSize = QString("left:%1, right:%2, top:%3, bottom: %4").arg(rect.left).arg(rect.right).arg(rect.top).arg(rect.bottom);
                // 总感觉这里不对，和spyxx的不对。。。不过先这样吧
                // 这里会发生内存泄露么，我感觉不是很会，
                m_InfoTableWidget->setItem(row, 1, new QTableWidgetItem(windowSize));
                m_InfoTableWidget->setItem(row, 2, new QTableWidgetItem(detailedSize));
            }
        } else if (key == "进程句柄") {
            // 进程PID
            DWORD dwPid = -1;
            GetWindowThreadProcessId(m_CurrentWindowHandle, &dwPid);
            HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
            QString value = QString::number(dwPid);
            m_InfoTableWidget->setItem(row, 1, new QTableWidgetItem(value));
            CloseHandle(hProcess);
        } else if (key == "窗口可视") {
            bool isVisible = IsWindowVisible(m_CurrentWindowHandle);
            m_InfoTableWidget->setItem(row, 1, isVisible ? getGreenQTableWidgetItem(): getRedQTableWidgetItem());
            m_VisableCheckBox->setChecked(isVisible);
        } else if (key == "窗口禁止") {
            bool isEnable = IsWindowEnabled(m_CurrentWindowHandle);
            m_InfoTableWidget->setItem(row, 1, isEnable ? getRedQTableWidgetItem(): getGreenQTableWidgetItem());
            m_StopMoveCheckBox->setChecked(!isEnable);
        } else if (key == "窗口置顶") {
            bool isTopMost = isWndTopMost(m_CurrentWindowHandle);
            m_InfoTableWidget->setItem(row, 1, isTopMost ? getGreenQTableWidgetItem() : getRedQTableWidgetItem());
            m_TopWindowCheckBox->setChecked(isTopMost);
        } else if (key == "窗口透明") {
            if (exStyle & WS_EX_LAYERED) {
                BYTE alpha{ 0 };
                DWORD flags{ 0 };
                if (GetLayeredWindowAttributes(m_CurrentWindowHandle, nullptr, &alpha, &flags)) {
                    if (flags & LWA_ALPHA) {
                        m_InfoTableWidget->setItem(row, 1, alpha < 255 ? getGreenQTableWidgetItem() : getRedQTableWidgetItem());
                        m_TransparentCheckBox->setChecked(alpha < 255);
                    }
                }
            } else {
                m_InfoTableWidget->setItem(row, 1, getRedQTableWidgetItem());
                m_TransparentCheckBox->setChecked(false);
            }
        }

        // 更新窗口系列的函数
        for (const auto& info: ClassInfoVec) {
            if (key == info.key) {
                m_InfoTableWidget->setItem(row, 1, style & info.style ? getGreenQTableWidgetItem() : getRedQTableWidgetItem());
                break;
            }
        }

        for (const auto& info : WMInfoVec) {
            if (key == info.key) {
                m_InfoTableWidget->setItem(row, 1, style & info.style ? getGreenQTableWidgetItem() : getRedQTableWidgetItem());
                break;
            }
        }

        // 更新额外的窗口信息
        for (const auto& info : WMExtraInfoVec) {
            if (key == info.key) {
                m_InfoTableWidget->setItem(row, 1, exStyle & info.style ? getGreenQTableWidgetItem() : getRedQTableWidgetItem());
                break;
            }
        }
    }
   


}

bool SpyWindow::isWndTopMost(HWND hwnd) const {
    // 从网上看到的，判断窗口是否置顶
    return GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_TOPMOST;
}

QString SpyWindow::getProgramPathByHwnd(HWND hwnd) const {
    DWORD dwPid = -1;
    GetWindowThreadProcessId(m_CurrentWindowHandle, &dwPid);
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwPid);
    QString processPath{};
    if (hProcess != nullptr) {
        TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
        GetModuleFileNameEx(hProcess, NULL, szProcessName, MAX_PATH);
        processPath = QString::fromWCharArray(szProcessName);
    }

    if (hProcess) {
        CloseHandle(hProcess);
    }

    return processPath;
}

QString SpyWindow::getWindowTitleByHwnd(HWND hwnd) const {
    std::wstring className(256, L'\0');
    int resultLength = GetClassName(m_CurrentWindowHandle, &className[0], static_cast<int>(className.size()));

    if (resultLength != 0) {
        className.resize(resultLength);
    }

    return QString::fromStdWString(className);
}

void SpyWindow::updateWindowTree() {
    // 从顶级窗口开始直接枚举，相当于传递回调函数了
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(this));
    

}

BOOL SpyWindow::EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    if (GetParent(hwnd) == nullptr) {
        SpyWindow* spyWindow = reinterpret_cast<SpyWindow*>(lParam);
        spyWindow->addTreeItem(hwnd);
    }
    return TRUE;

}

void SpyWindow::addTreeItem(HWND hwnd) {
    RECT rect;
    // 太少了话，就直接 return 回去，不显示了。 //TODO: 这里改一下，纠正一下
    if (GetWindowRect(hwnd, &rect)) {
        if (rect.left == rect.right && rect.top == rect.bottom && rect.left == 0) {
            return;
        }
    }

    TCHAR windowTitle[256];
    TCHAR className[256];

    GetWindowText(hwnd, windowTitle, sizeof(windowTitle) / sizeof(TCHAR));
    GetClassName(hwnd, className, sizeof(className) / sizeof(TCHAR));
    
    QString windowHandle = QString::number(reinterpret_cast<quintptr>(hwnd));
    QString windowTitleStr = QString::fromWCharArray(windowTitle);
    QString classNameStr = QString::fromWCharArray(className);
    QString all = windowHandle + QString(" ") + windowTitleStr + QString(" ") + classNameStr;
    QTreeWidgetItem* windowItem = new QTreeWidgetItem(QStringList() << all);
    windowItem->setIcon(0, QIcon(getIconByHwnd(hwnd)));
    m_WindowTree->addTopLevelItem(windowItem);
}

QPixmap SpyWindow::getIconByHwnd(HWND hwnd) {
    HICON hIcon = reinterpret_cast<HICON>(SendMessage(hwnd, WM_GETICON, ICON_BIG, 0));

    if (hIcon == nullptr) {
        hIcon = reinterpret_cast<HICON>(GetClassLongPtr(hwnd, GCLP_HICON));
    }

    if (hIcon == nullptr) {
        hIcon = reinterpret_cast<HICON>(SendMessage(hwnd, WM_GETICON, ICON_SMALL, 0));
    }

    if (hIcon == nullptr) {
        hIcon = reinterpret_cast<HICON>(GetClassLongPtr(hwnd, GCLP_HICONSM));
    }

    if (hIcon == nullptr) {
        return QPixmap();
    }

    ICONINFO iconInfo;
    if (!GetIconInfo(hIcon, &iconInfo)) {
        return QPixmap(); // Failed to get icon info
    }

    QPixmap pixmap = QtWin::fromHBITMAP(iconInfo.hbmColor, QtWin::HBitmapNoAlpha);

    DeleteObject(iconInfo.hbmColor);
    DeleteObject(iconInfo.hbmMask);
    DestroyIcon(hIcon);

    return pixmap;
}

