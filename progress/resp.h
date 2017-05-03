#pragma once

#include <stdint.h>
#include <assert.h>

#include <string>

#include "ser.h"

struct resp_t {
  uint32_t id = 0;
  uint32_t req_id = 0;
  ::std::vector<uint32_t> int_values;
  ::std::vector<::std::string> str_values;

  const buf_t ser() const {
    ::std::vector<uchar_t> buf;
    SER_UINT32(buf, id)
    SER_UINT32(buf, req_id)
    SER_VEC_OF_UINT32(buf, int_values)
    SER_VEC_OF_STRING(buf, str_values)
    return buf_t::from_vector(buf);
  }

  void deser(const buf_t buf) {
    uint32_t cntr = 0;
    DESER_UINT32(buf.data.get(), cntr, id)
    DESER_UINT32(buf.data.get(), cntr, req_id)
    DESER_VEC_OF_UINT32(buf.data.get(), cntr, int_values)
    DESER_VEC_OF_STRING(buf.data.get(), cntr, str_values)
    assert(cntr == buf.len);
  }
};