#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    up_margin = 100;
    simulador = new CSimuladorTemperatura();
    simulador->resetSize(size_x, size_y);
    ui->setupUi(this);
    mImage = new QImage(size_x*2+space_between_draws, size_y,QImage::Format_ARGB32_Premultiplied);
    timerId = startTimer(20);

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
    ui->plot_MatProps->yAxis->setLabel("rho*cp/k");

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
        double temperature = ui->spinBox_Temperature->value();
        bool isSource = ui->checkBox_source->checkState();
        int size = ui->horizontalSliderDrawSize->value();
        simulador->setActualTemperature(temperature); /// importante para atualizar Tmin/Tmax

        if (drawFormat =="circulo")
            simulador->grid[currentGrid]->draw_cir(event->pos().x()-left_margin-size_x-space_between_draws, event->pos().y()-up_margin, size/2, temperature, isSource, simulador->getMaterial(actualMaterial), eraserActivated);
        else
            simulador->grid[currentGrid]->draw_rec(event->pos().x()-left_margin-size_x-space_between_draws, event->pos().y()-up_margin, size, temperature, isSource, simulador->getMaterial(actualMaterial), eraserActivated);
    }
    else if (event->buttons() == Qt::RightButton){
        int x = event->pos().x()-left_margin-size_x-space_between_draws;
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

void MainWindow::printPosition(){
    int x = QWidget::mapFromParent(QCursor::pos()).x() - left_margin-size_x-space_between_draws;
    int y = QWidget::mapFromParent(QCursor::pos()).y() - up_margin;
    QWidget::mapFromParent(QCursor::pos()).x();
    std::string txt;
    if ((x>0) && (x<size_x) && (y>0) && (y<size_y))
        if (!simulador->grid[currentGrid]->operator()(x, y)->active)
            txt = "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
        else
            txt = "(" + std::to_string(x) + ", " + std::to_string(y) + ") - T: " +
                    std::to_string(simulador->grid[currentGrid]->operator()(x, y)->temp) + "K - "+ simulador->grid[currentGrid]->operator()(x, y)->material->getName();
    else
        txt = "";

    ui->textMousePosition->setText(QString::fromStdString(txt));
}

void MainWindow::printDrawSize(){
    int size = ui->horizontalSliderDrawSize->value();
    ui->textDrawSize->setText("Tamanho: "+QString::number(size) + " px/ "+QString::number(size*simulador->getDelta_x()) + " cm");
}

void MainWindow::start_buttons(){
    /// adicionar borda em widget
    ui->widget_props->setStyleSheet("border-width: 1;"
                                    "border-radius: 3;"
                                    "border-style: solid;"
                                    "border-color: rgb(10,10,10)");

    ui->widget_simulator_deltas->setStyleSheet( "border-width: 1;"
                                                "border-radius: 3;"
                                                "border-style: solid;"
                                                "border-color: rgb(10,10,10)");

    ui->widget_drawStyles->setStyleSheet(       "border-width: 1;"
                                                "border-radius: 3;"
                                                "border-style: solid;"
                                                "border-color: rgb(10,10,10)");

    ui->widget_buttonCircle->setStyleSheet(     "border-width: 1;"
                                                "border-radius: 15;"
                                                "border-style: solid;"
                                                "border-color: rgb(255,0,0)");

    /// remover borda das caixas de texto
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
    ui->textBrowser_14->setFrameStyle(QFrame::NoFrame);
    ui->textBrowser_16->setFrameStyle(QFrame::NoFrame);
    ui->textMousePosition->setFrameStyle(QFrame::NoFrame);
    ui->textDrawSize->setFrameStyle(QFrame::NoFrame);

    /// spinBox temperatura
    ui->spinBox_Temperature->setSingleStep(50);
    ui->spinBox_Temperature->setMaximum(2000);
    ui->spinBox_Temperature->setValue(300);

    /// texto do grid
    ui->textGrid->setFrameStyle(QFrame::NoFrame);
    ui->textGrid->setText(QString::fromStdString(std::to_string(currentGrid)));
    QFont f = ui->textGrid->font();
    f.setPixelSize(16);
    ui->textGrid->setFont(f);
    ui->textGrid->setAlignment(Qt::AlignCenter);

    /// lista de materiais
    std::vector<std::string> materiais = simulador->getMateriais();
    for (unsigned int i = 0; i < materiais.size(); i++)
        ui->material_comboBox->addItem(QString::fromStdString(materiais[i]));

    ui->horizontalSliderDrawSize->setMinimum(2);
    ui->horizontalSliderDrawSize->setMaximum(150);
    ui->horizontalSliderDrawSize->setValue(50);

    /// lista de paralelismo
    ui->parallel_comboBox->addItem("Paralelismo total");
    ui->parallel_comboBox->addItem("Sem paralelismo");
    ui->parallel_comboBox->addItem("Paralelismo por grid");

    ui->input_dt->setText(QString::fromStdString(std::to_string(simulador->getDelta_t())));
    ui->input_dx->setText(QString::fromStdString(std::to_string(simulador->getDelta_x())));
    ui->input_dz->setText(QString::fromStdString(std::to_string(simulador->getDelta_z())));

    createWidgetProps();
}

void MainWindow::createWidgetProps(){
    /// scroll com os materiais para o gráfico
    std::vector<std::string> materiais = simulador->getMateriais();
    checkboxes = new QWidget(ui->scrollArea);
    layout = new QVBoxLayout(checkboxes);
    myCheckbox.resize(materiais.size());
    selectedMateriails.resize(materiais.size(), false);
    QString qss;
    for(unsigned int i = 0; i < materiais.size(); i++){
        myCheckbox[i] = new QCheckBox(QString::fromStdString(materiais[i]), checkboxes);
        qss = QString("background-color: %1").arg(simulador->getColor(materiais[i]).name(QColor::HexArgb));
        myCheckbox[i]->setStyleSheet(qss);
        layout->addWidget(myCheckbox[i]);
    }
    ui->scrollArea->setWidget(checkboxes);
    makePlotMatProps();
}

void MainWindow::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    *mImage = paint(currentGrid);
    painter.drawImage(left_margin,up_margin, *mImage);
    e->accept();
}

