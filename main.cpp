#include <stdio.h>
#include "vm.h"
#include <QApplication>
#include <iostream>
#include "window.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Window *window = new Window(NULL);

    window->resize(64, 32);
    
    // show the label
    window->show();

    app.exec();

    
    delete window;
    
    return 0; 

}
