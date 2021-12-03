#include "C3D.h"

C3D::C3D(CSimuladorTemperatura *_simulador, QWidget *parent)
    : QMainWindow(parent)
{
    //ui->setupUi(this);
    this->setFixedSize(800,800);
    this->adjustSize();
    simulador = _simulador;
    size_x = 500;
    mImage = new QImage(size_x, size_y,QImage::Format_ARGB32_Premultiplied);
    timerId = startTimer(60);

    createPoints();
    size = upperPoints.size();
    drawPoints_up.resize(size);
    drawPoints_down.resize(size);
}


C3D::~C3D()
{
    //delete ui;
}

void C3D::createPoints(){
    double dz = simulador->getDelta_z();
    double dx = simulador->getDelta_x();

    for(int g = 0; g<simulador->getNGRIDS(); g++){
        for(int i = 0; i < simulador->grid[g]->getWidth(); i++){
            for(int j = 0; j < simulador->grid[g]->getHeight(); j++){
                if (simulador->grid[g]->operator()(i,j)->active){
                    upperPoints.push_back(QVector3D(i,j,(g+1)*(dz/dx)));
                    lowerPoints.push_back(QVector3D(i,j,g*(dz/dx)));
                    color.push_back(simulador->grid[g]->operator()(i,j)->material->getColor());
                }
            }
        }
    }

}

void C3D::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Up){
        margin_y-=10;
    }
    else if (event->key() == Qt::Key_Down){
        margin_y+=10;
    }
    else if (event->key() == Qt::Key_Left){
        margin_x-=10;
    }
    else if (event->key() == Qt::Key_Right){
        margin_x+=10;
    }
    else if (event->key() == Qt::Key_PageUp){
        distance*=1.1;
    }
    else if (event->key() == Qt::Key_PageDown){
        distance*=0.9;
    }
}

void C3D::mousePressEvent(QMouseEvent *e){
    mousePos = e->pos();
    mousePress = true;
}
void C3D::mouseReleaseEvent(QMouseEvent *e){
    angle_y-= (e->pos().x() - mousePos.x());
    angle_x-= (e->pos().y() - mousePos.y());
    mousePress = false;
}

void C3D::mouseMoveEvent(QMouseEvent *e){
    if (mousePress){
        angle_y-= (e->pos().x() - mousePos.x())/60.0;
        angle_x+= (e->pos().y() - mousePos.y())/60.0;
        mousePos = e->pos();
    }
}

void C3D::paintEvent(QPaintEvent *e) {

    QPainter painter(this);
    QVector<double> depth(size);
    QVector<double> sort(size);

    /// calcula os pontos considerando a rotacao
    for(int i = 0; i < size; i++){
        drawPoints_up[i] = rotate(upperPoints[i]);
        drawPoints_down[i] = rotate(lowerPoints[i]);
        depth[i] = drawPoints_up[i].z();
        sort[i] = i;
    }
    /*
    int min;
    double temp;

    /// ordeno os desenhos utilizando a profundidade
    for(int i = 0; i < size; i++){
        min = depth[i];
        for(int j=i; j<size;j++){
            if(depth[j]<min){
                min = depth[j];
                sort[i] = j;
            }
        }
        temp = depth[i];
        depth[i] = min;
        depth[sort[i]] = temp;
    }*/

    /// desenha as retas
    int i;
    for(int k = 0; k < size; k++){
        i = sort[k];
        painter.setPen(QPen(color[i],2));
        painter.drawLine(drawPoints_up[i].x(), drawPoints_up[i].y(), drawPoints_down[i].x(), drawPoints_down[i].y());
        painter.setPen(QPen(QColor(50, 50, 50, 30),2));
        painter.drawEllipse(drawPoints_up[i].x(), drawPoints_up[i].y(), 2, 2);
        painter.setPen(QPen(QColor(50, 50, 50, 70),2));
        painter.drawEllipse(drawPoints_down[i].x(), drawPoints_down[i].y(), 2, 2);
    }

    painter.drawImage(0,0, *mImage);
    e->accept();
}

QColor C3D::getRGB(int z){
    return QColor::fromRgb(150+z, 150+z, 150+z);
}

void C3D::timerEvent(QTimerEvent *e){
    Q_UNUSED(e);
    update();
}

QVector3D C3D::rotate(QVector3D a){
    double A[3] = {a.x(), a.y(), a.z()};
    double rotation[3][3];
    double result[3] = {0,0,0};

    /// rotation in x
    rotation[0][0] = cos(angle_z)*cos(angle_y);
    rotation[0][1] = cos(angle_z)*sin(angle_y)*sin(angle_x)-sin(angle_z)*cos(angle_x);
    rotation[0][2] = cos(angle_z)*sin(angle_y)*cos(angle_x)+sin(angle_z)*sin(angle_x);

    rotation[1][0] = sin(angle_z)*cos(angle_y);
    rotation[1][1] = sin(angle_z)*sin(angle_y)*sin(angle_x)+cos(angle_z)*cos(angle_x);
    rotation[1][2] = sin(angle_z)*sin(angle_y)*cos(angle_x)-cos(angle_z)*sin(angle_x);

    rotation[2][0] = -sin(angle_y);
    rotation[2][1] = cos(angle_y)*sin(angle_x);
    rotation[2][2] = cos(angle_y)*cos(angle_x);

    for(int i = 0;i<3; i++)
        for(int j = 0;j<3; j++)
                result[i]+=A[j]*rotation[i][j];

    return QVector3D(result[0]*distance+margin_x,result[1]*distance+margin_y,result[2]*distance);
}
























