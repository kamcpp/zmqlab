#pragma once

#include <stdint.h>

#include "Req.h"
#include "Resp.h"

class ProgressSyncProxy
{
public:
  ProgressSyncProxy();
  virtual ~ProgressSyncProxy();
public:
  uint32_t startProgress();
  void resetProgress(const uint32_t id);
  uint32_t getProgress(const uint32_t id);
private:
  const Resp send(const Req req);
private:
  void *ctx_;
  void *reqSocket_;
};