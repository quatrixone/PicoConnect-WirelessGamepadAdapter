// web_server_nonblocking.c
#include "lwip/tcp.h"
#include "lwip/api.h"
#include "pico/cyw43_arch.h"
#include <string.h>
#include <stdio.h>

const char* html_page =
    "<!DOCTYPE html>"
    "<html>"
    "<head><title>Controller Emulator Configuration</title></head>"
    "<body>"
    "<h1>Controller Emulator</h1>"
    "<form action=\"/set_target\" method=\"GET\">"
    "Select Target OS:<br>"
    "<input type=\"radio\" id=\"windows\" name=\"target\" value=\"windows\" checked>"
    "<label for=\"windows\">Windows</label><br>"
    "<input type=\"radio\" id=\"linux\" name=\"target\" value=\"linux\">"
    "<label for=\"linux\">Linux</label><br>"
    "<input type=\"radio\" id=\"android\" name=\"target\" value=\"android\">"
    "<label for=\"android\">Android</label><br><br>"
    "<input type=\"submit\" value=\"Set Target\">"
    "</form>"
    "</body>"
    "</html>";

const char* response_ok = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Connection: close\r\n\r\n"
    "<!DOCTYPE html>"
    "<html><body><h1>Target OS Updated</h1><a href=\"/\">Go Back</a></body></html>";

void handle_http_request(struct netconn *conn) {
    struct netbuf *inbuf;
    char *buf;
    u16_t len;

    if (netconn_recv(conn, &inbuf) == ERR_OK) {
        netbuf_data(inbuf, (void**)&buf, &len);
        
        if (strncmp(buf, "GET /set_target?target=windows", 29) == 0) {
            printf("Target set to Windows\n");
        } else if (strncmp(buf, "GET /set_target?target=linux", 26) == 0) {
            printf("Target set to Linux\n");
        } else if (strncmp(buf, "GET /set_target?target=android", 28) == 0) {
            printf("Target set to Android\n");
        }

        netconn_write(conn, response_ok, strlen(response_ok), NETCONN_NOCOPY);
    }

    netbuf_delete(inbuf);
    netconn_close(conn);
}

void web_server_nonblocking_task() {
    struct netconn *conn, *newconn;
    err_t err;

    conn = netconn_new(NETCONN_TCP);
    if (conn == NULL) {
        printf("Failed to create new connection\n");
        return;
    }

    netconn_bind(conn, NULL, 80);
    netconn_listen(conn);
    netconn_set_nonblocking(conn, true);  // Set non-blocking

    while (1) {
        err = netconn_accept(conn, &newconn);  // Non-blocking accept

        if (err == ERR_OK && newconn) {
            handle_http_request(newconn);
            netconn_delete(newconn);
        }

        cyw43_arch_poll();  // Important: Ensure other tasks can run
    }

    netconn_close(conn);
    netconn_delete(conn);
}