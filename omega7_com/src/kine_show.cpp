//
// Created by hsh on 2023/3/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_kine_show.h" resolved

#include "../header/kine_show.h"
#include "../form/ui_kine_show.h"


Kinematic_Displayer::Kinematic_Displayer(QWidget *parent) :
        QWidget(parent) {

}

Kinematic_Displayer::~Kinematic_Displayer() {
    delete ui;
}
