#include "CRender3D.h"

CRender3D::CRender3D(QWidget *parent)
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

CRender3D::CRender3D(CSimuladorTemperatura *_simulador, QWidget *parent)
    : QMainWindow(parent)
{
    simulador = _simulador;
    this->setFixedSize(800,800);
    this->adjustSize();
    size_x = 500;
    mImage = new QImage(size_x, size_y,QImage::Format_ARGB32_Premultiplied);
    timerId = startTimer(0);
    margin_x = 400;//simulador->getWidth();
    margin_y = 400;//simulador->getHeight();
    std::cout<<"criando cubos"<<std::endl;
    dx = 1;//simulador->getDelta_x();
    dy = dx;
    dz = 1*simulador->getDelta_z()/simulador->getDelta_x();
    double maxTemp = simulador->getTmax();
    double minTemp = simulador->getTmin();
    for(int g = 0; g<simulador->getNGRIDS(); g++){
        for(int i = 0; i < simulador->grid[g]->getWidth(); i++){
            for(int j = 0; j < simulador->grid[g]->getHeight(); j++){
                if (simulador->grid[g]->operator()(i,j)->active){
                    cube.push_back(createCube(QVector3D(i,j,(g+1)*dz)));
                    activeEdges.push_back(edges(i,j,g));
                    colorsMaterial.push_back(simulador->grid[g]->operator()(i,j)->material->getColor());
                    colorsTemperature.push_back(getRGB(simulador->grid[g]->operator()(i,j)->temp, minTemp, maxTemp));
                }
            }
        }
    }

    std::cout<<"cubos criados"<<std::endl;
    createTriangles();
    drawCube.resize(8);
    update();
}


CRender3D::~CRender3D()
{
    //delete ui;
}

QVector<bool> CRender3D::edges(int i, int j, int g){
    QVector<bool> actives(12, true);
    int max_i = simulador->getWidth()-1;
    int max_j = simulador->getHeight()-1;
    int max_g = simulador->grid.size()-1;


    if (g > 0){
        if (simulador->grid[g-1]->operator()(i,j)->active){
            actives[0] = false;
            actives[1] = false;
        }
    }
    if (i < max_i){
        if (simulador->grid[g]->operator()(i+1,j)->active){
            actives[2] = false;
            actives[3] = false;
        }
    }
    if (i > 0){
        if (simulador->grid[g]->operator()(i-1,j)->active){
            actives[4] = false;
            actives[5] = false;
        }
    }
    if (j < max_j){
        if (simulador->grid[g]->operator()(i,j+1)->active){
            actives[6] = false;
            actives[7] = false;
        }
    }
    if (g < max_g){
        if (simulador->grid[g+1]->operator()(i,j)->active){
            actives[8] = false;
            actives[9] = false;
        }
    }
    if (j > 0){
        if (simulador->grid[g]->operator()(i,j-1)->active){
            actives[10] = false;
            actives[11] = false;
        }
    }
    return actives;
}

void CRender3D::createTriangles(){
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

QVector<QVector3D> CRender3D::createCube(QVector3D point){
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

void CRender3D::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Up){
        margin_y+=30.0f;
    }
    else if (event->key() == Qt::Key_Down){
        margin_y-=30.0f;
    }
    else if (event->key() == Qt::Key_Left){
        margin_x+=30.0f;
    }
    else if (event->key() == Qt::Key_Right){
        margin_x-=30.0f;
    }
    else if (event->key() == Qt::Key_PageUp){
        distance*=1.1;
    }
    else if (event->key() == Qt::Key_PageDown){
        distance*=0.9;
    }
    else if (event->key() == Qt::Key_W){
        angle_x-=0.1;
    }
    else if (event->key() == Qt::Key_S){
        angle_x+=0.1;
    }
    else if (event->key() == Qt::Key_D){
        angle_y-=0.1;
    }
    else if (event->key() == Qt::Key_A){
        angle_y+=0.1;
    }
    else if (event->key() == Qt::Key_Space){
        corMaterial = corMaterial ? false:true;
    }
    update();
}

