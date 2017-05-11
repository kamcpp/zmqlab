#include <iostream>

#include "ProgressSyncProxy.h"

int main(int argc, char **argv)
{
  std::cout << "Creating proxy object ... ";
  std::shared_ptr<ProgressSyncProxy> syncProxy(new ProgressSyncProxy);
  std::cout << "done" << std::endl;
  std::cout << "Starting a progress ... ";
  uint32_t id = syncProxy->startProgress();
  std::cout << "done. Progress id is " << id << std::endl;
  std::cout << "Resetting the progress ... ";
  syncProxy->resetProgress(id);
  std::cout << "done." << id << std::endl;
  uint32_t currentProgress = 0;
  do
  {
    std::cout << "Reading the progress ... ";
    currentProgress = syncProxy->getProgress(id);
    std::cout << "done. Progress is " << currentProgress << "%" << std::endl;
  }
  while (currentProgress < 100);
  std::cout << "Bye." << std::endl;
  return 0;
}