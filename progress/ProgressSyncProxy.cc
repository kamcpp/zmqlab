#include "zhelpers.h"
#include "ProgressSyncProxy.h"

ProgressSyncProxy::ProgressSyncProxy()
{
  ctx_ = zmq_ctx_new();
  reqSocket_ = zmq_socket(ctx_, ZMQ_REQ);
  zmq_connect(reqSocket_, "tcp://localhost:2000");
}

ProgressSyncProxy::~ProgressSyncProxy()
{
  zmq_close(reqSocket_);
  zmq_ctx_destroy(ctx_);
}

uint32_t ProgressSyncProxy::startProgress()
{
  Req req;
  req.methodId = 100;
  req.intArgs.push_back(0);
  const Resp resp = send(req);
  return resp.intValues[0];
}

void ProgressSyncProxy::resetProgress(const uint32_t id)
{
  Req req;
  req.methodId = 200;
  req.intArgs.push_back(id);
  const Resp resp = send(req);
}

uint32_t ProgressSyncProxy::getProgress(const uint32_t id)
{
    Req req;
    req.methodId = 300;
    req.intArgs.push_back(id);
    const Resp resp = send(req);
    uint32_t ret = resp.intValues[0];
    return ret;
}

const Resp ProgressSyncProxy::send(const Req req)
{
  {
    const Buffer buf = req.serialize();
    zmq_msg_t msg;
    zmq_msg_init_data(&msg, buf.data, buf.len, NULL, NULL);
    zmq_msg_send(&msg, reqSocket_, 0);
  }
  {
    zmq_msg_t msg;
    zmq_msg_init(&msg);
    zmq_msg_recv(&msg, reqSocket_, 0);
    Buffer buf;
    buf.data = (uchar_t *)zmq_msg_data(&msg);
    buf.len = zmq_msg_size(&msg);
    Resp resp;
    resp.deserialize(buf);
    return resp;
  }
}
