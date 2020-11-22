#include "mainwindow.hpp"

#include <QApplication>
#include <QPushButton>
#include <QRect>
#include <QMainWindow>
#include <QProgressBar>

int main(int argc, char *argv[])
{
    const int taille_x_max = 1000;
    const int taille_y_max = 1000;
    const int nb_voiture = 10;
    const int nb_parking = 8;
    int nb_places[nb_parking] = {5,6,7,8,9,10,11,12} ;

    QApplication a(argc, argv);
    MainWindow w;
    w.setXY(taille_x_max, taille_y_max);
    w.setInfos(nb_voiture, nb_parking);
    w.setFixedSize(taille_x_max, taille_y_max);
    w.setProgressBar(nb_places);
    w.updateBar();
    w.show();
    //QPushButton bouton("Salut les Zéros, la forme ?");
    //bouton.show();
    return a.exec();
}
