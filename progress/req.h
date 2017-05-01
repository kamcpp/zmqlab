#pragma once

#include <stdint.h>
#include <assert.h>

#include "ser.h"

enum method_t {
  UNKNOWN = 0,
  RESET = 1,
  START = 2,
  GET = 3
};

struct req_t {
  method_t method;
  uint32_t progress_id;

  const buf_t ser() const {
    ::std::vector<uchar_t> buf;
    SER_UINT32(buf, method)
    SER_UINT32(buf, progress_id)
    return buf_t::from_vector(buf);
  }

  void deser(const buf_t buf) {
    uint32_t cntr = 0;
    DESER_UINT32(buf.data.get(), cntr, method)
    DESER_UINT32(buf.data.get(), cntr, progress_id)
    assert(cntr == buf.len);
  }
};