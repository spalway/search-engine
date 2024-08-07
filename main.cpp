#include <iostream>

#include "DocumentParser.h"
#include "UserInterface.h"

using namespace std;

int main(int argc, char **argv ) {
    if(argc<2){
        return 1;
    }
    string command = argv[1];
    if(command =="index"){
        UserInterface ui;
        ui.createIndex(argv[2]);
        ui.writeIndex();
    }else if(command =="query"){
        UserInterface ui;
        ui.readIndex();
        ui.enterQuery(argv[2], false);
    }else if(command =="ui"){
        UserInterface ui;
        ui.displayMenu();
    }
    return 0;
}