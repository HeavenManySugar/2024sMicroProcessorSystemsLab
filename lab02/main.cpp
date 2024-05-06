#include <fcntl.h>
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

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

int main(int argc, char *argv[]) {
  unsigned int gpio[4] = {255, 481, 297, 394};
  if (string(argv[1]).compare("Mode_Shine") == 0) {
    for (int i=0;i<stoi(argv[2]);i++){
      for(int j=0;j<2;j++) {  
        gpio_export(gpio[j]);
        gpio_set_dir(gpio[j], "out");
        gpio_set_value(gpio[j], 1);
        gpio_set_value(gpio[2+j], 0);
        gpio_unexport(gpio[2+j]);
      }
      sleep(1);
      for(int j=0;j<2;j++) {  
        gpio_export(gpio[2+j]);
        gpio_set_dir(gpio[2+j], "out");
        gpio_set_value(gpio[2+j], 1);
        gpio_set_value(gpio[j], 0);
        gpio_unexport(gpio[j]);
      }
      sleep(1);
    }
    for(int i=0;i<4;i++){
      gpio_set_value(gpio[i], 0);
      gpio_unexport(gpio[i]);
    }
  }else{
    int LEDN = int(argv[1][3] - '0' - 1);
    if (string(argv[2]).compare("on") == 0) {
      gpio_export(gpio[LEDN]);
      gpio_set_dir(gpio[LEDN], "out");
      gpio_set_value(gpio[LEDN], 1);
    } else if (string(argv[2]).compare("off") == 0) {
      gpio_set_value(gpio[LEDN], 0);
      gpio_unexport(gpio[LEDN]);
    } 


  }

  return 0;
}