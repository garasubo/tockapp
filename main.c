#include <console.h>
#include <led.h>
#include <timer.h>

char hello[] = "Hello World!\r\n";
char error[] = "getch failed!\r\n";


static void cb_led(
  int a __attribute__((unused)),
  int b __attribute__((unused)),
  int c __attribute__((unused)),
  void* d __attribute__((unused))) {
    led_toggle(0);
}

static void nop(
  int a __attribute__((unused)),
  int b __attribute__((unused)),
  int c __attribute__((unused)),
  void* d __attribute__((unused))) {}

static tock_timer_t timer;

int main(void) {
    putnstr_async(hello, sizeof(hello), nop, NULL);
    bool enabled = 0;
    while (1) {
        int c = getch();

        if (c == TOCK_FAIL) {
          putnstr_async(error, sizeof(error), nop, NULL);
        } else {
            if (enabled) {
                timer_cancel(&timer);
                led_off(0);
                enabled = false;
            } else {
                timer_every(500, cb_led, NULL, &timer);
                enabled = true;
            }
        }
    }
    return 0;
}

