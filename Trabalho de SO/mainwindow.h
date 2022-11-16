//mainwindow.h (a classe q gera a parte gráfica)
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void updateInterface(int,int,int);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_horizontalSlider_rangeChanged(int min, int max);

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_2_sliderMoved(int position);

    void on_horizontalSlider_3_sliderMoved(int position);

    void on_horizontalSlider_4_sliderMoved(int position);

    void on_horizontalSlider_5_sliderMoved(int position);

private:
    Ui::MainWindow *ui;

    //Cria os objetos TREM's
    Trem *trem1;
    Trem *trem2;
    Trem *trem3;
    Trem *trem4;
    Trem *trem5;

    pthread_mutex_t mut0; // Mutex referente à região crítica 0 (de acordo com a descrição do projeto).
    pthread_mutex_t mut1; // Mutex referente à região crítica 1 (de acordo com a descrição do projeto).
    pthread_mutex_t mut2; // Mutex referente à região crítica 2 (de acordo com a descrição do projeto).
    pthread_mutex_t mut3; // Mutex referente à região crítica 3 (de acordo com a descrição do projeto).
    pthread_mutex_t mut4; // Mutex referente à região crítica 4 (de acordo com a descrição do projeto).
    pthread_mutex_t mut5; // Mutex referente à região crítica 5 (de acordo com a descrição do projeto).
    pthread_mutex_t mut6; // Mutex referente à região crítica 6 (de acordo com a descrição do projeto).

    pthread_cond_t check; // Checa se mutex X está travado ou não.
};

#endif // MAINWINDOW_H
