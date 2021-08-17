#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/container.h"
#include "../Model/deepptr.h"
#include "../Model/file.h"
#include <QDebug>

class Controller {
private:
    Container<Deepptr<File>> listaAccount;

public:
    Controller();
    void aggiungiAccount();
};

#endif // CONTROLLER_H
