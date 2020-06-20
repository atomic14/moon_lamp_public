// #include "esp_http_server.h"

class LEDControl;
class Papertrail;

class WebControl
{
private:
    Papertrail *papertrail;
    LEDControl *ledControl;
    // httpd_handle_t httpd;

    // void createHandler(const char *path, http_method method, esp_err_t (*handler)(httpd_req_t *r));

public:
    WebControl(Papertrail *papertrail, LEDControl *ledControl);
    // esp_err_t handleRequest(httpd_req_t *req);
};