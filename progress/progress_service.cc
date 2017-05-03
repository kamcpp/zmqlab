#include <thread>

#include "progress.h"
#include "progress_service.h"

progress_service_t::progress_service_t() 
  : id_cntr_(0) {
}

progress_service_t::~progress_service_t() {
}

resp_t progress_service_t::handle(req_t req) {
  /* ::std::shared_ptr<progress_t> p(new progress_t);
  p->id = ++id_cntr_;
  pmap_[p->id] = p; */

  // TODO
  
}