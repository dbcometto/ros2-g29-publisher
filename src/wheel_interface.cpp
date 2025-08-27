#include <cstdio>
#include <iostream>

#include <fcntl.h>      // open()
#include <unistd.h>     // read(), close()
#include <linux/input.h> // struct input_event, event types
#include <sys/ioctl.h>   // ioctl

#include <rclcpp/rclcpp.hpp>

std::string device_name = "/dev/input/event6";

auto openDevice() {
  int fd = open(device_name.c_str(), O_RDONLY);
  if (fd < 0) {
      std::cerr << "Failed to open " << device_name << std::endl;
  }
  return fd;
}

void read_event(int fd) {
  struct input_event ev;

  ssize_t n = read(fd, &ev, sizeof(ev));
      if (n == sizeof(ev)) {
          if (ev.type == EV_ABS) {  // absolute axis event
              std::cout << "Code: " << ev.code 
                        << ", Value: " << ev.value << std::endl;
          }
      } else {
          std::cerr << "Read failed or incomplete" << std::endl;
      }

}


int main(int argc, char ** argv)
{
  (void) argc;
  (void) argv;

  int fd = openDevice();

  while (true) {
    read_event(fd);
  }

  printf("hello world g29-publisher package\n");
  return 0;
}
