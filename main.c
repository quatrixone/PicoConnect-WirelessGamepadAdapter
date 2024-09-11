int main(void) {
    board_init();
    tusb_init();
    setup_bluetooth();
    connect_to_wifi();

    // Start the web server in a separate task or thread
    // Depending on your setup, you might need to create a new thread
    // For simplicity, we'll run it in the main loop with non-blocking behavior
    // Alternatively, use a RTOS or cooperative multitasking

    while (1) {
        tud_task();          // Handle USB events
        loop_bluetooth();    // Handle Bluetooth events
        hid_task();         // Send HID reports
        web_server_task();  // Handle web server requests
    }

    return 0;
}
