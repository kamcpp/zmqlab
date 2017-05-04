#include <iostream>

#include "progress_sync_proxy.h"

int main(int argc, char **argv) {
  ::std::cout << "Creating proxy object ... ";
  ::std::shared_ptr<progress_sync_proxy_t> sync_proxy(new progress_sync_proxy_t);
  ::std::cout << "done" << ::std::endl;
  ::std::cout << "Starting a progress ... ";
  uint32_t id = sync_proxy->start_progress();
  ::std::cout << "done. Progress id is " << id << ::std::endl;
  ::std::cout << "Resetting the progress ... ";
  sync_proxy->reset_progress(id);
  ::std::cout << "done." << id << ::std::endl;
  uint32_t current_progress = 0;
  do {
    ::std::cout << "Reading the progress ... ";
     current_progress = sync_proxy->get_progress(id);
    ::std::cout << "done. Progress is " << current_progress << "%" << ::std::endl;
  } while (current_progress < 100);
  ::std::cout << "Bye." << ::std::endl;
  return 0;
}