#include "trem.h"
#include <QtCore>
#include <QDebug>

//Construtor
Trem::Trem(int ID, int x, int y, std::vector<pthread_mutex_t*> trem, pthread_cond_t* condition){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;

    mutexes = trem;
    check = condition;
}

void Trem::setSpeed(int novaVelocidade){
    velocidade = novaVelocidade;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 280 && x <320){
                if(x<170) x+=10;
                else{ //critical region treatment
                    if(x==170){
                        if(pthread_mutex_trylock(mutexes[5])){
                            if(pthread_mutex_lock(mutexes[2])){
                                pthread_mutex_unlock(mutexes[2]);//break;
                            } else {
                                pthread_mutex_unlock(mutexes[2]);
                                if(pthread_mutex_lock(mutexes[0])){
                                    pthread_mutex_unlock(mutexes[0]);//break;
                                }
                                else{
                                    pthread_mutex_unlock(mutexes[0]);
                                }
                            }
                        } else {
                            pthread_mutex_unlock(mutexes[5]);
                            if(pthread_mutex_lock(mutexes[0])){
                                pthread_mutex_unlock(mutexes[0]);//break;
                            }
                            else{
                                pthread_mutex_unlock(mutexes[0]);
                            }
                        }
                        pthread_mutex_lock(mutexes[1]);
                        pthread_mutex_lock(mutexes[5]);

                        qDebug() << "Mutexes 1 & 5 are with train 1";
                    }
                    if(x == 300) {
                        //pthread_mutex_lock(mutexes[5]);
                    }
                    x+=10;
                }
            }
            else if (x == 320 && y < 400){
                if(y==300){
                    //pthread_mutex_unlock(&mut1);
                     pthread_mutex_unlock(mutexes[1]);
                     qDebug() << "Mutex 1 is free from train 1";
                }
                y+=10;
            }
            else if (x > 50 && y == 400){
                if(x==300){

                    //pthread_mutex_unlock(&mut5);
                    pthread_mutex_unlock(mutexes[5]);
                }
                x-=10;
            }
            else{
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 280 && x < 590){
                if(x==340){
                    //pthread_mutex_unlock(&mut5);
                    pthread_mutex_unlock(mutexes[5]);
                }
                if(x<440) x+=10;
                else{
                    if(x == 440){
                        if(pthread_mutex_trylock(mutexes[6])){
                            if(pthread_mutex_trylock(mutexes[4])){
                                break;
                            } else {
                                pthread_mutex_unlock(mutexes[4]);
                            }
                        } else {
                            pthread_mutex_unlock(mutexes[6]);
                        }
                        //pthread_mutex_lock(&mut3);
                        pthread_mutex_lock(mutexes[3]);
                        qDebug() << "Mutex 3 is with train 2";
                    }
                    if(x==480){
                        //pthread_mutex_unlock(&mut2);
                         pthread_mutex_unlock(mutexes[2]);
                         qDebug() << "Mutex 2 is no longer with train 2";


                    }
                    if(x==570){
                        //pthread_mutex_lock(&mut6);
                         pthread_mutex_lock(mutexes[6]);
                         qDebug() << "Mutex 6 is with train 2";
                    }
                    x+=10;
                }
            }
            else if (x == 590 && y < 400){
                if(y==300){

                   // pthread_mutex_unlock(&mut3);
                    pthread_mutex_unlock(mutexes[3]);

                }
                y+=10;
            }
            else if (x > 320 && y == 400){
                if(x==570){

                   // pthread_mutex_unlock(&mut6);
                    pthread_mutex_unlock(mutexes[6]);
                }
                if(x==340){
                    if(pthread_mutex_trylock(mutexes[1])){
                        if(pthread_mutex_trylock(mutexes[5])){
                            if(pthread_mutex_trylock(mutexes[0])){
                                break;
                            }
                            else{
                                pthread_mutex_unlock(mutexes[0]);
                                break;
                            }
                        } else {
                            pthread_mutex_unlock(mutexes[5]);
                        }
                    } else{
                        pthread_mutex_unlock(mutexes[1]);
                    }
                    //pthread_mutex_lock(&mut5);
                     pthread_mutex_lock(mutexes[5]);
                     qDebug() << "Mutex 5 is with train 2";
                }
                x-=10;
            }
            else{
                if(y==300){
                    if(pthread_mutex_trylock(mutexes[3])){
                        if(pthread_mutex_trylock(mutexes[0])){
                            if(pthread_mutex_trylock(mutexes[6])){
                                break;
                            }
                            else{
                                pthread_mutex_unlock(mutexes[6]);
                                break;
                            }
                        } else {
                            pthread_mutex_unlock(mutexes[0]);
                        }
                    } else{
                        pthread_mutex_unlock(mutexes[3]);
                    }
                    qDebug() << "Trying to get mutex 2 to train 2";
                    pthread_mutex_lock(mutexes[2]);
                    qDebug() << "Mutex 2 is with train 2";
                }
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (y == 280 && x < 860){
                if(x==610){
                   // pthread_mutex_unlock(&mut6);
                    pthread_mutex_unlock(mutexes[6]);
                }
                if(x==750){

                   // pthread_mutex_unlock(&mut4);
                    pthread_mutex_unlock(mutexes[4]);
                }
                x+=10;
            }
            else if (x == 860 && y < 400){
                y+=10;
            }
            else if (x > 590 && y == 400){
                if(x==610){
                    if(pthread_mutex_trylock(mutexes[3])){
                        if(pthread_mutex_trylock(mutexes[4])){
                            if(pthread_mutex_trylock(mutexes[5])){
                                break;
                            }
                            else{
                                pthread_mutex_unlock(mutexes[5]);
                                break;
                            }
                        } else {
                            pthread_mutex_unlock(mutexes[4]);
                        }
                    } else {
                        pthread_mutex_unlock(mutexes[3]);
                    }
                    //pthread_mutex_lock(&mut6);
                     pthread_mutex_lock(mutexes[4]);
                     pthread_mutex_lock(mutexes[6]);
                     qDebug() << "Mutexes 4 & 6 are with train 3";
                }
                x-=10;
            }
            else{
                if(y==300){

                    //pthread_mutex_lock(&mut4);
                    //pthread_mutex_lock(mutexes[4]);
                }
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if (y == 160 && x < 460){
                if(x==440){
                    if(pthread_mutex_trylock(mutexes[2])){
                        if(pthread_mutex_trylock(mutexes[3])){
                            if(pthread_mutex_trylock(mutexes[4])){
                                break;
                            }
                            else{
                                pthread_mutex_unlock(mutexes[4]);
                                break;
                            }
                        } else {
                            pthread_mutex_unlock(mutexes[3]);
                        }
                    } else{
                        pthread_mutex_unlock(mutexes[2]);
                    }
                    //pthread_mutex_lock(&mut0);
                    pthread_mutex_lock(mutexes[0]);
                    qDebug() << "Mutex 0 is with train 4";
                    //pthread_mutex_lock(mutexes[2]);
                }
                x+=10;
            }
            else if (x == 460 && y < 280){
                if(y==260){
                    if(pthread_mutex_trylock(mutexes[1])){
                        qDebug() << "Mutex 1 is locked";
                        if(pthread_mutex_trylock(mutexes[5])){
                            qDebug() << "Mutex 5 is locked";
                            break;
                        } else {
                            pthread_mutex_unlock(mutexes[5]);
                            qDebug() << "Mutex 5 is free";
                        }
                    } else {
                        pthread_mutex_unlock(mutexes[1]);
                        qDebug() << "Mutex 1 is free";
                    }
                    //pthread_mutex_lock(&mut2);
                    qDebug() << "Trying to get mutex 2 to train 4";
                    pthread_mutex_lock(mutexes[2]);
                    qDebug() << "Mutex 2 is with train 4";
                    //pthread_mutex_lock(mutexes[1]);
                }
                y+=10;
            }
            else if (x > 190 && y == 280){
                if(x==440){
                    // pthread_mutex_unlock(&mut0);
                    pthread_mutex_unlock(mutexes[0]);
                }
                if(x==340){
                    // pthread_mutex_lock(&mut1);
                    qDebug() << "Trying to get mutex 1 to train 4";
                    pthread_mutex_lock(mutexes[1]);
                    qDebug() << "Mutex 1 is with train 4";
                }
                if(x==300){
                    // pthread_mutex_unlock(&mut2);
                    pthread_mutex_unlock(mutexes[2]);
                    qDebug() << "Mutex 2 is no longer with train 4";
                    qDebug() << "We're at coordinates (";
                    qDebug() << x << ", " << y << ")";
                }
                x-=10;
            }
            else{
                if(y==260){
                    // pthread_mutex_unlock(&mut1);
                    pthread_mutex_unlock(mutexes[1]);
                    qDebug() << "Mutex 1 is no longer with train 4";
                }
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (y == 160 && x < 730){
                if(x==480){

                    // pthread_mutex_unlock(&mut0);
                    pthread_mutex_unlock(mutexes[0]);
                }
                x+=10;
            }
            else if (x == 730 && y < 280){
                if(y==260){
                    if(pthread_mutex_trylock(mutexes[3])){
                        if(pthread_mutex_trylock(mutexes[6])){
                            break;
                        } else {
                            pthread_mutex_unlock(mutexes[6]);
                            if(pthread_mutex_trylock(mutexes[1])){
                                break;
                            }
                            else{
                                pthread_mutex_unlock(mutexes[1]);
                            }
                        }
                    } else {
                        pthread_mutex_unlock(mutexes[3]);
                    }
                    // pthread_mutex_lock(&mut4);
                    pthread_mutex_lock(mutexes[4]);
                    qDebug() << "Mutex 4 is with train 5";
                    //pthread_mutex_lock(mutexes[3]);
                }
                y+=10;
            }
            else if (x > 460 && y == 280){
                if(x==610){
                    if(pthread_mutex_trylock(mutexes[0])){
                        if(pthread_mutex_trylock(mutexes[2])){
                            if(pthread_mutex_trylock(mutexes[5])){
                                break;
                            }
                            else{
                                pthread_mutex_unlock(mutexes[5]);
                                break;
                            }
                        } else {
                            pthread_mutex_unlock(mutexes[2]);
                        }
                    } else{
                        pthread_mutex_unlock(mutexes[0]);
                    }
                   // pthread_mutex_lock(&mut3);
                    pthread_mutex_lock(mutexes[3]);
                    qDebug() << "Mutex 3 is with train 5";
                }
                if(x==570){
                   // pthread_mutex_unlock(&mut4);
                    pthread_mutex_unlock(mutexes[4]);
                }
                if(x==480){
                   // pthread_mutex_lock(&mut0);
                    pthread_mutex_lock(mutexes[0]);
                    qDebug() << "Mutex 0 is with train 5";
                }
                x-=10;
            }
            else{
                if(y==260){
                   // pthread_mutex_unlock(&mut3);
                    pthread_mutex_unlock(mutexes[3]);
                }
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        default:
            break;
        }
        if(velocidade!=0) msleep(200-velocidade);
        while(velocidade==0); // "laço infinito"
    }
}
