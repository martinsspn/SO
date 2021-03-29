#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <pthread.h>
#include "controller.h"

#define N 7
sem_t s[N];
sem_t mutex[3];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int i=0;i<N;i++){
        sem_init(&s[i], 0, 1);
    }
    for(int i=0;i<3;i++){
        sem_init(&mutex[i], 0, 1);
    }

    controller = new Controller(s, mutex);
    //Cria o trem com seu (ID, posição X, posição Y)

    trem1 = new Trem(1, 160, 30, controller);
    trem2 = new Trem(2, 470, 30, controller);
    trem3 = new Trem(3, 870, 90, controller);
    trem4 = new Trem(4, 600, 270, controller);
    trem5 = new Trem(5, 320, 270, controller);

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

    for(int i=0;i<N;i++){
        sem_destroy(&s[i]);
    }
    for(int i=0;i<3;i++){
        sem_destroy(&mutex[i]);
    }
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
    case 3: //Atualiza a posição do objeto da tela (quadrado) que representa o trem3
        ui ->label_trem3->setGeometry(x,y,21,17);
        break;
    case 4: //Atualiza a posição do objeto da tela (quadrado) que representa o trem4
        ui->label_trem4->setGeometry(x,y,27,17);
        break;
    case 5: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem5->setGeometry(x,y,27,17);
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Ao clicar, trens começam execução
 */
void MainWindow::on_pushButton_clicked()
{
    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
}

/*
 * Ao clicar, trens param execução
 */
void MainWindow::on_pushButton_2_clicked()
{
    trem1->terminate();
    trem2->terminate();
    trem3->terminate();
    trem4->terminate();
    trem5->terminate();

}

void MainWindow::on_slidert1_valueChanged(int value)
{
    trem1->setVelocidade(value);
}

void MainWindow::on_slidert2_valueChanged(int value)
{
    trem2->setVelocidade(value);
}

void MainWindow::on_slidert3_valueChanged(int value)
{
    trem3->setVelocidade(value);
}

void MainWindow::on_slidert4_valueChanged(int value)
{
    trem4->setVelocidade(value);
}

void MainWindow::on_slidert5_valueChanged(int value)
{
    trem5->setVelocidade(value);
}
