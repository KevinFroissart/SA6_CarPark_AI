#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include<QPainter>
#include <QProgressBar>
#include <QTimer>
#include <QPushButton>
#include <QApplication>
#include <QMainWindow>
#include <vector>
#include <QSlider>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent (QPaintEvent *event);
    void setXY(int x, int y);
    void setInfos(int nbCar, int nbParking);
    void setProgressBar(int tab[8]);
    void updateBar();

private:
    Ui::MainWindow *ui;
    int taille_x_max;
    int taille_y_max;
    int nb_voiture;
    int nb_parking;
    int nb_places[8];

    QProgressBar * progressBar;
    QProgressBar * tab_bar[50];
    QPushButton *m_bouton;
    QPushButton * bouton[50];
    QSlider *m_slider; 


};
#endif // MAINWINDOW_HPP
