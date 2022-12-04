#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BUF 64
#define LED_UP "24"
#define LED_DOWN "23"
#define BUTTON_UP "4"
#define BUTTON_DOWN "15"
#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define HIGH "1"
#define LOW "0"

int gpio_export(char* pin);
int gpio_unexport(char* pin);
int gpio_direction(char* pin, char* direction);
int gpio_set_edge(char* pin, char* edge);
int gpio_set_active_low(char* pin, char* pullup);
void gpio_init(char* pin, char* direction, char* edge, char* pullup);
int gpio_write(char* pin, char* value);
char gpio_read(char* pin);
int gpio_fd_open(char* pin);