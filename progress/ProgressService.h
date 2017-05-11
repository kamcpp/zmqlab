#pragma once

#include <stdint.h>

#include <map>
#include <memory>

#include "Service.h"

class Progress;
class ProgressService : public Service
{
public:
  ProgressService();
  virtual ~ProgressService();
public:
  virtual Resp handle(Req req);
private:
  uint32_t idCounter_;
  std::map<uint32_t, std::shared_ptr<Progress> > pMap_;
};