#pragma once

class Service;
class ServiceRuntime
{
public:
  ServiceRuntime();
  virtual ~ServiceRuntime();
public:
  void registerService(std::shared_ptr<Service> service)
  {
    service_ = service;
  }
  void uniregisterService()
  {
    service_ = nullptr;
  }
public:
  void start();
private:
  void sendResp(Resp resp);
private:
  std::shared_ptr<Service> service_;
  void *ctx_;
  void *socket_;
};