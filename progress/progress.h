#pragma once

#include <stdint.h>

struct progress_t {
  uint32_t id;
  uint32_t val;
  progress_t()
    : id(0) , val(0) {
  }
};