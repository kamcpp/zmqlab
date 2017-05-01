#include <iostream>

#include "progress_service.h"

int main(int argc, char **argv) {
  ::std::shared_ptr<progress_service_t> service(new progress_service_t);
  service->start();
  return 0;
}