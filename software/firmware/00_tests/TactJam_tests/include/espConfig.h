#ifndef _TACTJAM_ESPCONFIG_
#define _TACTJAM_ESPCONFIG_

#include <WiFi.h>

namespace tactjam {
namespace config {
    void DisableEspRadios() {
        WiFi.mode(WIFI_OFF);
        btStop();
    }
}
}

#endif //_TACTJAM_ESPCONFIG_
