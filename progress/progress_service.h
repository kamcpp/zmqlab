#pragma once

#include <stdint.h>

#include <map>
#include <memory>

#include "service.h"

class progress_t;
class progress_service_t : public service_t {
public:
  progress_service_t();
  virtual ~progress_service_t();
public:
  virtual resp_t handle(req_t req);
private:
  uint32_t id_cntr_;
  ::std::map<uint32_t, ::std::shared_ptr<progress_t> > pmap_;
};