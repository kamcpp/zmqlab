#include <iostream>

#include "progress_sync_proxy.h"

int main(int argc, char **argv) {
  ::std::shared_ptr<progress_sync_proxy_t> sync_proxy(new progress_sync_proxy_t);
  uint32_t id = sync_proxy->start_progress();
  sync_proxy->reset_progress(id);
  uint16_t current_progress = sync_proxy->get_progress(id);
  while (current_progress <= 100) {
    ::std::cout << "Progress: " << current_progress << " % ..." << ::std::endl;
    current_progress = sync_proxy->get_progress(id);
  }
  ::std::cout << "Done." << ::std::endl;
  return 0;
}