#pragma once

#include <stdint.h>
#include <assert.h>

#include <string>

#include "ser.h"

struct req_t {
  uint32_t id = 0;
  uint32_t method_id = 0;
  ::std::vector<uint32_t> int_args;
  ::std::vector<::std::string> str_args;

  const buf_t ser() const {
    ::std::vector<uchar_t> buf;
    SER_UINT32(buf, id)
    SER_UINT32(buf, method_id)
    SER_VEC_OF_UINT32(buf, int_args)
    SER_VEC_OF_STRING(buf, str_args)
    return buf_t::from_vector(buf);
  }

  void deser(const buf_t buf) {
    uint32_t cntr = 0;
    DESER_UINT32(buf.data.get(), cntr, id)
    DESER_UINT32(buf.data.get(), cntr, method_id)
    DESER_VEC_OF_UINT32(buf.data.get(), cntr, int_args)
    DESER_VEC_OF_STRING(buf.data.get(), cntr, str_args)
    assert(cntr == buf.len);
  }
};