#pragma once

#include "Resp.h"
#include "Req.h"

class Service
{
public:
  virtual Resp handle(Req req) = 0;
};