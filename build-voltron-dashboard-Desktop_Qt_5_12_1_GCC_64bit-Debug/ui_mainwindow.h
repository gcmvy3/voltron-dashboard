/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Widgets/BatteryWidget.h"
#include "Widgets/CANWidget.h"
#include "Widgets/ConsoleWidget.h"
#include "Widgets/LidarWidget.h"
#include "Widgets/LoggingWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_11;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QSplitter *splitter_2;
    QSplitter *splitter;
    LidarWidget *lidarWidget;
    LoggingWidget *loggingWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *endDriveButton;
    QPushButton *startDriveButton;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QPushButton *canRecordButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QPushButton *lidarRecordButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QPushButton *gpsRecordButton;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QPushButton *cameraRecordButton;
    QSpacerItem *verticalSpacer;
    ConsoleWidget *consoleWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextBrowser *consoleBrowser;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_7;
    LidarWidget *lidarWidget_2;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_6;
    BatteryWidget *batteryWidget_2;
    QVBoxLayout *verticalLayout_8;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *verticalLayout_10;
    QLabel *batteryLabel_2;
    QFrame *line_2;
    QTableWidget *batteryTable_2;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_12;
    CANWidget *canWidget;
    QVBoxLayout *verticalLayout_13;
    QPushButton *loadCANFileButton;
    QTableWidget *CANCodesTable;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(983, 604);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(211, 215, 207)"));
        verticalLayout_11 = new QVBoxLayout(centralWidget);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setStyleSheet(QString::fromUtf8("QTabBar{font: 14pt;}\n"
"QTabBar::tab { height: 40%;}"));
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setDocumentMode(false);
        tabWidget->setMovable(false);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        splitter_2 = new QSplitter(tab);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        splitter_2->setChildrenCollapsible(false);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(10);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setLayoutDirection(Qt::RightToLeft);
        splitter->setOrientation(Qt::Horizontal);
        lidarWidget = new LidarWidget(splitter);
        lidarWidget->setObjectName(QString::fromUtf8("lidarWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(4);
        sizePolicy1.setVerticalStretch(5);
        sizePolicy1.setHeightForWidth(lidarWidget->sizePolicy().hasHeightForWidth());
        lidarWidget->setSizePolicy(sizePolicy1);
        splitter->addWidget(lidarWidget);
        loggingWidget = new LoggingWidget(splitter);
        loggingWidget->setObjectName(QString::fromUtf8("loggingWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(5);
        sizePolicy2.setHeightForWidth(loggingWidget->sizePolicy().hasHeightForWidth());
        loggingWidget->setSizePolicy(sizePolicy2);
        loggingWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236)"));
        verticalLayout_3 = new QVBoxLayout(loggingWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_6 = new QLabel(loggingWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy3);

        verticalLayout_3->addWidget(label_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);
        endDriveButton = new QPushButton(loggingWidget);
        endDriveButton->setObjectName(QString::fromUtf8("endDriveButton"));
        endDriveButton->setEnabled(false);
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(endDriveButton->sizePolicy().hasHeightForWidth());
        endDriveButton->setSizePolicy(sizePolicy4);
        endDriveButton->setMinimumSize(QSize(0, 40));

        horizontalLayout_5->addWidget(endDriveButton);

        startDriveButton = new QPushButton(loggingWidget);
        startDriveButton->setObjectName(QString::fromUtf8("startDriveButton"));
        sizePolicy4.setHeightForWidth(startDriveButton->sizePolicy().hasHeightForWidth());
        startDriveButton->setSizePolicy(sizePolicy4);
        startDriveButton->setMinimumSize(QSize(0, 40));

        horizontalLayout_5->addWidget(startDriveButton);


        verticalLayout_3->addLayout(horizontalLayout_5);

        groupBox = new QGroupBox(loggingWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy5);
        groupBox->setLayoutDirection(Qt::LeftToRight);
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_2);

        canRecordButton = new QPushButton(groupBox);
        canRecordButton->setObjectName(QString::fromUtf8("canRecordButton"));
        canRecordButton->setEnabled(false);

        horizontalLayout->addWidget(canRecordButton);


        verticalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_3);

        lidarRecordButton = new QPushButton(groupBox);
        lidarRecordButton->setObjectName(QString::fromUtf8("lidarRecordButton"));
        lidarRecordButton->setEnabled(false);

        horizontalLayout_2->addWidget(lidarRecordButton);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_4);

        gpsRecordButton = new QPushButton(groupBox);
        gpsRecordButton->setObjectName(QString::fromUtf8("gpsRecordButton"));
        gpsRecordButton->setEnabled(false);

        horizontalLayout_3->addWidget(gpsRecordButton);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_5);

        cameraRecordButton = new QPushButton(groupBox);
        cameraRecordButton->setObjectName(QString::fromUtf8("cameraRecordButton"));
        cameraRecordButton->setEnabled(false);

        horizontalLayout_4->addWidget(cameraRecordButton);


        verticalLayout_4->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        verticalLayout_3->addWidget(groupBox);

        splitter->addWidget(loggingWidget);
        splitter_2->addWidget(splitter);
        consoleWidget = new ConsoleWidget(splitter_2);
        consoleWidget->setObjectName(QString::fromUtf8("consoleWidget"));
        consoleWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236)"));
        verticalLayout = new QVBoxLayout(consoleWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(consoleWidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);
        label->setAutoFillBackground(false);
        label->setFrameShape(QFrame::VLine);
        label->setFrameShadow(QFrame::Plain);
        label->setLineWidth(1);
        label->setMidLineWidth(0);

        verticalLayout->addWidget(label);

        consoleBrowser = new QTextBrowser(consoleWidget);
        consoleBrowser->setObjectName(QString::fromUtf8("consoleBrowser"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(consoleBrowser->sizePolicy().hasHeightForWidth());
        consoleBrowser->setSizePolicy(sizePolicy6);

        verticalLayout->addWidget(consoleBrowser);

        splitter_2->addWidget(consoleWidget);

        verticalLayout_2->addWidget(splitter_2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_7 = new QVBoxLayout(tab_2);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        lidarWidget_2 = new LidarWidget(tab_2);
        lidarWidget_2->setObjectName(QString::fromUtf8("lidarWidget_2"));

        verticalLayout_7->addWidget(lidarWidget_2);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_6 = new QVBoxLayout(tab_3);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        batteryWidget_2 = new BatteryWidget(tab_3);
        batteryWidget_2->setObjectName(QString::fromUtf8("batteryWidget_2"));
        batteryWidget_2->setMinimumSize(QSize(200, 200));
        batteryWidget_2->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_8 = new QVBoxLayout(batteryWidget_2);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        frame_2 = new QFrame(batteryWidget_2);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236)"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_9 = new QVBoxLayout(frame_2);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        batteryLabel_2 = new QLabel(frame_2);
        batteryLabel_2->setObjectName(QString::fromUtf8("batteryLabel_2"));
        QFont font;
        font.setPointSize(14);
        batteryLabel_2->setFont(font);
        batteryLabel_2->setAutoFillBackground(false);
        batteryLabel_2->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(batteryLabel_2);

        line_2 = new QFrame(frame_2);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_10->addWidget(line_2);

        batteryTable_2 = new QTableWidget(frame_2);
        if (batteryTable_2->columnCount() < 2)
            batteryTable_2->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        batteryTable_2->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        batteryTable_2->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        batteryTable_2->setObjectName(QString::fromUtf8("batteryTable_2"));
        batteryTable_2->setColumnCount(2);
        batteryTable_2->horizontalHeader()->setStretchLastSection(true);
        batteryTable_2->verticalHeader()->setVisible(false);

        verticalLayout_10->addWidget(batteryTable_2);


        verticalLayout_9->addLayout(verticalLayout_10);


        verticalLayout_8->addWidget(frame_2);


        verticalLayout_6->addWidget(batteryWidget_2);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_12 = new QVBoxLayout(tab_4);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        canWidget = new CANWidget(tab_4);
        canWidget->setObjectName(QString::fromUtf8("canWidget"));
        verticalLayout_13 = new QVBoxLayout(canWidget);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        loadCANFileButton = new QPushButton(canWidget);
        loadCANFileButton->setObjectName(QString::fromUtf8("loadCANFileButton"));
        loadCANFileButton->setFont(font);

        verticalLayout_13->addWidget(loadCANFileButton);

        CANCodesTable = new QTableWidget(canWidget);
        if (CANCodesTable->columnCount() < 6)
            CANCodesTable->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        CANCodesTable->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        CANCodesTable->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        CANCodesTable->setHorizontalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font);
        CANCodesTable->setHorizontalHeaderItem(3, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font);
        CANCodesTable->setHorizontalHeaderItem(4, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font);
        CANCodesTable->setHorizontalHeaderItem(5, __qtablewidgetitem7);
        CANCodesTable->setObjectName(QString::fromUtf8("CANCodesTable"));
        CANCodesTable->setFont(font);
        CANCodesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        CANCodesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        CANCodesTable->setColumnCount(6);
        CANCodesTable->horizontalHeader()->setDefaultSectionSize(124);
        CANCodesTable->horizontalHeader()->setStretchLastSection(true);
        CANCodesTable->verticalHeader()->setVisible(false);

        verticalLayout_13->addWidget(CANCodesTable);


        verticalLayout_12->addWidget(canWidget);

        tabWidget->addTab(tab_4, QString());

        verticalLayout_11->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 983, 22));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(batteryTable_2, loadCANFileButton);
        QWidget::setTabOrder(loadCANFileButton, CANCodesTable);
        QWidget::setTabOrder(CANCodesTable, tabWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Voltron Dashboard", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Drive Controls", nullptr));
        endDriveButton->setText(QApplication::translate("MainWindow", "End Drive", nullptr));
        startDriveButton->setText(QApplication::translate("MainWindow", "Start Drive", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Recordings", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "CAN Messages", nullptr));
        canRecordButton->setText(QApplication::translate("MainWindow", "Start Recording", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "LIDAR", nullptr));
        lidarRecordButton->setText(QApplication::translate("MainWindow", "Start Recording", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "GPS", nullptr));
        gpsRecordButton->setText(QApplication::translate("MainWindow", "Start Recording", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Depth Camera", nullptr));
        cameraRecordButton->setText(QApplication::translate("MainWindow", "Start Recording", nullptr));
        label->setText(QApplication::translate("MainWindow", "Console", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Home", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "LIDAR", nullptr));
        batteryLabel_2->setText(QApplication::translate("MainWindow", "Battery Data", nullptr));
        QTableWidgetItem *___qtablewidgetitem = batteryTable_2->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Cell Number", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = batteryTable_2->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Charge Level", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Battery", nullptr));
        loadCANFileButton->setText(QApplication::translate("MainWindow", "Load CAN Code File", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = CANCodesTable->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = CANCodesTable->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = CANCodesTable->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Sender ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = CANCodesTable->horizontalHeaderItem(3);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Start Bit", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = CANCodesTable->horizontalHeaderItem(4);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "End Bit", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = CANCodesTable->horizontalHeaderItem(5);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "Value", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "CAN", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
