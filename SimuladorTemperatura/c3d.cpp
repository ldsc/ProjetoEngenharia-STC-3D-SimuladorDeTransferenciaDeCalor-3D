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
    timerId = startTimer(0);

    createPoints();
    size = upperPoints.size();
    drawPoints_up.resize(size);
    drawPoints_down.resize(size);
    update();
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
        margin_y-=10.0f;
    }
    else if (event->key() == Qt::Key_Down){
        margin_y+=10.0f;
    }
    else if (event->key() == Qt::Key_Left){
        margin_x-=10.0f;
    }
    else if (event->key() == Qt::Key_Right){
        margin_x+=10.0f;
    }
    else if (event->key() == Qt::Key_PageUp){
        distance*=1.1;
    }
    else if (event->key() == Qt::Key_PageDown){
        distance*=0.9;
    }
    else if (event->key() == Qt::Key_W){
        angle_x+=0.1;
    }
    else if (event->key() == Qt::Key_S){
        angle_x-=0.1;
    }
    else if (event->key() == Qt::Key_D){
        angle_y+=0.1;
    }
    else if (event->key() == Qt::Key_A){
        angle_y-=0.1;
    }
    update();
}

void C3D::mousePressEvent(QMouseEvent *e){
    mousePos = e->pos();
    mousePress = true;
    update();
}
void C3D::mouseReleaseEvent(QMouseEvent *e){
    angle_y-= (e->pos().x() - mousePos.x());
    angle_x-= (e->pos().y() - mousePos.y());
    mousePress = false;
    update();
}

void C3D::mouseMoveEvent(QMouseEvent *e){
    if (mousePress){
        angle_y-= (e->pos().x() - mousePos.x())/60.0;
        angle_x+= (e->pos().y() - mousePos.y())/60.0;
        mousePos = e->pos();
    }
    update();
}

void C3D::minimizeAngles(){
    if(angle_x > 2.0f*PI)
        angle_x = 0.0f;
    if(angle_x < 0.0f)
        angle_x = 2.0f*PI;

    if(angle_y > 2.0f*PI)
        angle_y = 0.0f;
    if(angle_y < 0.0f)
        angle_y = 2.0f*PI;

    if(angle_z > 2.0f*PI)
        angle_z = 0.0f;
    if(angle_z < 0.0f)
        angle_z = 2.0f*PI;
}

void C3D::paintEvent(QPaintEvent *e) {

    QPainter painter(this);

    minimizeAngles();
    /// desenha as retas
    omp_set_num_threads(MAX_THREADS);
    {
        int thread = omp_get_thread_num();
        int pos;
        for(int i = thread; i < size; i+=MAX_THREADS){
            if ((angle_x<PI/2.0 || angle_x>PI*3.0/2.0) && (angle_y<PI/2.0 || angle_y>PI*3.0/2.0))
                pos = i;
            else
                pos = size-i-1;

            drawPoints_up[pos] = rotate(upperPoints[pos]);
            drawPoints_down[pos] = rotate(lowerPoints[pos]);
            painter.setPen(QPen(color[pos],2));
            painter.drawLine(drawPoints_up[pos].x(), drawPoints_up[pos].y(), drawPoints_down[pos].x(), drawPoints_down[pos].y());

            /*
            if ((angle_x<PI) && (angle_y>PI/2.0 || angle_y<PI*3.0/2.0)){
                painter.setPen(QPen(QColor(70, 70, 70, 20),2));
                painter.drawEllipse(drawPoints_up[pos].x(), drawPoints_up[pos].y(), 3, 3);
                //painter.setPen(QPen(QColor(70, 70, 70, 50),2));
                //painter.drawEllipse(drawPoints_down[pos].x(), drawPoints_down[pos].y(), 3, 3);
            }
            else{
                painter.setPen(QPen(QColor(50, 50, 50, 70),2));
                painter.drawEllipse(drawPoints_down[pos].x(), drawPoints_down[pos].y(), 3, 3);
                //painter.setPen(QPen(QColor(50, 50, 50, 30),2));
                //painter.drawEllipse(drawPoints_up[pos].x(), drawPoints_up[pos].y(), 3, 3);
            }
            */
        }
    }
    painter.drawImage(0,0, *mImage);
    e->accept();
}

QColor C3D::getRGB(int z){
    return QColor::fromRgb(150+z, 150+z, 150+z);
}

void C3D::timerEvent(QTimerEvent *e){
    //angle_x-=0.05;
    //angle_y+=0.05;
    update();
    Q_UNUSED(e);
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
























