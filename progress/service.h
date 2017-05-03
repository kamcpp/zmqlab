#pragma once

#include "resp.h"
#include "req.h"

class service_t {
public:
  virtual resp_t handle(req_t req) = 0;
};