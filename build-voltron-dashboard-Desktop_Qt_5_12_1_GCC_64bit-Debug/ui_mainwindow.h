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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Widgets/BatteryWidget.h"
#include "Widgets/ConsoleWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    BatteryWidget *batteryWidget;
    QFrame *frame;
    QPushButton *batteryReadButton;
    QTableWidget *batteryTable;
    ConsoleWidget *consoleWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextBrowser *consoleBrowser;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(983, 604);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        batteryWidget = new BatteryWidget(centralWidget);
        batteryWidget->setObjectName(QString::fromUtf8("batteryWidget"));
        frame = new QFrame(batteryWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 551, 271));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        batteryReadButton = new QPushButton(frame);
        batteryReadButton->setObjectName(QString::fromUtf8("batteryReadButton"));
        batteryReadButton->setGeometry(QRect(210, 10, 141, 31));
        batteryReadButton->setCheckable(true);
        batteryReadButton->setFlat(false);
        batteryTable = new QTableWidget(frame);
        if (batteryTable->columnCount() < 2)
            batteryTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        batteryTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        batteryTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        batteryTable->setObjectName(QString::fromUtf8("batteryTable"));
        batteryTable->setGeometry(QRect(5, 70, 541, 192));
        batteryTable->setColumnCount(2);
        batteryTable->horizontalHeader()->setStretchLastSection(true);
        batteryTable->verticalHeader()->setVisible(false);

        verticalLayout_2->addWidget(batteryWidget);

        consoleWidget = new ConsoleWidget(centralWidget);
        consoleWidget->setObjectName(QString::fromUtf8("consoleWidget"));
        verticalLayout = new QVBoxLayout(consoleWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(consoleWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setAutoFillBackground(true);
        label->setFrameShape(QFrame::StyledPanel);
        label->setFrameShadow(QFrame::Plain);
        label->setLineWidth(1);
        label->setMidLineWidth(0);

        verticalLayout->addWidget(label);

        consoleBrowser = new QTextBrowser(consoleWidget);
        consoleBrowser->setObjectName(QString::fromUtf8("consoleBrowser"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(consoleBrowser->sizePolicy().hasHeightForWidth());
        consoleBrowser->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(consoleBrowser);


        verticalLayout_2->addWidget(consoleWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 983, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());

        retranslateUi(MainWindow);
        QObject::connect(batteryReadButton, SIGNAL(clicked()), batteryWidget, SLOT(onStartReading()));
        QObject::connect(batteryReadButton, SIGNAL(clicked()), consoleWidget, SLOT(onStartReading()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        batteryReadButton->setText(QApplication::translate("MainWindow", "Read Data", nullptr));
        QTableWidgetItem *___qtablewidgetitem = batteryTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Cell Number", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = batteryTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Charge Level", nullptr));
        label->setText(QApplication::translate("MainWindow", "Console", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
