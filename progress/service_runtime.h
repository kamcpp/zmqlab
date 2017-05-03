#pragma once

class service_t;
class service_runtime_t {
public:
  service_runtime_t() 
    : service_(nullptr) {
  }
  virtual ~service_runtime_t() {
  }
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
  ::std::shared_ptr<service_t> service_;
};