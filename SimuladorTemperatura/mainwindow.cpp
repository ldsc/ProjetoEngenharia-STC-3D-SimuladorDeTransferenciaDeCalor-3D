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
    start_buttons();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->buttons() == Qt::LeftButton){
        std::string actualMaterial = ui->material_comboBox->currentText().toStdString();
        double temperature = std::stod(ui->temperature_input->text().toStdString());
        simulador->set_ActualTemperature(temperature); /// importante para atualizar Tmin/Tmax

        if (drawFormat =="circle")
            simulador->grid[currentGrid]->draw_cir(event->pos().x()-left_margin, event->pos().y()-up_margin, drawSize, temperature, isSource, actualMaterial);
        else
            simulador->grid[currentGrid]->draw_rec(event->pos().x()-left_margin, event->pos().y()-up_margin, drawSize, temperature, isSource, actualMaterial);
        update();
    }
    else if (event->buttons() == Qt::RightButton){
        simulador->studyPosition(event->pos().x()-left_margin, event->pos().y()-up_margin, currentGrid);
        time.clear();
        temperature.clear();
    }
}

void MainWindow::start_buttons(){
    ui->textBrowser_2->setFrameStyle(QFrame::NoFrame);
    ui->textBrowser_3->setFrameStyle(QFrame::NoFrame);
    /// texto do grid
    ui->textGrid->setFrameStyle(QFrame::NoFrame);
    ui->textGrid->setText(QString::fromStdString(std::to_string(currentGrid)));

    /// lista de materiais
    std::vector<std::string> materiais = simulador->getMateriais();
    for (unsigned int i = 0; i < materiais.size(); i++)
        ui->material_comboBox->addItem(QString::fromStdString(materiais[i]));

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
    std::string result = "Time: " + std::to_string(simulador->get_time()) + " - duracao do solver: " + std::to_string(std::time(0) - start_time) + " seg";
    if(type == "Sem paralelismo")
        simulador->run_sem_paralelismo();
    if(type=="Paralelismo por grid")
        simulador->run_paralelismo_por_grid();
    if(type=="Paralelismo total")
        simulador->run_paralelismo_total();
    ui->textBrowser_3->setText(QString::fromStdString(result));
    simulador->updateActualTime();
    update();
    makePlot1();
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
    time.append(simulador->getLastTimeStudy());
    temperature.append(simulador->getLastTemperatureStudy());

    ui->plot1->graph(0)->setData(time,temperature);
    ui->plot1->xAxis->setRange(time[0], time[time.size()-1]+1);
    ui->plot1->yAxis->setRange(simulador->getTmin()-50, simulador->getTmax()+50);
    ui->plot1->replot();
    ui->plot1->update();
}

