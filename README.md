# Moon Lamp Frontend and Firmware

[![Video](https://img.youtube.com/vi/3wEAKVvzJyA/0.jpg)](https://www.youtube.com/watch?v=3wEAKVvzJyA)

# Setup

Replace the placeholders for the SSID and PASSWORD in `firmware/main.cpp`.

You can use the `Makefile` to download the firmware and frontend files to your ESP32.

Setup a python virtual environment:

```
python3 -m venv venv
source ./venv/bin/activate
pip install -r requirements.txt
```

Now run

```
make upload_fs
make upload_firmware
```

The initial install of the firmware needs to be over USB. Subsequent installs can use OTA updates using "moonbase.local" as the upload port.
