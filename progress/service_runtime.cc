#include "zhelpers.h"
#include "progress_service.h"
#include "service_runtime.h"

service_runtime_t::service_runtime_t()
  : service_(nullptr) {
  ctx_ = zmq_ctx_new ();
  socket_ = zmq_socket (ctx_, ZMQ_REP);
}

service_runtime_t::~service_runtime_t() {
  zmq_close (socket_);
  zmq_ctx_destroy (ctx_);
}

void service_runtime_t::start() {
  zmq_connect (socket_, "tcp://localhost:3000");
  while (1) {
    zmq_msg_t msg;
    zmq_msg_init(&msg);
    zmq_msg_recv(&msg, socket_, 0);
    buf_t buf;
    buf.data = (uchar_t *)zmq_msg_data(&msg);
    buf.len = zmq_msg_size(&msg);
    req_t req;
    req.deser(buf);
    if (service_) {
      resp_t resp = service_->handle(req);
      send_resp(resp);
    } else {
      resp_t resp = resp_t();
      send_resp(resp);
    }
  }
}

void service_runtime_t::send_resp(resp_t resp) {
  const buf_t buf = resp.ser();
  zmq_msg_t msg;
  zmq_msg_init_data(&msg, buf.data, buf.len, NULL, NULL);
  zmq_msg_send(&msg, socket_, 0);
}