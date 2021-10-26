#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    simulador = new CSimuladorTemperatura();
    simulador->resetSize(size, size);
    ui->setupUi(this);
    mImage = new QImage(size*2+space_between_draws, size,QImage::Format_ARGB32_Premultiplied);
    timerId = startTimer(200);

    ui->plot1->addGraph();
    ui->plot2->addGraph();
    ui->plot3->addGraph();
    ui->plot4->addGraph();
    ui->plot1->xAxis->setLabel("tempo (s)");
    ui->plot1->yAxis->setLabel("temperatura (K)");
    ui->plot2->xAxis->setLabel("eixo z (m)");
    ui->plot2->yAxis->setLabel("temperatura (K)");
    ui->plot3->xAxis->setLabel("eixo x (m)");
    ui->plot3->yAxis->setLabel("temperatura (K)");
    ui->plot4->xAxis->setLabel("eixo y (m)");
    ui->plot4->yAxis->setLabel("temperatura (K)");
    start_buttons();
}

MainWindow::~MainWindow() {
    delete mImage;
    delete simulador;
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->buttons() == Qt::LeftButton){
        std::string actualMaterial = ui->material_comboBox->currentText().toStdString();
        double temperature = std::stod(ui->temperature_input->text().toStdString());
        bool isSource = ui->checkBox_source->checkState();
        std::string drawFormat = ui->drawFormat->currentText().toStdString();
        int size = ui->horizontalSliderDrawSize->value();
        simulador->setActualTemperature(temperature); /// importante para atualizar Tmin/Tmax

        if (drawFormat =="circulo")
            simulador->grid[currentGrid]->draw_cir(event->pos().x()-left_margin, event->pos().y()-up_margin, size/2, temperature, isSource, simulador->getMaterial(actualMaterial));
        else
            simulador->grid[currentGrid]->draw_rec(event->pos().x()-left_margin, event->pos().y()-up_margin, size, temperature, isSource, simulador->getMaterial(actualMaterial));
    }
    else if (event->buttons() == Qt::RightButton){
        studyPoint = QPoint(event->pos().x()-left_margin, event->pos().y()-up_margin);
        studyGrid = currentGrid;
        time.clear();
        temperature.clear();
    }
    update();
}

void MainWindow::start_buttons(){
    ui->textBrowser_2->setFrameStyle(QFrame::NoFrame);
    ui->textBrowser_3->setFrameStyle(QFrame::NoFrame);
    ui->textBrowser_4->setFrameStyle(QFrame::NoFrame);
    ui->textBrowser_5->setFrameStyle(QFrame::NoFrame);
    ui->textBrowser_6->setFrameStyle(QFrame::NoFrame);
    ui->textBrowser_7->setFrameStyle(QFrame::NoFrame);
    /// texto do grid
    ui->textGrid->setFrameStyle(QFrame::NoFrame);
    ui->textGrid->setText(QString::fromStdString(std::to_string(currentGrid)));

    /// lista de materiais
    std::vector<std::string> materiais = simulador->getMateriais();
    for (unsigned int i = 0; i < materiais.size(); i++)
        ui->material_comboBox->addItem(QString::fromStdString(materiais[i]));

    /// design para desenho
    ui->drawFormat->addItem("circulo");
    ui->drawFormat->addItem("quadrado");

    ui->horizontalSliderDrawSize->setMinimum(2);
    ui->horizontalSliderDrawSize->setMaximum(150);
    ui->horizontalSliderDrawSize->setValue(50);

    /// lista de paralelismo
    ui->parallel_comboBox->addItem("Paralelismo total");
    ui->parallel_comboBox->addItem("Sem paralelismo");
    ui->parallel_comboBox->addItem("Paralelismo por grid");

    /// texto do imput de temperatura
    ui->temperature_input->setText(QString::fromStdString(std::to_string(simulador->get_ActualTemperature())));
}

void MainWindow::paintEvent(QPaintEvent *e) {
    QPainter painter(this);

    /// first draw
    for (int i = 0; i < size; i++){
        for (int k = 0; k < size; k++){
            if (!simulador->grid[currentGrid]->operator()(i, k)->active)
                mImage->setPixelColor(i,k, QColor::fromRgb(255,255,255));
            else
                mImage->setPixelColor(i,k, calcRGB(simulador->grid[currentGrid]->operator()(i, k)->temp));
        }
    }

    for(int i = 0; i < size; i++){
        mImage->setPixelColor(i,studyPoint.y(), QColor::fromRgb(0,0,0));
        mImage->setPixelColor(studyPoint.x(), i, QColor::fromRgb(0,0,0));
    }

    /// second draw
    for (int i = 0; i < size; i++){
        for (int k = 0; k < size; k++){
            if (!simulador->grid[currentGrid]->operator()(i, k)->active)
                mImage->setPixelColor(i+size+space_between_draws,k, QColor::fromRgb(255,255,255));
            else
                mImage->setPixelColor(i+size+space_between_draws,k, simulador->grid[currentGrid]->operator()(i, k)->material->getColor());
        }
    }
    painter.drawImage(left_margin,up_margin, *mImage);
    e->accept();
}

