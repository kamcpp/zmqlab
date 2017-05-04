#pragma once

class service_t;
class service_runtime_t {
public:
  service_runtime_t();
  virtual ~service_runtime_t();
public:
  void register_service(::std::shared_ptr<service_t> service) {
    service_ = service;
  }
  void unregister_service() {
    service_ = nullptr;
  }
public:
  void start();
private:
  void send_resp(resp_t resp);
private:
  ::std::shared_ptr<service_t> service_;
  void *ctx_;
  void *socket_;
};