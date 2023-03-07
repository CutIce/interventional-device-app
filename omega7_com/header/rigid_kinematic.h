//
// Created by hsh on 2023/2/27.
//

#ifndef OMEGA7_COM_RIGID_KINEMATIC_H
#define OMEGA7_COM_RIGID_KINEMATIC_H

#include <QObject>

class rigid_kinematic : public QObject {
    Q_OBJECT

public:
    explicit rigid_kinematic(QObject *parent = nullptr);

    ~rigid_kinematic() override;

private:

};


#endif //OMEGA7_COM_RIGID_KINEMATIC_H
