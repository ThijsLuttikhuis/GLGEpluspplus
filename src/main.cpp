//
// Created by thijs on 11-08-20.
//


#include "GameController.h"

int main() {
    GameController gameController;
    gameController.initialize();

    while (true) {
        gameController.update();

        // check for exit button
        if (KeyboardInput::getExit(gameController.getWindow())) {
            break;
        }
    }

    return 0;
}