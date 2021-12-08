#include "C3D.h"
C3D::C3D(QWidget *parent)
    : QMainWindow(parent)
{
    //ui->setupUi(this);
    this->setFixedSize(800,800);
    this->adjustSize();
    size_x = 500;
    mImage = new QImage(size_x, size_y,QImage::Format_ARGB32_Premultiplied);
    timerId = startTimer(0);

    QVector3D point(0,0,0);
    cube.push_back(createCube(point));

    createTriangles();
    drawCube.resize(8);
    update();
}

C3D::C3D(CSimuladorTemperatura *_simulador, QWidget *parent)
    : QMainWindow(parent)
{
    simulador = _simulador;
    this->setFixedSize(800,800);
    this->adjustSize();
    size_x = 500;
    mImage = new QImage(size_x, size_y,QImage::Format_ARGB32_Premultiplied);
    timerId = startTimer(0);
    std::cout<<"criando cubos"<<std::endl;
    double dz = simulador->getDelta_z();
    double dx = simulador->getDelta_x();
    for(int g = 0; g<simulador->getNGRIDS(); g++){
        for(int i = 0; i < simulador->grid[g]->getWidth(); i++){
            for(int j = 0; j < simulador->grid[g]->getHeight(); j++){
                if (simulador->grid[g]->operator()(i,j)->active){
                    cube.push_back(createCube(QVector3D(i,j,(g+1)*dz/dx)));
                }
            }
        }
    }

    std::cout<<"cubos criados"<<std::endl;
    createTriangles();
    drawCube.resize(8);
    update();
}


C3D::~C3D()
{
    //delete ui;
}

void C3D::createTriangles(){
    triangles.resize(12);
    triangles[0]  = QVector3D( 0,1,2);
    triangles[1]  = QVector3D( 4,2,1);

    triangles[2]  = QVector3D( 1,5,4);
    triangles[3]  = QVector3D( 7,4,5);

    triangles[4]  = QVector3D( 6,3,2);
    triangles[5]  = QVector3D( 0,2,3);

    triangles[6]  = QVector3D( 4,7,2);
    triangles[7]  = QVector3D( 6,2,7);

    triangles[8]  = QVector3D( 6,7,3);
    triangles[9]  = QVector3D( 5,3,7);

    triangles[10] = QVector3D( 1,0,5);
    triangles[11] = QVector3D( 3,5,0);
}

QVector<QVector3D> C3D::createCube(QVector3D point){
    double x = point.x(), y = point.y(), z = point.z();

    QVector<QVector3D> cube(8);
    cube[0] = QVector3D( x-dx/2.0, y-dy/2.0, z-dz/2.0);
    cube[1] = QVector3D( x+dx/2.0, y-dy/2.0, z-dz/2.0);
    cube[2] = QVector3D( x-dx/2.0, y+dy/2.0, z-dz/2.0);
    cube[3] = QVector3D( x-dx/2.0, y-dy/2.0, z+dz/2.0);
    cube[4] = QVector3D( x+dx/2.0, y+dy/2.0, z-dz/2.0);
    cube[5] = QVector3D( x+dx/2.0, y-dy/2.0, z+dz/2.0);
    cube[6] = QVector3D( x-dx/2.0, y+dy/2.0, z+dz/2.0);
    cube[7] = QVector3D( x+dx/2.0, y+dy/2.0, z+dz/2.0);
    return cube;
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
    QPolygon triangle;

    minimizeAngles();

    int a, b, c;
    painter.setPen(QPen(QColor(100, 100, 100, 100*0.8),2));
    for(int cb = 0; cb < cube.size(); cb++){
        for(int i = 0; i < 8; i++)
            drawCube[i] = rotate(cube[cb][i]);

        for(int r = 0; r < 12; r++){
            a = triangles[r].x();
            b = triangles[r].y();
            c = triangles[r].z();
            if(produtoVetorial(drawCube[a], drawCube[b], drawCube[c]).z() > 0){
                painter.drawLine(drawCube[a].x(), drawCube[a].y(), drawCube[b].x(), drawCube[b].y());
                painter.drawLine(drawCube[a].x(), drawCube[a].y(), drawCube[c].x(), drawCube[c].y());
                painter.drawLine(drawCube[c].x(), drawCube[c].y(), drawCube[b].x(), drawCube[b].y());
            }
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

QVector3D C3D::produtoVetorial(QVector3D origem, QVector3D a, QVector3D b){
    QVector3D ax = a - origem;
    QVector3D bx = b - origem;
    return QVector3D(ax.y()*bx.z()-ax.z()*bx.y(), -ax.x()*bx.z()+ax.z()*bx.x(), ax.x()*bx.y()-ax.y()*bx.x());
}
