QImage MainWindow::paint(int grid) {
    QImage img = QImage(size_x*2+space_between_draws, size_y,QImage::Format_ARGB32_Premultiplied);

    /// desenho da temperatura
    for (int i = 0; i < size_x; i++){
        for (int k = 0; k < size_y; k++){
            if (!simulador->grid[grid]->operator()(i, k)->active)
                img.setPixelColor(i+size_x+space_between_draws,k, QColor::fromRgb(255,255,255));
            else
                img.setPixelColor(i+size_x+space_between_draws,k, calcRGB(simulador->grid[grid]->operator()(i, k)->temp));
        }
    }

    if ((studyPoint.x() > 0 && studyPoint.x() < size_x) && (studyPoint.y() > 0 || studyPoint.y() < size_y) && grid == studyGrid){
        for(int i = 0; i < size_x; i++)
            img.setPixelColor(i+size_x+space_between_draws,studyPoint.y(), QColor::fromRgb(0,0,0));
        for(int i = 0; i < size_y; i++)
            img.setPixelColor(studyPoint.x()+size_x+space_between_draws, i, QColor::fromRgb(0,0,0));
    }

    /// desenho dos materiais
    for (int i = 0; i < size_x; i++){
        for (int k = 0; k < size_y; k++){
            if (!simulador->grid[grid]->operator()(i, k)->active)
                img.setPixelColor(i,k, QColor::fromRgb(255,255,255));
            else
                img.setPixelColor(i,k, simulador->grid[grid]->operator()(i, k)->material->getColor());
        }
    }
    return img;
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
    printPosition();
    printDrawSize();
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
    ui->textGrid->setAlignment(Qt::AlignCenter);
    update();
}

