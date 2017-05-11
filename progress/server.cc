#include <iostream>

#include "ProgressService.h"
#include "ServiceRuntime.h"

int main(int argc, char **argv)
{
  std::shared_ptr<ProgressService> service(new ProgressService);
  std::shared_ptr<ServiceRuntime> rt(new ServiceRuntime);
  rt->registerService(service);
  rt->start();
  // TODO: Unregister and perform a clean exit
  return 0;
}