#pragma once

#include <stdint.h>
#include <assert.h>

#include <string>

#include "Ser.h"

struct Resp
{
  uint32_t id = 0;
  uint32_t reqId = 0;
  uint32_t status = 0;
  std::vector<uint32_t> intValues;
  std::vector<::std::string> strValues;

  const Buffer serialize() const
  {
    std::vector<uchar_t> buf;
    SER_UINT32(buf, id)
    SER_UINT32(buf, reqId)
    SER_UINT32(buf, status)
    SER_VEC_OF_UINT32(buf, intValues)
    SER_VEC_OF_STRING(buf, strValues)
    return Buffer::fromVector(buf);
  }

  void deserialize(const Buffer buf)
  {
    uint32_t cntr = 0;
    DESER_UINT32(buf.data, cntr, id)
    DESER_UINT32(buf.data, cntr, reqId)
    DESER_UINT32(buf.data, cntr, status)
    DESER_VEC_OF_UINT32(buf.data, cntr, intValues)
    DESER_VEC_OF_STRING(buf.data, cntr, strValues)
    assert(cntr == buf.len);
  }
};
