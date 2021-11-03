#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    up_margin = 100;
    //std::cout<<ui->widget->pos().y();
    simulador = new CSimuladorTemperatura();
    simulador->resetSize(size_x, size_y);
    ui->setupUi(this);
    mImage = new QImage(size_x*2+space_between_draws, size_y,QImage::Format_ARGB32_Premultiplied);
    timerId = startTimer(200);

    ui->plot1->addGraph();
    ui->plot2->addGraph();
    ui->plot3->addGraph();
    ui->plot4->addGraph();
    ui->plot_MatProps->addGraph();
    ui->plot1->xAxis->setLabel("tempo (s)");
    ui->plot1->yAxis->setLabel("temperatura (K)");
    ui->plot2->xAxis->setLabel("eixo z (m)");
    ui->plot2->yAxis->setLabel("temperatura (K)");
    ui->plot3->xAxis->setLabel("eixo x (m)");
    ui->plot3->yAxis->setLabel("temperatura (K)");
    ui->plot4->xAxis->setLabel("eixo y (m)");
    ui->plot4->yAxis->setLabel("temperatura (K)");
    ui->plot_MatProps->xAxis->setLabel("Temperatura (K)");
    ui->plot_MatProps->yAxis->setLabel("props");

    for(unsigned int i = 0; i < simulador->getMateriais().size();i++)
        ui->plot_MatProps->addGraph();
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
        int x = event->pos().x()-left_margin;
        int y = event->pos().y()-up_margin;
        if (x >= 0 && x < size_x && y >= 0 && y < size_y){
            studyPoint = QPoint(x, y);
            studyGrid = currentGrid;
            time.clear();
            temperature.clear();
        }
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
    ui->textBrowser_8->setFrameStyle(QFrame::NoFrame);
    ui->textBrowser_9->setFrameStyle(QFrame::NoFrame);
    ui->textBrowser_10->setFrameStyle(QFrame::NoFrame);
    ui->textBrowser_11->setFrameStyle(QFrame::NoFrame);
    ui->textBrowser_12->setFrameStyle(QFrame::NoFrame);
    ui->textBrowser_13->setFrameStyle(QFrame::NoFrame);

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

    ui->input_dt->setText(QString::fromStdString(std::to_string(simulador->getDelta_t())));
    ui->input_dx->setText(QString::fromStdString(std::to_string(simulador->getDelta_x())));
    ui->input_dz->setText(QString::fromStdString(std::to_string(simulador->getDelta_z())));

    /// scroll com os materiais para o gráfico
    checkboxes = new QWidget(ui->scrollArea);
    layout = new QVBoxLayout(checkboxes);
    myCheckbox.resize(materiais.size());
    selectedMateriails.resize(materiais.size(), false);

    for(unsigned int i = 0; i < materiais.size(); i++){
        myCheckbox[i] = new QCheckBox(QString::fromStdString(materiais[i]), checkboxes);
        layout->addWidget(myCheckbox[i]);
    }
    ui->scrollArea->setWidget(checkboxes);
    makePlotMatProps();
}

