#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QRect>
#include <QPainter>
#include <QMainWindow>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    taille_x_max = 0;
    taille_y_max = 0;
}

void MainWindow::paintEvent(QPaintEvent *event)
{

    /*QPainter painter(this);
    painter.setBrush(Qt::DiagCrossPattern);

    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(5);

    painter.setPen(pen);*/

    /*m_bouton = new QPushButton("Pimp mon bouton !", this);
    m_bouton->setCursor(Qt::PointingHandCursor);
    m_bouton->setIcon(QIcon("smile.png"));
    m_bouton->move(60, 50);
    m_bouton->setFixedSize(150,100);
    m_bouton->show();*/

    

    for(int i = 0; i<nb_parking; i++){
        bouton[i] = new QPushButton("bouton", this);
        bouton[i]->move( taille_x_max - (taille_x_max / nb_parking)*(nb_parking-i),0);
        bouton[i]->setFixedSize(taille_x_max/nb_parking, taille_y_max/2);
        bouton[i]->setCursor(Qt::PointingHandCursor);
        bouton[i]->show();
    }


   /*for(int i = 0; i<nb_parking; i++){
        painter.drawRect(QRect( taille_x_max - (taille_x_max / nb_parking)*(nb_parking-i),0,
                                taille_x_max/nb_parking, taille_y_max/2));
    }*/

    for (int i = 0; i<nb_parking; i++){
        tab_bar[i] = new QProgressBar(bouton[i]);
        tab_bar[i]->setRange(0, nb_places[i]);
        //tab_bar[i]->move(taille_x_max - (taille_x_max / nb_parking)*(nb_parking-i)
        //                              +(taille_x_max / nb_parking)*0.10, 200);
        tab_bar[i]->setValue(5);
        tab_bar[i]->move(10 , 50);
        tab_bar[i]->setTextVisible(true);
        tab_bar[i]->setFormat(QString::number(tab_bar[i]->value())+"/"+QString::number(nb_places[i]));
        tab_bar[i]->setAlignment(Qt::AlignCenter);
        tab_bar[i]->show();
    }
    m_slider = new QSlider(Qt::Horizontal, bouton[2]);
    m_slider->setGeometry(10, 10, 150, 20);
    m_slider->show();
    QObject::connect(m_slider, SIGNAL(valueChanged(int)), tab_bar[2], SLOT(setValue(int))) ;


}

void MainWindow::setXY(int x, int y){
    taille_x_max = x;
    taille_y_max = y;
}

void MainWindow::setInfos(int nbCar, int nbParking){
    nb_voiture = nbCar;
    nb_parking = nbParking;
}

void MainWindow::setProgressBar(int tab[8]){
    for (int i =0; i<nb_parking; i++){
        nb_places[i] = tab[i];
    }
}

void MainWindow::updateBar(){
    //tab_bar[2]->setValue(2);
    //tab_bar[i]->setFormat(QString::number(tab_bar[i]->value())+"/"+QString::number(nb_places[i]));
}


MainWindow::~MainWindow()
{
    delete ui;
}

