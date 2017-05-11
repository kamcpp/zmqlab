#include "zhelpers.h"

#include "ProgressService.h"
#include "ServiceRuntime.h"

ServiceRuntime::ServiceRuntime()
  : service_(nullptr)
{
  ctx_ = zmq_ctx_new ();
  socket_ = zmq_socket (ctx_, ZMQ_REP);
}

ServiceRuntime::~ServiceRuntime()
{
  zmq_close (socket_);
  zmq_ctx_destroy (ctx_);
}

void ServiceRuntime::start()
{
  zmq_connect (socket_, "tcp://localhost:3000");
  while (1)
  {
    zmq_msg_t msg;
    zmq_msg_init(&msg);
    zmq_msg_recv(&msg, socket_, 0);
    Buffer buf;
    buf.data = (uchar_t *)zmq_msg_data(&msg);
    buf.len = zmq_msg_size(&msg);
    Req req;
    req.deserialize(buf);
    if (service_)
    {
      Resp resp = service_->handle(req);
      sendResp(resp);
    }
    else
    {
      Resp resp = Resp();
      sendResp(resp);
    }
  }
}

void ServiceRuntime::sendResp(Resp resp)
{
  const Buffer buf = resp.serialize();
  zmq_msg_t msg;
  zmq_msg_init_data(&msg, buf.data, buf.len, NULL, NULL);
  zmq_msg_send(&msg, socket_, 0);
}