void MainWindow::paintEvent(QPaintEvent *e) {
    QPainter painter(this);

    /// first draw
    for (int i = 0; i < size_x; i++){
        for (int k = 0; k < size_y; k++){
            if (!simulador->grid[currentGrid]->operator()(i, k)->active)
                mImage->setPixelColor(i,k, QColor::fromRgb(255,255,255));
            else
                mImage->setPixelColor(i,k, calcRGB(simulador->grid[currentGrid]->operator()(i, k)->temp));
        }
    }

    if ((studyPoint.x() > 0 && studyPoint.x() < size_x) && (studyPoint.y() > 0 || studyPoint.y() < size_y)){
        for(int i = 0; i < size_x; i++)
            mImage->setPixelColor(i,studyPoint.y(), QColor::fromRgb(0,0,0));
        for(int i = 0; i < size_y; i++)
            mImage->setPixelColor(studyPoint.x(), i, QColor::fromRgb(0,0,0));

    }

    /// second draw
    for (int i = 0; i < size_x; i++){
        for (int k = 0; k < size_y; k++){
            if (!simulador->grid[currentGrid]->operator()(i, k)->active)
                mImage->setPixelColor(i+size_x+space_between_draws,k, QColor::fromRgb(255,255,255));
            else
                mImage->setPixelColor(i+size_x+space_between_draws,k, simulador->grid[currentGrid]->operator()(i, k)->material->getColor());
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
    simulador->setDelta_t(std::stod(ui->input_dt->text().toStdString()));
    simulador->setDelta_x(std::stod(ui->input_dx->text().toStdString()));
    simulador->setDelta_z(std::stod(ui->input_dz->text().toStdString()));

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
    if (runningSimulator)
        runSimulator();
    makePlotMatProps();
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
    QVector<double> temperature_x(size_x);
    QVector<double> labor_x(size_x);
    for (int i = 0; i < size_x; i++){
        labor_x[i] = simulador->getDelta_x()*(i+1);
        temperature_x[i] = simulador->grid[studyGrid]->operator()(i, studyPoint.y())->temp;
    }

    ui->plot3->graph(0)->setData(labor_x,temperature_x);
    ui->plot3->xAxis->setRange(labor_x[0], labor_x[size_x-1]);
    ui->plot3->yAxis->setRange(simulador->getTmin()-50, simulador->getTmax()+50);
    ui->plot3->replot();
    ui->plot3->update();
}

void MainWindow::makePlot4(){
    QVector<double> temperature_y(size_y);
    QVector<double> labor_y(size_y);
    for (int i = 0; i < size_y; i++){
        labor_y[i] = simulador->getDelta_x()*(i+1);
        temperature_y[i] = simulador->grid[studyGrid]->operator()(studyPoint.x(), i)->temp;
    }

    ui->plot4->graph(0)->setData(labor_y,temperature_y);
    ui->plot4->xAxis->setRange(labor_y[0], labor_y[size_y-1]);
    ui->plot4->yAxis->setRange(simulador->getTmin()-50, simulador->getTmax()+50);
    ui->plot4->replot();
    ui->plot4->update();
}

void MainWindow::makePlotMatProps(){
    bool changeState = checkChangeMaterialsState();
    if (!changeState)
        return;
    int nPoints = 100;
    QVector<double> props(nPoints);
    QVector<double> temperature_x(nPoints);
    std::vector<std::string> materiais = simulador->getMateriais();


    double dT = (simulador->getTmax() - simulador->getTmin())/(nPoints-1);
    for (unsigned int mat = 0; mat < materiais.size(); mat++){
        if (selectedMateriails[mat]){
            for (int i = 0; i < nPoints; i++){
                temperature_x[i] = dT*i + simulador->getTmin();
                props[i] = simulador->getProps(temperature_x[i], materiais[mat]);
            }
        ui->plot_MatProps->graph(mat)->setPen(QPen(simulador->getColor(materiais[mat])));
        ui->plot_MatProps->graph(mat)->setData(temperature_x,props);
        }else{
            ui->plot_MatProps->graph(mat)->data()->clear();
        }
    }
    ui->plot_MatProps->xAxis->setRange(temperature_x[0], temperature_x[nPoints-1]);
    ui->plot_MatProps->yAxis->setRange(0, 600);

    ui->plot_MatProps->replot();
    ui->plot_MatProps->update();
}

bool MainWindow::checkChangeMaterialsState(){
    bool change = false;
    bool temp = false;
    for (unsigned int i = 0; i<selectedMateriails.size(); i++){
        temp = myCheckbox[i]->checkState();
        if (!(selectedMateriails[i] == temp)){
            change = true;
            selectedMateriails[i] = temp;
        }
    }
    return change;
}

void MainWindow::on_actionSave_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Save a file", "C://Users//nicholas//Desktop//ProjetoEngenharia//Projeto-TCC-SimuladorDifusaoTermica//SimuladorTemperatura//save", tr("Dados (*.dat)"));
    std::string txt = simulador->saveGrid(file_name.toStdString());
    ui->textBrowser_3->setText(QString::fromStdString(txt));
}


void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", "C://Users//nicholas//Desktop//ProjetoEngenharia//Projeto-TCC-SimuladorDifusaoTermica//SimuladorTemperatura//save", tr("Dados (*.dat)"));
    std::string txt = simulador->openGrid(file_name.toStdString());
    ui->textBrowser_3->setText(QString::fromStdString(txt));
}

void MainWindow::on_actionNew_triggered()
{
    simulador->resetGrid();
    update();
}

void MainWindow::on_pushButton_2_clicked()
{
    makePlotMatProps();
}

