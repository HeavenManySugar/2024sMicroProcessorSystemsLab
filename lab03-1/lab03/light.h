#ifndef LIGHT_H
#define LIGHT_H

#include <fcntl.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <QApplication>

using namespace std;

namespace light {
    int gpio_export(unsigned int gpio) {
      int fd, len;
      char buf[64];

      fd = open("/sys/class/gpio/export", O_WRONLY);
      if (fd < 0) {
        perror("gpio/export");
        return fd;
      }

      len = snprintf(buf, sizeof(buf), "%d", gpio);
      write(fd, buf, len);
      close(fd);

      return 0;
    }

    int gpio_unexport(unsigned int gpio) {
      int fd, len;
      char buf[64];

      fd = open("/sys/class/gpio/unexport", O_WRONLY);
      if (fd < 0) {
        perror("gpio/export");
        return fd;
      }

      len = snprintf(buf, sizeof(buf), "%d", gpio);
      write(fd, buf, len);
      close(fd);
      return 0;
    }

    int gpio_set_dir(unsigned int gpio, string dirStatus) {
      int fd;
      char buf[64];

      snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", gpio);

      fd = open(buf, O_WRONLY);
      if (fd < 0) {
        perror("gpio/direction");
        return fd;
      }

      if (dirStatus == "in") {
        write(fd, "in", 3);
      } else {
        write(fd, "out", 4);
      }

      close(fd);
      return 0;
    }

    int gpio_set_value(unsigned int gpio, int value) {
      int fd;
      char buf[64];

      snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpio);

      fd = open(buf, O_WRONLY);
      if (fd < 0) {
        perror("gpio/set-value");
        return fd;
      }

      if (value == 1) {
        write(fd, "1", 2);
      } else {
        write(fd, "0", 2);
      }

      close(fd);
      return 0;
    }
    constexpr unsigned int gpio[4] = {255, 254, 297, 394};
    void lightOn(int LEDNum) {
        gpio_export(gpio[LEDNum]);
        gpio_set_dir(gpio[LEDNum], "out");
        gpio_set_value(gpio[LEDNum], 1);
    };
    void lightOff(int LEDNum) {
        gpio_set_value(gpio[LEDNum], 0);
        gpio_unexport(gpio[LEDNum]);
    }

}


#endif // LIGHT_H
