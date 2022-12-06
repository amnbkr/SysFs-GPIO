#include "sysfs-gpio.h"

int gpio_export(char *pin)
{
	int fd;
	// write export
	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (fd == -1)
		printf("Cannot open the export file\n");
	write(fd, pin, strlen(pin));
	// close Export
	close(fd);
	return 0;
}
int gpio_unexport(char *pin)
{
	int fd;

	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	if (fd == -1) {
		printf("Cannot open the unexport file\n");
	}
	// Write unxport
	write(fd, pin, strlen(pin));
	// close unexport
	close(fd);
	return 0;
}
int gpio_direction(char *pin, char *direction)
{
	int fd;
	char str[MAX_BUF];

	sprintf(str, "/sys/class/gpio/gpio%s/direction", pin);
	fd = open(str, O_WRONLY);
	if (fd == -1)
		printf("Cannot open the direction of %s file\n", pin);
	// Write Direction
	write(fd, direction, strlen(direction));
	// Close Direction
	close(fd);
	return 0;
}
int gpio_set_edge(char *pin, char *edge)
{
	int fd;
	char str[MAX_BUF];

	sprintf(str, "/sys/class/gpio/gpio%s/edge", pin);
	fd = open(str, O_WRONLY);
	if (fd == -1) {
		printf("Cannot open the edge of LED_UP file\n");
	}
	write(fd, edge, strlen(edge));
	close(fd);
}
int gpio_set_active_low(char *pin, char *pullup)
{
	int fd;
	char str[MAX_BUF];

	sprintf(str, "/sys/class/gpio/gpio%s/active_low", pin);
	fd = open(str, O_WRONLY);
	if (fd == -1) {
		printf("Cannot open the edge of LED_UP file\n"); // hello
	}

	write(fd, pullup, strlen(pullup));
	close(fd);
}
void gpio_init(char *pin, char *direction, char *edge, char *pullup)
{
	// write export
	gpio_export(pin);
	// write direction
	gpio_direction(pin, direction);
	// set edge
	gpio_set_edge(pin, edge);
	// set pullup
	gpio_set_active_low(pin, pullup);
}
int gpio_write(char *pin, char *value)
{
	int fd;
	char str[MAX_BUF];

	sprintf(str, "/sys/class/gpio/gpio%s/value", pin);
	fd = open(str, O_WRONLY);
	if (fd == -1) {
		printf("Cannot open the value of BUTTON_UP file\n");
	}
	write(fd, value, 1);
	close(fd);
	return fd;
}
char gpio_read(char *pin)
{
	int fd;
	char str[MAX_BUF];
	char value;
	char ch;

	sprintf(str, "/sys/class/gpio/gpio%s/value", pin);
	fd = open(str, O_RDONLY);
	if (fd == -1) {
		printf("Cannot open the value of gpio %s value file\n", pin);
	}
	read(fd, &ch, 1);
	if (ch != '0') {
		value = 1;
	} else {
		value = 0;
	}
	close(fd);
	return value;
}
/*open file*/
int gpio_fd_open(char *pin)
{
	int fd;
	char str[MAX_BUF];

	sprintf(str, "/sys/class/gpio/gpio%s/value", pin);
	fd = open(str, O_RDONLY);
	if (fd == -1) {
		printf("Cannot open the value of gpio %s value file\n", pin);
	}
	return fd;
}
