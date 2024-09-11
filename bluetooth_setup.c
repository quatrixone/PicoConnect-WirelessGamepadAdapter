// bluetooth_setup.c
#include <Bluepad32.h>
#include <stdio.h>

#define MAX_CONTROLLERS 4

GamepadPtr gamepads[MAX_CONTROLLERS];

void onConnectedGamepad(GamepadPtr gp) {
    for (int i = 0; i < MAX_CONTROLLERS; i++) {
        if (gamepads[i] == nullptr) {
            gamepads[i] = gp;
            printf("Gamepad %d connected!\n", i + 1);
            break;
        }
    }
}

void onDisconnectedGamepad(GamepadPtr gp) {
    for (int i = 0; i < MAX_CONTROLLERS; i++) {
        if (gamepads[i] == gp) {
            gamepads[i] = nullptr;
            printf("Gamepad %d disconnected!\n", i + 1);
            break;
        }
    }
}

void setup_bluetooth() {
    BP32.setup(&onConnectedGamepad, &onDisconnectedGamepad);
}

void handle_gamepad_input() {
    for (int i = 0; i < MAX_CONTROLLERS; i++) {
        if (gamepads[i]) {
            // Example: Read left stick X and Y
            int lx = gamepads[i]->axisLeftX();
            int ly = gamepads[i]->axisLeftY();
            bool button_a = gamepads[i]->a();

            // Store or process these inputs for HID emulation
            // You may want to store them in a shared structure
        }
    }
}

void loop_bluetooth() {
    BP32.update();
    handle_gamepad_input();
}
