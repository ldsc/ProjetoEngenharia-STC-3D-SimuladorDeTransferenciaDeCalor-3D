#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QDir>                  ///< Biblioteca que permite acessar diretórios.
#include <QImage>                /// desenhar pixels
#include <QColor>                /// escolher a cor dos pixels
#include <string>
#include <iostream>
#include <QPainter>              /// desenhar pixels
#include <QPrinter>              ///< Biblioteca  que habilita a geração de pdf.
#include <QPainter>              ///< Biblioteca que auxilia a geração do pdf.
#include <QPdfWriter>
#include <QMainWindow>
#include <QMouseEvent>           /// pegar acoes/posicao do mouse
#include <QFileDialog>
#include <QDirIterator>

#include "C3D.h"
#include "ui_mainwindow.h"
#include "CSimuladorTemperatura.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPoint m_mousePos;
    QPixmap pixmap;
    QImage *mImage;
    QWidget* checkboxes;
    QVBoxLayout* layout;
    std::vector<QCheckBox*> myCheckbox;
    CSimuladorTemperatura *simulador;
    std::string drawFormat = "circulo";

    int timerId;
    int parallelType = 2;
    int size_x = 300, size_y = 480;
    int currentGrid = 0;
    int space_between_draws = 50;
    int left_margin = 20, up_margin = 140;
    bool runningSimulator = false;
    bool eraserActivated = false;
    QPoint studyPoint = QPoint(0,0);
    int studyGrid;
    std::vector<bool> selectedMateriails;
    QVector<double> time, temperature;

protected:
    void start_buttons();
    void mousePressEvent(QMouseEvent *event) override;
    void printPosition();
    void printDrawSize();
    void paintEvent(QPaintEvent *e) override;
    QImage paint(int grid);

    QColor calcRGB(double temperatura);
    void runSimulator();
    void timerEvent(QTimerEvent *e) override;

private slots:
    void on_pushButton_clicked();
    void on_gridDownButton_clicked();
    void on_gridUpButton_clicked();

    void createWidgetProps();

    void makePlot1();
    void makePlot2();
    void makePlot3();
    void makePlot4();
    void makePlotMatProps();
    bool checkChangeMaterialsState();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actionNew_triggered();
    void on_actionExport_pdf_triggered();
    QString save_pdf(QString file_name);
    void on_buttonCircle_clicked();
    void on_buttonSquare_clicked();
    void on_actionImport_material_triggered();
    void on_gridAddGrid_clicked();
    void on_gridDelGrid_clicked();
    void on_buttonEraser_clicked();
    void on_button3D_clicked();
};
#endif