void CRender3D::mousePressEvent(QMouseEvent *e){
    mousePos = e->pos();
    mousePress = true;
    update();
}
void CRender3D::mouseReleaseEvent(QMouseEvent *e){
    angle_y-= (e->pos().x() - mousePos.x());
    angle_x-= (e->pos().y() - mousePos.y());
    mousePress = false;
    update();
}

void CRender3D::mouseMoveEvent(QMouseEvent *e){
    if (mousePress){
        angle_y-= (e->pos().x() - mousePos.x())/60.0;
        angle_x+= (e->pos().y() - mousePos.y())/60.0;
        mousePos = e->pos();
    }
    update();
}

void CRender3D::minimizeAngles(){
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

void CRender3D::paintEvent(QPaintEvent *e) {

    //QPolygon triangle;

    QPainter painter(this);
    minimizeAngles();
    QVector<QPolygon> triangulosDesenho;
    QVector<QColor> coresDesenho;
    QVector<std::pair<int, double>> pos_norm;
    QVector<QColor> color;
    if (corMaterial)
        color = colorsMaterial;
    else
        color = colorsTemperature;
    double prodVet;
    int a, b, c;
    int count = 0;
    for(int cb = 0; cb < cube.size(); cb++){
        for(int i = 0; i < 8; i++)
            drawCube[i] = rotate(cube[cb][i]);

        for(int r = 0; r < 12; r++){
            if(activeEdges[cb][r]){
                a = triangles[r].x();
                b = triangles[r].y();
                c = triangles[r].z();
                prodVet = produtoVetorial(drawCube[a], drawCube[b], drawCube[c]).z();
                if(prodVet > 0){
                    pos_norm.push_back(std::pair(count, prodVet));
                    count++;
                    if(r == 0 || r == 1 || r == 8 || r == 9) /// fronteiras de g
                        coresDesenho.push_back(QColor(color[cb].red(), color[cb].green(), color[cb].blue(), 255));
                    else
                        coresDesenho.push_back(QColor(QColor(color[cb].red()*0.6, color[cb].green()*0.6, color[cb].blue()*0.6, 255)));

                    QPolygon pol;
                    pol << QPoint(drawCube[a].x(),drawCube[a].y())
                        << QPoint(drawCube[b].x(),drawCube[b].y())
                        << QPoint(drawCube[c].x(),drawCube[c].y());
                    triangulosDesenho.push_back(pol);
                }
            }
        }
    }

    /// organizo conforme a profundidade
    std::sort(pos_norm.begin(), pos_norm.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    });

    /// desenho na tela
    int pos;
    painter.setPen(QColor(0,0,0,0));
    for(int i = 0; i<triangulosDesenho.size(); i++){
        pos = pos_norm[i].first;
        painter.setBrush(coresDesenho[pos]);
        painter.drawPolygon(triangulosDesenho[pos]);
    }

    painter.drawImage(0,0, *mImage);
    e->accept();
}

QColor CRender3D::getRGB(double x, double min, double max){
    return QColor::fromRgb(255, (max - x)*255/(max - min), 0, 255);
}

void CRender3D::timerEvent(QTimerEvent *e){
    //angle_x-=0.05;
    //angle_y+=0.05;
    update();
    Q_UNUSED(e);
}

QVector3D CRender3D::rotate(QVector3D a){
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

    return QVector3D((result[0]+margin_x-200)*distance,(result[1]+margin_y-200)*distance,result[2]*distance);
}

QVector3D CRender3D::produtoVetorial(QVector3D origem, QVector3D a, QVector3D b){
    QVector3D ax = a - origem;
    QVector3D bx = b - origem;
    return QVector3D(ax.y()*bx.z()-ax.z()*bx.y(), -ax.x()*bx.z()+ax.z()*bx.x(), ax.x()*bx.y()-ax.y()*bx.x());
}
























