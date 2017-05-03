#include "zhelpers.h"
#include "progress_sync_proxy.h"

progress_sync_proxy_t::progress_sync_proxy_t() {
  ctx_ = zmq_ctx_new ();
  reqr_ = zmq_socket (ctx_, ZMQ_REQ);
  zmq_connect (reqr_, "tcp://localhost:2000");
}

progress_sync_proxy_t::~progress_sync_proxy_t() {
  zmq_close (reqr_);
  zmq_ctx_destroy (ctx_);
}

uint32_t progress_sync_proxy_t::start_progress() {
  req_t req;
  req.method_id = 100;
  req.int_args.push_back(0);
  const resp_t resp = send(req);
  return resp.int_values[0];
}

void progress_sync_proxy_t::reset_progress(const uint32_t id) {
  req_t req;
  req.method_id = 200;
  req.int_args.push_back(id);
  const resp_t resp = send(req);
}

uint32_t progress_sync_proxy_t::get_progress(const uint32_t id) {
    req_t req;
    req.method_id = 300;
    req.int_args.push_back(id);
    const resp_t resp = send(req);
    return resp.int_values[0];
}

const resp_t progress_sync_proxy_t::send(const req_t req) {
  {
    const buf_t buf = req.ser();
    zmq_msg_t msg;
    zmq_msg_init_data(&msg, buf.data.get(), buf.len, NULL, NULL);
    zmq_msg_send(&msg, reqr_, 0);
  }
  {
    zmq_msg_t msg;
    zmq_msg_init(&msg);
    zmq_msg_recv(&msg, reqr_, 0);
    buf_t buf;
    buf.data = ::std::shared_ptr<uchar_t>((uchar_t *)zmq_msg_data(&msg));
    buf.len = zmq_msg_size(&msg);
    resp_t resp;
    resp.deser(buf);
    return resp;
  }
}
