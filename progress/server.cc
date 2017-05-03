#include <iostream>

#include "progress_service.h"
#include "service_runtime.h"

int main(int argc, char **argv) {
  ::std::shared_ptr<progress_service_t> service(new progress_service_t);
  ::std::shared_ptr<service_runtime_t> rt(new service_runtime_t);
  rt->register_service(service);
  rt->start();
  return 0;
}