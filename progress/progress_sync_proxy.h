#pragma once

#include <stdint.h>

#include "req.h"
#include "resp.h"

class progress_sync_proxy_t {
public:
  progress_sync_proxy_t();
  virtual ~progress_sync_proxy_t();
public:
  uint32_t start_progress();
  void reset_progress(const uint32_t id);
  uint32_t get_progress(const uint32_t id);
private:
  const resp_t send(const req_t req);
private:
  void *ctx_;
  void *reqr_;
};