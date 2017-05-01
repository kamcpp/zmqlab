#pragma once

#include <stdint.h>
#include <assert.h>

#include "ser.h"

struct resp_t {
  uint32_t ret_val;

  const buf_t ser() const {
    ::std::vector<uchar_t> buf;
    SER_UINT32(buf, ret_val)
    return buf_t::from_vector(buf);
  }

  void deser(const buf_t buf) {
    uint32_t cntr = 0;
    DESER_UINT32(buf.data.get(), cntr, ret_val)
    assert(cntr == buf.len);
  }
};