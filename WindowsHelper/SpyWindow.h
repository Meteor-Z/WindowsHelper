#pragma once

// VS������������Ľ��
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")// ��ָ���֧��VS����
#endif

#include <Windows.h>
#include <QWidget>
#include <QPushButton>
#include <QTreeWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <qTableWidget>
#include <QStringList>
#include <QMouseEvent>
#include "ui_SpyWindow.h"


// �������е�С����
class SpyWindow : public QWidget
{
	Q_OBJECT

public:
	SpyWindow(QWidget *parent = nullptr);
	~SpyWindow();

protected:
// ��д�˷�������Ҫ��ͼ��ı���
	void paintEvent(QPaintEvent* e) override;
private:
	// ���ϲ��һϵ����Ϣ
	void initTopButton();

	// ��ʼ�����в��ֵ���Ϣ��
	void initAllLayout();
	// �������еĲ�����Ϣ
	void setAllLayout();

	// ��ʼ�����½ǵ��ǹ��ڴ�����Ϣ��Layout
	void initLeftButtomWindowLayout();

	// ��ʼ���������Ե���һ��
	void initAttributesLayout();

	// ��ʼ��������
	void initFunctionLayout();

	// ��ʼ�����
	void initTableWidget();

	// ��������Button����ʽ
	void setAllButtonStyle();
	
	// ��������CheckBox����ʽ 
	void setAllCheckBoxSytle();

	// �������е��źŲ�
	void setAllSingalSlot();

	// ��TableWidget������ӱ���
	void addTitleRow(const QString& title);


	// �����Ϣ���������ڿ���ֱ�Ӵ��ļ��ж�ȡ
	void addRow(const QStringList& data);

	// �źŲۣ��ı䵱ǰ�������ʽ
	void changeCursor();


	// �ظ�������ʽ�����Ҵ洢��ǰ���ڵľ��
	void restoreCursor();

	void getPointWindowHandle();

	bool eventFilter(QObject* obj, QEvent* event) override;

private:
	Ui::SpyWindowClass ui;
	QTreeWidget* m_WindowTree{}; // ���ڵ�Tree
	QVBoxLayout* m_MainLayout{}; // ���²��ֵ�������
	
	QHBoxLayout* m_TopLayout{}; // ���水ť�Ĳ���
	QHBoxLayout* m_ButtomLayout{}; // �������ҵ�Layout

	QPushButton* m_BasicInfoButton{};// ������Ϣ
	QPushButton* m_CommonOperationsButton{}; // ���ò���
	QLabel* m_FindWindowlabel{}; // �鿴����
	QLineEdit* m_FindWindowLineEdit{}; // ����򣬲���


	QVBoxLayout* m_LeftButtomLayout{}; // ���½ǵ�Layout


	QGridLayout* m_LeftButtomWindowGridLayout{}; // ���½Ǵ�����صĵ�Layout 

	QPushButton* m_ShootButton{}; // ��׼��ͼ��,��ʵ��Ҳ��֪�������ôʵ�ֵġ���
	bool m_ShootButtonIsPress{false}; // �Ƿ��Ѿ�������

	QLineEdit* m_WindowHandleLineEdit{}; // ���ھ��
	QLineEdit* m_WindowTitleLineEdit{}; // ���ڱ�ǩ
	QLineEdit* m_WindowPosLineEdit{}; // ����λ��
	QPushButton* m_FlushButton{}; // ˢ��Button

	QCheckBox* m_VisableCheckBox{}; // ���ӻ�
	QCheckBox* m_StopMoveCheckBox{}; // ��ֹ
	QCheckBox* m_TopWindowCheckBox{}; // �ö�
	QCheckBox* m_TransparentCheckBox{}; // ͸��

	QHBoxLayout* m_AttributesLeftLayout{}; // ���������Buttom

	QGridLayout* m_FunctionGridLayout{}; // ���½ǹ������Ĳ���

	QLineEdit* m_TopLevelLineEdit{}; // ��������
	QPushButton* m_TopLevelPushButton{}; // ̽�ⶥ������

	QLineEdit* m_ParentLineEdit{}; // ������
	QPushButton* m_ParentPushButton{}; // ̽�⸸����

	QLineEdit* m_PreviewLineEdit{}; // ��һ����
	QPushButton* m_PreviewPushButton{}; // ̽����һ������

	QLineEdit* m_NextLineEdit{}; // ��һ����
	QPushButton* m_NextPushButton{}; // ̽����һ������

	QLineEdit* m_ProgramPathLineEdit{}; // ����·��
	QPushButton* m_ProgramPathPushButton{}; // �򿪳���·��

	QTableWidget* m_InfoTableWidget{}; // �����ʾ������Ϣ



	
	
	
	
	

};
