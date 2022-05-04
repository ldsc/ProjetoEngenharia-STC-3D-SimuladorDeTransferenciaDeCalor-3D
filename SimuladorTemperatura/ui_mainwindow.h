/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave;
    QAction *actionOpen;
    QAction *actionNew;
    QAction *actionExport_pdf;
    QAction *actionImport_material;
    QAction *actionConfigurar_simula_o;
    QAction *actionAbout;
    QAction *actionConfig;
    QWidget *centralwidget;
    QPushButton *pushButton;
    QTextBrowser *textBrowser_3;
    QFrame *line;
    QWidget *widget_Draw;
    QPushButton *gridDownButton;
    QTextBrowser *textGrid;
    QPushButton *gridUpButton;
    QPushButton *gridAddGrid;
    QPushButton *gridDelGrid;
    QFrame *line_2;
    QCustomPlot *plot1;
    QCustomPlot *plot2;
    QCustomPlot *plot3;
    QCustomPlot *plot4;
    QFrame *line_3;
    QTextBrowser *textBrowser_11;
    QTextBrowser *textBrowser_12;
    QTextBrowser *textBrowser_13;
    QWidget *widget_props;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QCustomPlot *plot_MatProps;
    QWidget *widget_simulator_deltas;
    QTextBrowser *textBrowser_10;
    QLineEdit *input_dz;
    QTextBrowser *textBrowser_9;
    QTextBrowser *textBrowser_8;
    QLineEdit *input_dx;
    QLineEdit *input_dt;
    QComboBox *parallel_comboBox;
    QTextBrowser *textBrowser_6;
    QLineEdit *input_max_iter;
    QTextBrowser *textBrowser_17;
    QLineEdit *input_erro;
    QTextBrowser *textBrowser_18;
    QWidget *widget_drawStyles;
    QTextBrowser *textBrowser_7;
    QTextBrowser *textBrowser_5;
    QDoubleSpinBox *spinBox_Temperature;
    QTextBrowser *textBrowser_4;
    QComboBox *material_comboBox;
    QTextBrowser *textBrowser_16;
    QCheckBox *checkBox_source;
    QTextBrowser *textBrowser_14;
    QSlider *horizontalSliderDrawSize;
    QWidget *widget_buttonCircle;
    QPushButton *buttonCircle;
    QWidget *widget_buttonSquare;
    QPushButton *buttonSquare;
    QWidget *widget_eraser;
    QPushButton *buttonEraser;
    QTextBrowser *textDrawSize;
    QTextBrowser *textMousePosition;
    QFrame *line_4;
    QFrame *line_5;
    QPushButton *button3D;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1516, 900);
        MainWindow->setStyleSheet(QString::fromUtf8("border-bottom-color: rgb(85, 170, 255);"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/fig/icon_novo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/fig/icon_abrir.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/fig/icon_salvar.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon2);
        actionExport_pdf = new QAction(MainWindow);
        actionExport_pdf->setObjectName(QString::fromUtf8("actionExport_pdf"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/fig/icon_pdf.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExport_pdf->setIcon(icon3);
        actionImport_material = new QAction(MainWindow);
        actionImport_material->setObjectName(QString::fromUtf8("actionImport_material"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/fig/new_mat.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImport_material->setIcon(icon4);
        actionConfigurar_simula_o = new QAction(MainWindow);
        actionConfigurar_simula_o->setObjectName(QString::fromUtf8("actionConfigurar_simula_o"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionConfig = new QAction(MainWindow);
        actionConfig->setObjectName(QString::fromUtf8("actionConfig"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(260, 810, 211, 31));
        pushButton->setAcceptDrops(false);
        pushButton->setCheckable(true);
        textBrowser_3 = new QTextBrowser(centralwidget);
        textBrowser_3->setObjectName(QString::fromUtf8("textBrowser_3"));
        textBrowser_3->setGeometry(QRect(300, 850, 461, 31));
        textBrowser_3->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(10, 570, 1511, 21));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        widget_Draw = new QWidget(centralwidget);
        widget_Draw->setObjectName(QString::fromUtf8("widget_Draw"));
        widget_Draw->setGeometry(QRect(20, 80, 661, 481));
        gridDownButton = new QPushButton(widget_Draw);
        gridDownButton->setObjectName(QString::fromUtf8("gridDownButton"));
        gridDownButton->setGeometry(QRect(300, 190, 41, 41));
        gridDownButton->setAcceptDrops(false);
        gridDownButton->setStyleSheet(QString::fromUtf8("border-image: url(:/fig/icon_down.png);"));
        gridDownButton->setCheckable(true);
        textGrid = new QTextBrowser(widget_Draw);
        textGrid->setObjectName(QString::fromUtf8("textGrid"));
        textGrid->setGeometry(QRect(300, 170, 41, 31));
        textGrid->setMouseTracking(false);
        textGrid->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border-color: rgba(255, 255, 255, 0);"));
        textGrid->setLineWidth(0);
        gridUpButton = new QPushButton(widget_Draw);
        gridUpButton->setObjectName(QString::fromUtf8("gridUpButton"));
        gridUpButton->setGeometry(QRect(300, 140, 41, 41));
        gridUpButton->setAcceptDrops(false);
        gridUpButton->setStyleSheet(QString::fromUtf8("border-image: url(:/fig/icon_up.png);"));
        gridUpButton->setCheckable(true);
        gridAddGrid = new QPushButton(widget_Draw);
        gridAddGrid->setObjectName(QString::fromUtf8("gridAddGrid"));
        gridAddGrid->setGeometry(QRect(310, 110, 21, 21));
        gridAddGrid->setAcceptDrops(false);
        gridAddGrid->setStyleSheet(QString::fromUtf8("border-image: url(:/fig/icon_adicionar_camada.png);"));
        gridAddGrid->setCheckable(true);
        gridDelGrid = new QPushButton(widget_Draw);
        gridDelGrid->setObjectName(QString::fromUtf8("gridDelGrid"));
        gridDelGrid->setGeometry(QRect(310, 240, 21, 21));
        gridDelGrid->setAcceptDrops(false);
        gridDelGrid->setStyleSheet(QString::fromUtf8("border-image: url(:/fig/icon_deletar_camada.png);"));
        gridDelGrid->setCheckable(true);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(683, 80, 20, 491));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        plot1 = new QCustomPlot(centralwidget);
        plot1->setObjectName(QString::fromUtf8("plot1"));
        plot1->setGeometry(QRect(710, 80, 391, 231));
        plot2 = new QCustomPlot(centralwidget);
        plot2->setObjectName(QString::fromUtf8("plot2"));
        plot2->setGeometry(QRect(1110, 80, 391, 231));
        plot3 = new QCustomPlot(centralwidget);
        plot3->setObjectName(QString::fromUtf8("plot3"));
        plot3->setGeometry(QRect(710, 330, 391, 231));
        plot4 = new QCustomPlot(centralwidget);
        plot4->setObjectName(QString::fromUtf8("plot4"));
        plot4->setGeometry(QRect(1110, 330, 391, 231));
        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(0, 840, 1511, 21));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        textBrowser_11 = new QTextBrowser(centralwidget);
        textBrowser_11->setObjectName(QString::fromUtf8("textBrowser_11"));
        textBrowser_11->setGeometry(QRect(370, 30, 291, 41));
        textBrowser_11->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
        textBrowser_12 = new QTextBrowser(centralwidget);
        textBrowser_12->setObjectName(QString::fromUtf8("textBrowser_12"));
        textBrowser_12->setGeometry(QRect(20, 30, 291, 41));
        textBrowser_12->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
        textBrowser_13 = new QTextBrowser(centralwidget);
        textBrowser_13->setObjectName(QString::fromUtf8("textBrowser_13"));
        textBrowser_13->setGeometry(QRect(860, 30, 481, 41));
        textBrowser_13->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
        widget_props = new QWidget(centralwidget);
        widget_props->setObjectName(QString::fromUtf8("widget_props"));
        widget_props->setGeometry(QRect(490, 590, 1021, 261));
        widget_props->setStyleSheet(QString::fromUtf8(""));
        scrollArea = new QScrollArea(widget_props);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(10, 10, 181, 241));
        scrollArea->setStyleSheet(QString::fromUtf8("border-color: rgba(255, 255, 255, 0);"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 179, 239));
        scrollArea->setWidget(scrollAreaWidgetContents);
        plot_MatProps = new QCustomPlot(widget_props);
        plot_MatProps->setObjectName(QString::fromUtf8("plot_MatProps"));
        plot_MatProps->setGeometry(QRect(220, 10, 791, 241));
        widget_simulator_deltas = new QWidget(centralwidget);
        widget_simulator_deltas->setObjectName(QString::fromUtf8("widget_simulator_deltas"));
        widget_simulator_deltas->setGeometry(QRect(20, 710, 461, 91));
        textBrowser_10 = new QTextBrowser(widget_simulator_deltas);
        textBrowser_10->setObjectName(QString::fromUtf8("textBrowser_10"));
        textBrowser_10->setGeometry(QRect(290, 10, 51, 31));
        textBrowser_10->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border-color: rgba(255, 255, 255, 0);"));
        input_dz = new QLineEdit(widget_simulator_deltas);
        input_dz->setObjectName(QString::fromUtf8("input_dz"));
        input_dz->setGeometry(QRect(200, 10, 91, 20));
        textBrowser_9 = new QTextBrowser(widget_simulator_deltas);
        textBrowser_9->setObjectName(QString::fromUtf8("textBrowser_9"));
        textBrowser_9->setGeometry(QRect(150, 10, 51, 31));
        textBrowser_9->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border-color: rgba(255, 255, 255, 0);"));
        textBrowser_8 = new QTextBrowser(widget_simulator_deltas);
        textBrowser_8->setObjectName(QString::fromUtf8("textBrowser_8"));
        textBrowser_8->setGeometry(QRect(0, 10, 51, 31));
        textBrowser_8->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border-color: rgba(255, 255, 255, 0);"));
        input_dx = new QLineEdit(widget_simulator_deltas);
        input_dx->setObjectName(QString::fromUtf8("input_dx"));
        input_dx->setGeometry(QRect(50, 10, 91, 20));
        input_dt = new QLineEdit(widget_simulator_deltas);
        input_dt->setObjectName(QString::fromUtf8("input_dt"));
        input_dt->setGeometry(QRect(340, 10, 91, 20));
        parallel_comboBox = new QComboBox(widget_simulator_deltas);
        parallel_comboBox->setObjectName(QString::fromUtf8("parallel_comboBox"));
        parallel_comboBox->setGeometry(QRect(220, 40, 211, 22));
        textBrowser_6 = new QTextBrowser(widget_simulator_deltas);
        textBrowser_6->setObjectName(QString::fromUtf8("textBrowser_6"));
        textBrowser_6->setGeometry(QRect(0, 40, 221, 31));
        textBrowser_6->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border-color: rgba(255, 255, 255, 0);"));
        input_max_iter = new QLineEdit(widget_simulator_deltas);
        input_max_iter->setObjectName(QString::fromUtf8("input_max_iter"));
        input_max_iter->setGeometry(QRect(220, 70, 71, 20));
        textBrowser_17 = new QTextBrowser(widget_simulator_deltas);
        textBrowser_17->setObjectName(QString::fromUtf8("textBrowser_17"));
        textBrowser_17->setGeometry(QRect(150, 70, 71, 31));
        textBrowser_17->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border-color: rgba(255, 255, 255, 0);"));
        input_erro = new QLineEdit(widget_simulator_deltas);
        input_erro->setObjectName(QString::fromUtf8("input_erro"));
        input_erro->setGeometry(QRect(50, 70, 91, 20));
        textBrowser_18 = new QTextBrowser(widget_simulator_deltas);
        textBrowser_18->setObjectName(QString::fromUtf8("textBrowser_18"));
        textBrowser_18->setGeometry(QRect(0, 70, 51, 31));
        textBrowser_18->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border-color: rgba(255, 255, 255, 0);"));
        widget_drawStyles = new QWidget(centralwidget);
        widget_drawStyles->setObjectName(QString::fromUtf8("widget_drawStyles"));
        widget_drawStyles->setGeometry(QRect(20, 590, 461, 111));
        textBrowser_7 = new QTextBrowser(widget_drawStyles);
        textBrowser_7->setObjectName(QString::fromUtf8("textBrowser_7"));
        textBrowser_7->setGeometry(QRect(190, 70, 81, 31));
        textBrowser_7->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border-color: rgba(255, 255, 255, 0);"));
        textBrowser_5 = new QTextBrowser(widget_drawStyles);
        textBrowser_5->setObjectName(QString::fromUtf8("textBrowser_5"));
        textBrowser_5->setGeometry(QRect(120, 80, 51, 31));
        textBrowser_5->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border-color: rgba(255, 255, 255, 0);"));
        spinBox_Temperature = new QDoubleSpinBox(widget_drawStyles);
        spinBox_Temperature->setObjectName(QString::fromUtf8("spinBox_Temperature"));
        spinBox_Temperature->setGeometry(QRect(300, 20, 141, 22));
        textBrowser_4 = new QTextBrowser(widget_drawStyles);
        textBrowser_4->setObjectName(QString::fromUtf8("textBrowser_4"));
        textBrowser_4->setGeometry(QRect(0, 80, 16, 21));
        textBrowser_4->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border-color: rgba(255, 255, 255, 0);"));
        material_comboBox = new QComboBox(widget_drawStyles);
        material_comboBox->setObjectName(QString::fromUtf8("material_comboBox"));
        material_comboBox->setGeometry(QRect(270, 70, 171, 21));
        textBrowser_16 = new QTextBrowser(widget_drawStyles);
        textBrowser_16->setObjectName(QString::fromUtf8("textBrowser_16"));
        textBrowser_16->setGeometry(QRect(40, 0, 81, 31));
        textBrowser_16->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border-color: rgba(255, 255, 255, 0);"));
        checkBox_source = new QCheckBox(widget_drawStyles);
        checkBox_source->setObjectName(QString::fromUtf8("checkBox_source"));
        checkBox_source->setGeometry(QRect(340, 40, 101, 21));
        checkBox_source->setStyleSheet(QString::fromUtf8("\n"
"border-color: rgba(255, 255, 255, 0);"));
        textBrowser_14 = new QTextBrowser(widget_drawStyles);
        textBrowser_14->setObjectName(QString::fromUtf8("textBrowser_14"));
        textBrowser_14->setGeometry(QRect(190, 20, 111, 31));
        textBrowser_14->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border-color: rgba(255, 255, 255, 0);"));
        horizontalSliderDrawSize = new QSlider(widget_drawStyles);
        horizontalSliderDrawSize->setObjectName(QString::fromUtf8("horizontalSliderDrawSize"));
        horizontalSliderDrawSize->setGeometry(QRect(20, 80, 101, 22));
        horizontalSliderDrawSize->setStyleSheet(QString::fromUtf8("\n"
"border-color: rgba(255, 255, 255, 0);"));
        horizontalSliderDrawSize->setMinimum(3);
        horizontalSliderDrawSize->setMaximum(49);
        horizontalSliderDrawSize->setOrientation(Qt::Horizontal);
        widget_buttonCircle = new QWidget(widget_drawStyles);
        widget_buttonCircle->setObjectName(QString::fromUtf8("widget_buttonCircle"));
        widget_buttonCircle->setGeometry(QRect(40, 20, 31, 31));
        buttonCircle = new QPushButton(widget_buttonCircle);
        buttonCircle->setObjectName(QString::fromUtf8("buttonCircle"));
        buttonCircle->setGeometry(QRect(0, 0, 31, 31));
        buttonCircle->setStyleSheet(QString::fromUtf8("image: url(:/fig/circle.png);\n"
"color: rgb(107, 166, 255);\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-color: rgba(255, 255, 255, 0);"));
        buttonCircle->setCheckable(false);
        buttonCircle->setChecked(false);
        widget_buttonSquare = new QWidget(widget_drawStyles);
        widget_buttonSquare->setObjectName(QString::fromUtf8("widget_buttonSquare"));
        widget_buttonSquare->setGeometry(QRect(90, 20, 31, 31));
        buttonSquare = new QPushButton(widget_buttonSquare);
        buttonSquare->setObjectName(QString::fromUtf8("buttonSquare"));
        buttonSquare->setGeometry(QRect(0, 0, 31, 31));
        buttonSquare->setStyleSheet(QString::fromUtf8("image: url(:/fig/square.png);\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-color: rgba(255, 255, 255, 0);"));
        buttonSquare->setCheckable(false);
        buttonSquare->setChecked(false);
        widget_eraser = new QWidget(widget_drawStyles);
        widget_eraser->setObjectName(QString::fromUtf8("widget_eraser"));
        widget_eraser->setGeometry(QRect(0, 20, 31, 31));
        widget_eraser->setStyleSheet(QString::fromUtf8("border-color: rgba(255, 255, 255, 0);"));
        buttonEraser = new QPushButton(widget_eraser);
        buttonEraser->setObjectName(QString::fromUtf8("buttonEraser"));
        buttonEraser->setGeometry(QRect(0, 0, 31, 31));
        buttonEraser->setStyleSheet(QString::fromUtf8("image: url(:/fig/icon_eraser.png);\n"
"background-color: rgba(255, 255, 255, 0);"));
        buttonEraser->setCheckable(false);
        buttonEraser->setChecked(false);
        textDrawSize = new QTextBrowser(widget_drawStyles);
        textDrawSize->setObjectName(QString::fromUtf8("textDrawSize"));
        textDrawSize->setGeometry(QRect(0, 50, 171, 31));
        textDrawSize->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border-color: rgba(255, 255, 255, 0);"));
        textMousePosition = new QTextBrowser(centralwidget);
        textMousePosition->setObjectName(QString::fromUtf8("textMousePosition"));
        textMousePosition->setGeometry(QRect(0, 850, 301, 31));
        textMousePosition->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
        line_4 = new QFrame(centralwidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(10, 60, 1511, 21));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(centralwidget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setGeometry(QRect(10, 10, 1511, 21));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        button3D = new QPushButton(centralwidget);
        button3D->setObjectName(QString::fromUtf8("button3D"));
        button3D->setEnabled(true);
        button3D->setGeometry(QRect(20, 810, 211, 31));
        button3D->setAcceptDrops(false);
        button3D->setCheckable(false);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1516, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionExport_pdf);
        menuFile->addAction(actionImport_material);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
        actionExport_pdf->setText(QCoreApplication::translate("MainWindow", "Export pdf", nullptr));
        actionImport_material->setText(QCoreApplication::translate("MainWindow", "Import material", nullptr));
        actionConfigurar_simula_o->setText(QCoreApplication::translate("MainWindow", "Simulation options", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionConfig->setText(QCoreApplication::translate("MainWindow", "Config.", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
        textBrowser_3->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        gridDownButton->setText(QString());
        textGrid->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">1</span></p></body></html>", nullptr));
        gridUpButton->setText(QString());
        gridAddGrid->setText(QString());
        gridDelGrid->setText(QString());
        textBrowser_11->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">Temperatura do objeto</span></p></body></html>", nullptr));
        textBrowser_12->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">Disposi\303\247\303\243o dos Materiais</span></p></body></html>", nullptr));
        textBrowser_13->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">Evolu\303\247\303\243o da Temperatura</span></p></body></html>", nullptr));
        textBrowser_10->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">dt -&gt;</span></p></body></html>", nullptr));
        textBrowser_9->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">dz -&gt;</span></p></body></html>", nullptr));
        textBrowser_8->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">dx -&gt;</span></p></body></html>", nullptr));
        textBrowser_6->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">Velocidade da simula\303\247\303\243o-&gt;</span></p></body></html>", nullptr));
        textBrowser_17->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">MAX ITER</span></p></body></html>", nullptr));
        textBrowser_18->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Erro</p></body></html>", nullptr));
        textBrowser_7->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">Material-&gt;</span></p></body></html>", nullptr));
        textBrowser_5->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">150</p></body></html>", nullptr));
        textBrowser_4->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:7pt;\">2</span></p></body></html>", nullptr));
        textBrowser_16->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">Objeto</span></p></body></html>", nullptr));
        checkBox_source->setText(QCoreApplication::translate("MainWindow", "Fonte de Calor", nullptr));
        textBrowser_14->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">Temperatura-&gt;</span></p></body></html>", nullptr));
        buttonCircle->setText(QString());
        buttonSquare->setText(QString());
        buttonEraser->setText(QString());
        textDrawSize->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        textMousePosition->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        button3D->setText(QCoreApplication::translate("MainWindow", "3D", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
