#include "sysfs-gpio.h"

#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int pressed;
int pressed_confidenece_level;
int released_confidence_level;
enum { YES, NO } e;
int main(void)
{
	/*Polling */
	struct pollfd fdset[2];
	int nfds = 2;
	int gpio_fd, timeout, rc;
	char *buf[MAX_BUF];
	unsigned int gpio;
	int len;
	int val;

	timeout = 300;

	gpio_init(LED_UP, "out", "none", "0");
	gpio_init(BUTTON_UP, "in", "both", "0");

	gpio_init(LED_DOWN, "out", "none", "0");
	gpio_init(BUTTON_DOWN, "in", "both", "0");

	// poll
	gpio_fd = gpio_fd_open(BUTTON_UP);

	while (1) {
		if ((gpio_read(BUTTON_UP) == 1)) {
			pressed_confidenece_level++;
			if (pressed_confidenece_level > 500) {
				gpio_write(LED_UP, "1");
				if (pressed == 0) {
					pressed = 1;
					printf("UP\n");
				}
				pressed_confidenece_level = 0;
			}
		} else if (gpio_read(BUTTON_UP) == 0) {
			released_confidence_level++;
			if (released_confidence_level > 500) {
				pressed = 0;
				gpio_write(LED_UP, "0");
				released_confidence_level = 0;
			}
		}
	}
	while (0) {
		/*Polling*/
		memset((void *)fdset, 0, sizeof(fdset));

		fdset[0].fd = STDIN_FILENO;
		fdset[0].events = POLLIN;

		fdset[1].fd = gpio_fd;
		fdset[1].events = POLLPRI;

		rc = poll(fdset, nfds, timeout);

		if (rc < 0) {
			printf("\npoll() failed!\n");
			return -1;
		}

		if (rc == 0) {
			// printf(".");
		}

		if (fdset[1].revents & POLLPRI) {
			lseek(fdset[1].fd, 0, SEEK_SET);
			len = read(fdset[1].fd, buf, MAX_BUF);
			// printf("\npoll() GPIO %d interrupt occurred\n", gpio);
			// printf("\tread value: '%c'\n", buf[0]);
			// Control LED_UP
			if ((gpio_read(BUTTON_UP) == 1)) {
				gpio_write(LED_UP, "1");
				if (pressed == 0) {
					pressed = 1;
					printf("UP\n");
				}
			} else if (gpio_read(BUTTON_UP) == 0) {
				pressed = 0;
				gpio_write(LED_UP, "0");
			}
		}
	}
	return 0;
}