void MainWindow::on_gridUpButton_clicked()
{
    currentGrid++;
    if (currentGrid > simulador->getNGRIDS()-1)
        currentGrid = simulador->getNGRIDS()-1;
    /// texto do grid
    ui->textGrid->setText(QString::fromStdString(std::to_string(currentGrid)));
    ui->textGrid->setAlignment(Qt::AlignCenter);
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
    std::ofstream file(dir.absolutePath().toStdString()+"\\save_results\\horizontal_"+std::to_string(time[time.size()-1]+1)+".dat");
    for (int i = 0; i < size_x; i++){
        labor_x[i] = simulador->getDelta_x()*(i+1);
        temperature_x[i] = simulador->grid[studyGrid]->operator()(i, studyPoint.y())->temp;
        file << labor_x[i] << "; " << temperature_x[i] << std::endl;
    }
    file.close();
    ui->plot3->graph(0)->setData(labor_x,temperature_x);
    ui->plot3->xAxis->setRange(labor_x[0], labor_x[size_x-1]);
    ui->plot3->yAxis->setRange(simulador->getTmin()-50, simulador->getTmax()+50);
    ui->plot3->replot();
    ui->plot3->update();
}

void MainWindow::makePlot4(){
    QVector<double> temperature_y(size_y);
    QVector<double> labor_y(size_y);
    std::ofstream file(dir.absolutePath().toStdString()+"\\save_results\\vertical"+std::to_string(time[time.size()-1]+1)+".dat");
    for (int i = 0; i < size_y; i++){
        labor_y[i] = simulador->getDelta_x()*(i+1);
        temperature_y[i] = simulador->grid[studyGrid]->operator()(studyPoint.x(), i)->temp;
        file << labor_y[i] << "; " << temperature_y[i] << std::endl;
    }
    file.close();
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
    double max_props = 700;

    double dT = (simulador->getTmax() - simulador->getTmin())/(nPoints-1);
    for (unsigned int mat = 0; mat < materiais.size(); mat++){
        if (selectedMateriails[mat]){
            for (int i = 0; i < nPoints; i++){
                temperature_x[i] = dT*i + simulador->getTmin();
                props[i] = simulador->getProps(temperature_x[i], materiais[mat]);
                std::cout<<props[i] << std::endl;
            }
        ui->plot_MatProps->graph(mat)->setPen(QPen(simulador->getColor(materiais[mat])));
        ui->plot_MatProps->graph(mat)->setData(temperature_x,props);
        for (int i = 0; i < nPoints; i++)
            max_props = max_props < props[i]? props[i] : max_props; /// aqui ajusto o ylabel
        }else{
            ui->plot_MatProps->graph(mat)->data()->clear();
        }
    }
    ui->plot_MatProps->xAxis->setRange(temperature_x[0], temperature_x[nPoints-1]);
    ui->plot_MatProps->yAxis->setRange(0, max_props);

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
    QDir dir; QString path = dir.absolutePath();
    QString file_name = QFileDialog::getSaveFileName(this, "Save a file", path+"//save", tr("Dados (*.dat)"));
    std::string txt = simulador->saveGrid(file_name.toStdString());
    ui->textBrowser_3->setText(QString::fromStdString(txt));
}


void MainWindow::on_actionOpen_triggered()
{
    QDir dir; QString path = dir.absolutePath();
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", path+"//save", tr("Dados (*.dat)"));
    std::string txt = simulador->openGrid(file_name.toStdString());
    ui->textBrowser_3->setText(QString::fromStdString(txt));
}

void MainWindow::on_actionNew_triggered()
{
    simulador->resetGrid();
    update();
}


void MainWindow::on_actionExport_pdf_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Save report as", "C://Users", tr("Dados (*.pdf)"));
    QString txt = save_pdf(file_name);
    ui->textBrowser_3->setText(txt);
}

void MainWindow::on_actionImport_material_triggered() {
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", "C://Users//nicholas//Desktop//ProjetoEngenharia//Projeto-TCC-SimuladorDifusaoTermica//SimuladorTemperatura//materiais", tr("Dados (*.txt)"));
    std::string name = simulador->openMaterial(file_name.toStdString());
    ui->textBrowser_3->setText(QString::fromStdString("Material "+name+" carregado!"));
    ui->material_comboBox->addItem(QString::fromStdString(name));

    createWidgetProps();
}

void MainWindow::on_buttonCircle_clicked()
{

    ui->widget_buttonCircle->setStyleSheet(     "border-width: 1;"
                                                "border-radius: 15;"
                                                "border-style: solid;"
                                                "border-color: rgb(255,0,0)");
    ui->widget_buttonSquare->setStyleSheet(     "border-width: 0;"
                                                "border-radius: 0;"
                                                "border-style: solid;"
                                                "border-color: rgb(255,0,0)");
    drawFormat = "circulo";
}