QColor MainWindow::calcRGB(double temperatura){
    double maxTemp = simulador->getTmax();
    double minTemp = simulador->getTmin();
    return QColor::fromRgb(255, (maxTemp - temperatura)*255/(maxTemp - minTemp), 0, 255);
}

void MainWindow::runSimulator(){
    time_t start_time = std::time(0);
    std::string type = ui->parallel_comboBox->currentText().toStdString();
    if(type == "Sem paralelismo")
        simulador->run_sem_paralelismo();
    if(type=="Paralelismo por grid")
        simulador->run_paralelismo_por_grid();
    if(type=="Paralelismo total")
        simulador->run_paralelismo_total();
    time.append((time.size()+1)*simulador->getDelta_t());

    std::string result = "Time: " + std::to_string(time[time.size()-1]) + " - duracao do solver: " + std::to_string(std::time(0) - start_time) + " seg";
    ui->textBrowser_3->setText(QString::fromStdString(result));

    update();
    makePlot1();
    makePlot2();
    makePlot3();
    makePlot4();
}

void MainWindow::timerEvent(QTimerEvent *e){
    Q_UNUSED(e);
    if (runningSimulator){
        runSimulator();
    }
}

void MainWindow::on_pushButton_clicked()
{
    runningSimulator = runningSimulator?false:true;
}

void MainWindow::on_gridDownButton_clicked()
{
    currentGrid--;
    if (currentGrid < 0)
        currentGrid = 0;
    /// texto do grid
    ui->textGrid->setText(QString::fromStdString(std::to_string(currentGrid)));
    update();
}

void MainWindow::on_gridUpButton_clicked()
{
    currentGrid++;
    if (currentGrid > simulador->getNGRIDS()-1)
        currentGrid = simulador->getNGRIDS()-1;
    /// texto do grid
    ui->textGrid->setText(QString::fromStdString(std::to_string(currentGrid)));
    update();
}

void MainWindow::makePlot1(){
    temperature.append(simulador->grid[studyGrid]->operator()(studyPoint.x(), studyPoint.y())->temp);

    ui->plot1->graph(0)->setData(time,temperature);
    ui->plot1->xAxis->setRange(time[0], time[time.size()-1]+1);
    ui->plot1->yAxis->setRange(simulador->getTmin()-50, simulador->getTmax()+50);
    ui->plot1->replot();
    ui->plot1->update();
}

void MainWindow::makePlot2(){
    QVector<double> temperature_z(simulador->getNGRIDS());
    QVector<double> labor_z(simulador->getNGRIDS());
    for (int i = 0; i < simulador->getNGRIDS(); i++){
        labor_z[i] = simulador->getDelta_z()*(i+1);
        temperature_z[i] = simulador->grid[i]->operator()(studyPoint.x(), studyPoint.y())->temp;
    }

    ui->plot2->graph(0)->setData(labor_z,temperature_z);
    ui->plot2->xAxis->setRange(labor_z[0], labor_z[labor_z.size()-1]);
    ui->plot2->yAxis->setRange(simulador->getTmin()-50, simulador->getTmax()+50);
    ui->plot2->replot();
    ui->plot2->update();
}

void MainWindow::makePlot3(){
    QVector<double> temperature_x(size);
    QVector<double> labor_x(size);
    for (int i = 0; i < size; i++){
        labor_x[i] = simulador->getDelta_x()*(i+1);
        temperature_x[i] = simulador->grid[studyGrid]->operator()(i, studyPoint.y())->temp;
    }

    ui->plot3->graph(0)->setData(labor_x,temperature_x);
    ui->plot3->xAxis->setRange(labor_x[0], labor_x[size-1]);
    ui->plot3->yAxis->setRange(simulador->getTmin()-50, simulador->getTmax()+50);
    ui->plot3->replot();
    ui->plot3->update();
}

void MainWindow::makePlot4(){
    QVector<double> temperature_y(size);
    QVector<double> labor_y(size);
    for (int i = 0; i < size; i++){
        labor_y[i] = simulador->getDelta_x()*(i+1);
        temperature_y[i] = simulador->grid[studyGrid]->operator()(studyPoint.x(), i)->temp;
    }

    ui->plot4->graph(0)->setData(labor_y,temperature_y);
    ui->plot4->xAxis->setRange(labor_y[0], labor_y[size-1]);
    ui->plot4->yAxis->setRange(simulador->getTmin()-50, simulador->getTmax()+50);
    ui->plot4->replot();
    ui->plot4->update();
}

void MainWindow::on_actionSave_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Save a file", "C://Users//nicholas//Desktop//ProjetoEngenharia//Projeto-TCC-SimuladorDifusaoTermica//SimuladorTemperatura//save", tr("Dados (*.dat)"));
    simulador->saveGrid(file_name.toStdString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", "C://Users//nicholas//Desktop//ProjetoEngenharia//Projeto-TCC-SimuladorDifusaoTermica//SimuladorTemperatura//save", tr("Dados (*.dat)"));
    simulador->openGrid(file_name.toStdString());
}

void MainWindow::on_actionNew_triggered()
{
    simulador->resetGrid();
    update();
}

