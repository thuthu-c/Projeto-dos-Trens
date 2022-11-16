#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pthread_mutex_init(&mut0, NULL);
    pthread_mutex_init(&mut1, NULL);
    pthread_mutex_init(&mut2, NULL);
    pthread_mutex_init(&mut3, NULL);
    pthread_mutex_init(&mut4, NULL);
    pthread_mutex_init(&mut5, NULL);
    pthread_mutex_init(&mut6, NULL);

    pthread_cond_init(&check, NULL);

    std::vector<pthread_mutex_t*> trem;
    trem.push_back(&mut0);
    trem.push_back(&mut1);
    trem.push_back(&mut2);
    trem.push_back(&mut3);
    trem.push_back(&mut4);
    trem.push_back(&mut5);
    trem.push_back(&mut6);

    //Cria o trem com seu (ID, posição X, posição Y)
    trem1 = new Trem(1, 50,280, trem, &check);
    trem2 = new Trem(2,460,400, trem, &check);
    trem3 = new Trem(3,860,280, trem, &check);
    trem4 = new Trem(4,190,160, trem, &check);
    trem5 = new Trem(5,730,160, trem, &check);

    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função UPDATEINTERFACE.
     * Os 3 parâmetros INT do sinal serão utilizados na função.
     * Trem1 e Trem2 são os objetos que podem chamar o sinal. Se um outro objeto chamar o
     * sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
     */
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));

    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
}

//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y){
    switch(id){
    case 1: //Atualiza a posição do objeto da tela (quadrado) que representa o trem1
        ui->label_trem1->setGeometry(x,y,21,17);
        break;
    case 2: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem2->setGeometry(x,y,21,17);
        break;
    case 3: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem3->setGeometry(x,y,21,17);
        break;
    case 4: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem4->setGeometry(x,y,21,17);
        break;
    case 5: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem5->setGeometry(x,y,21,17);
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    trem1->setSpeed(position);
}


void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    trem2->setSpeed(position);
}


void MainWindow::on_horizontalSlider_3_sliderMoved(int position)
{
    trem3->setSpeed(position);
}


void MainWindow::on_horizontalSlider_4_sliderMoved(int position)
{
    trem4->setSpeed(position);
}


void MainWindow::on_horizontalSlider_5_sliderMoved(int position)
{
    trem5->setSpeed(position);
}

