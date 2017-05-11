#include <thread>
#include <iostream>

#include "Progress.h"
#include "ProgressService.h"

ProgressService::ProgressService()
  : idCounter_(0)
{
}

ProgressService::~ProgressService()
{
}

Resp ProgressService::handle(Req req)
{
  Resp resp;
  resp.id = 0;
  resp.status = 0;
  resp.reqId = req.id;
  switch (req.methodId)
  {
    case 100:
    {
      std::cout << "New progress ..." << std::endl;
      std::shared_ptr<Progress> p(new Progress);
      p->id = ++idCounter_;
      p->val = 0;
      pMap_[p->id] = p;
      resp.intValues.push_back(p->id);
      break;
    }
    case 200:
    {
      std::cout << "Reset the progress ..." << std::endl;
      uint32_t id = req.int_args[0];
      if (pMap_.find(id) == pMap_.end())
      {
        resp.status = 1000;
      }
      else
      {
        pMap_[id]->val = 0;
      }
      break;
    }
    case 300:
    {
      std::cout << "Reading progress ..." << std::endl;
      uint32_t id = req.intArgs[0];
      if (pMap_.find(id) == pMap_.end())
      {
        resp.status = 1000;
      }
      else
      {
        pMap_[id]->val += 10;
        if (pMap_[id]->val > 100)
        {
          pMap_[id]->val = 100;
        }
        std::cout << "Current value for id(" << id << ") is " << pMap_[id]->val << std::endl;
        resp.intValues.push_back(pMap_[id]->val);
      }
      break;
    }
    default:
      resp.status = 1001;
  }
  return resp;
}