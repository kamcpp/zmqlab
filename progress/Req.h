#pragma once

#include <stdint.h>
#include <assert.h>

#include <string>

#include "Ser.h"

struct Req
{
  uint32_t id = 0;
  uint32_t methodId = 0;
  std::vector<uint32_t> intArgs;
  std::vector<::std::string> strArgs;

  const Buffer serialize() const
  {
    std::vector<uchar_t> buf;
    SER_UINT32(buf, id)
    SER_UINT32(buf, methodId)
    SER_VEC_OF_UINT32(buf, intArgs)
    SER_VEC_OF_STRING(buf, strArgs)
    return Buffer::fromVector(buf);
  }

  void deserialize(const Buffer buf)
  {
    uint32_t cntr = 0;
    DESER_UINT32(buf.data, cntr, id)
    DESER_UINT32(buf.data, cntr, methodId)
    DESER_VEC_OF_UINT32(buf.data, cntr, intArgs)
    DESER_VEC_OF_STRING(buf.data, cntr, strArgs)
    assert(cntr == buf.len);
  }
};
