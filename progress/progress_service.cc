#include <thread>
#include <iostream>

#include "progress.h"
#include "progress_service.h"

progress_service_t::progress_service_t() 
  : id_cntr_(0) {
}

progress_service_t::~progress_service_t() {
}

resp_t progress_service_t::handle(req_t req) {
  resp_t resp;
  resp.id = 0;
  resp.status = 0;
  resp.req_id = req.id;
  switch (req.method_id) {
    case 100: {
      ::std::cout << "New progress ..." << ::std::endl;
      ::std::shared_ptr<progress_t> p(new progress_t);
      p->id = ++id_cntr_;
      p->val = 0;
      pmap_[p->id] = p;
      resp.int_values.push_back(p->id);
      break;
    }
    case 200: {
      ::std::cout << "Reset the progress ..." << ::std::endl;
      uint32_t id = req.int_args[0];
      if (pmap_.find(id) == pmap_.end()) {
        resp.status = 1000;
      } else {
        pmap_[id]->val = 0;
      }
      break;
    }
    case 300: {
      ::std::cout << "Reading progress ..." << ::std::endl;
      uint32_t id = req.int_args[0];
      if (pmap_.find(id) == pmap_.end()) {
        resp.status = 1000;
      } else {
        pmap_[id]->val += 10;
        if (pmap_[id]->val > 100) {
          pmap_[id]->val = 100;
        }
        ::std::cout << "Current value for id(" << id << ") is " << pmap_[id]->val << ::std::endl;
        resp.int_values.push_back(pmap_[id]->val);
      }
      break;
    }
    default:
      resp.status = 1001;
  }
  return resp;
}