void MainWindow::on_buttonSquare_clicked()
{
    ui->widget_buttonSquare->setStyleSheet(     "border-width: 1;"
                                                "border-radius: 0;"
                                                "border-style: solid;"
                                                "border-color: rgb(255,0,0)");
    ui->widget_buttonCircle->setStyleSheet(     "border-width: 0;"
                                                "border-radius: 15;"
                                                "border-style: solid;"
                                                "border-color: rgb(255,0,0)");
    drawFormat = "quadrado";

}


void MainWindow::on_buttonEraser_clicked()
{
    if (eraserActivated){
        ui->widget_eraser->setStyleSheet("border-width: 0;"
                                         "border-radius: 0;"
                                         "border-style: solid;"
                                         "border-color: rgb(255,0,0)");
    eraserActivated = false;
    }
    else{
        ui->widget_eraser->setStyleSheet("border-width: 1;"
                                         "border-radius: 5;"
                                         "border-style: solid;"
                                         "border-color: rgb(255,170,100)");
        eraserActivated = true;
    }
}

QString MainWindow::save_pdf(QString file_name){

    QPdfWriter writer(file_name);
    writer.setPageSize(QPageSize::A4);
    writer.setPageMargins(QMargins(30, 30, 30, 30));

    QPrinter pdf;
    pdf.setOutputFormat(QPrinter::PdfFormat);
    pdf.setOutputFileName(file_name);

    QPainter painterPDF(this);
    if (!painterPDF.begin(&pdf))        //Se não conseguir abrir o arquivo PDF ele não executa o resto.
        return "Erro ao abrir PDF";


    painterPDF.setFont(QFont("Arial", 8));
    painterPDF.drawText(40,140, "==> PROPRIEDADES DO GRID <==");
    painterPDF.drawText(40,160, "Delta x: " + QString::number(simulador->getDelta_x())+" m");
    painterPDF.drawText(40,180, "Delta z: " + QString::number(simulador->getDelta_z())+" m");
    painterPDF.drawText(40,200, "Delta t: " + QString::number(simulador->getDelta_t())+" s");

    painterPDF.drawText(40,240, "Largura total horizontal: " + QString::number(simulador->getDelta_x()*size_x)+" m");
    painterPDF.drawText(40,260, "Largura total vertical: " + QString::number(simulador->getDelta_x()*size_y)+" m");
    painterPDF.drawText(40,280, "Largura total entre perfis (eixo z): " + QString::number(simulador->getDelta_z()*simulador->getNGRIDS())+" m");



    painterPDF.drawText(400,140, "==> PROPRIEDADES DA SIMULAÇÃO <==");
    painterPDF.drawText(400,160, "Temperatura máxima: " + QString::number(simulador->getTmax())+" K");
    painterPDF.drawText(400,180, "Temperatura mínima: " + QString::number(simulador->getTmin())+" K");
    painterPDF.drawText(400,200, "Tempo máximo: " + QString::number(time[time.size()-1])+" s");

    painterPDF.drawText(400,240, "Tipo de paralelismo: " + ui->parallel_comboBox->currentText());
    painterPDF.drawText(400,260, "Coordenada do ponto de estudo (x,y,z): " + QString::number(studyPoint.x()*simulador->getDelta_x())+","+QString::number(studyPoint.y()*simulador->getDelta_x())+","+QString::number(studyGrid*simulador->getDelta_z()));

    /// print dos 4 desenhos
    painterPDF.setPen(Qt::blue);
    painterPDF.setRenderHint(QPainter::LosslessImageRendering);
    int startDraw_x  = 40;
    int startDraw_y  = 300;
    int space_draw_x = 40;
    int space_draw_y = 30;
    int d = 5;
    painterPDF.setFont(QFont("Arial", 8));

    painterPDF.drawPixmap(startDraw_x, startDraw_y, (size_x*2+space_between_draws)/2, size_y/2, ui->plot1->toPixmap());
    QRect retangulo5(startDraw_x-d, startDraw_y-d, (size_x*2+space_between_draws)/2+2*d, size_y/2+2*d);
    painterPDF.drawRoundedRect(retangulo5, 2.0, 2.0);

    painterPDF.drawPixmap((size_x*2+space_between_draws)/2+startDraw_x+space_draw_x, startDraw_y, (size_x*2+space_between_draws)/2, size_y/2, ui->plot2->toPixmap());
    QRect retangulo6((size_x*2+space_between_draws)/2+startDraw_x+space_draw_x-d, startDraw_y-d, (size_x*2+space_between_draws)/2+2*d, size_y/2+2*d);
    painterPDF.drawRoundedRect(retangulo6, 2.0, 2.0);

    painterPDF.drawPixmap(startDraw_x, size_y/2+startDraw_y+space_draw_y, (size_x*2+space_between_draws)/2, size_y/2, ui->plot3->toPixmap());
    QRect retangulo7(startDraw_x-d, size_y/2+startDraw_y+space_draw_y-d, (size_x*2+space_between_draws)/2+2*d, size_y/2+2*d);
    painterPDF.drawRoundedRect(retangulo7, 2.0, 2.0);

    painterPDF.drawPixmap((size_x*2+space_between_draws)/2+startDraw_x+space_draw_x, size_y/2+startDraw_y+space_draw_y, (size_x*2+space_between_draws)/2, size_y/2, ui->plot4->toPixmap());
    QRect retangulo8((size_x*2+space_between_draws)/2+startDraw_x+space_draw_x-d, size_y/2+startDraw_y+space_draw_y-d, (size_x*2+space_between_draws)/2+2*d, size_y/2+2*d);
    painterPDF.drawRoundedRect(retangulo8, 2.0, 2.0);

    painterPDF.drawPixmap(startDraw_x, size_y+startDraw_y+space_draw_y*2, (size_x*2+space_between_draws*2), size_y/2, ui->widget_props->grab());


    startDraw_y = 100;
    space_draw_y = 50;

    for (int i = 0; i<simulador->getNGRIDS(); i++){
        if (i%6 == 0){
            startDraw_y = 100;
            writer.newPage();
            pdf.newPage();
        }
        if (i%2 == 0){
            painterPDF.drawText(startDraw_x+size_x/2, startDraw_y-d-8, "Grid "+QString::number(i));
            painterPDF.drawPixmap(startDraw_x, startDraw_y, (size_x*2+space_between_draws)/2, size_y/2, QPixmap::fromImage(paint(i)));
            QRect retangulo1(startDraw_x-d, startDraw_y-d, (size_x*2+space_between_draws)/2+2*d, size_y/2+2*d);
            painterPDF.drawRoundedRect(retangulo1, 2.0, 2.0);
        }
        else {
            painterPDF.drawText(startDraw_x+space_draw_x+size_x+size_x/2+4*d, startDraw_y-d-8, "Grid "+QString::number(i));
            painterPDF.drawPixmap((size_x*2+space_between_draws)/2+startDraw_x+space_draw_x, startDraw_y, (size_x*2+space_between_draws)/2, size_y/2, QPixmap::fromImage(paint(i)));
            QRect retangulo2((size_x*2+space_between_draws)/2+startDraw_x+space_draw_x-d, startDraw_y-d, (size_x*2+space_between_draws)/2+2*d, size_y/2+2*d);
            painterPDF.drawRoundedRect(retangulo2, 2.0, 2.0);
            startDraw_y+=size_y/2+space_draw_y;
        }
    }
    return "PDF salvo!";
}


void MainWindow::on_gridAddGrid_clicked()
{
    simulador->addGrid();
    currentGrid = simulador->getNGRIDS()-1;

    /// texto do grid
    ui->textGrid->setText(QString::fromStdString(std::to_string(currentGrid)));
    ui->textGrid->setAlignment(Qt::AlignCenter);
    update();

}

void MainWindow::on_gridDelGrid_clicked()
{
    if (simulador->getNGRIDS() > 1){
        simulador->delGrid(currentGrid);
        currentGrid = currentGrid==0? 0:currentGrid-1;
    }

    /// texto do grid
    ui->textGrid->setText(QString::fromStdString(std::to_string(currentGrid)));
    ui->textGrid->setAlignment(Qt::AlignCenter);
    update();
}

void MainWindow::on_button3D_clicked(){
    C3D *newWindow = new C3D(simulador);
    //C3D *newWindow = new C3D();
    newWindow->show();
}
