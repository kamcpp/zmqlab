#include <iostream>

#include "zhelpers.h"

int main(int argc, char **argv)
{
  std::cout << "Starting the broker ..." << std::endl;
  void *context = zmq_ctx_new ();
  void *frontend = zmq_socket (context, ZMQ_ROUTER);
  void *backend  = zmq_socket (context, ZMQ_DEALER);
  std::cout << "Binding the ports ... ";
  zmq_bind (frontEnd, "tcp://*:2000");
  zmq_bind (backEnd,  "tcp://*:3000");
  std::cout << "done" << std::endl;
  zmq_pollitem_t items [] =
  {
    { frontend, 0, ZMQ_POLLIN, 0 },
    { backend,  0, ZMQ_POLLIN, 0 }
  };
  std::cout << "Loop started." << std::endl;
  while (1)
  {
    zmq_msg_t message;
    zmq_poll (items, 2, -1);
    if (items [0].revents & ZMQ_POLLIN)
    {
      std::cout << "We have a message from frontend." << std::endl;
      while (1)
      {
        zmq_msg_init (&message);
        zmq_msg_recv (&message, frontend, 0);
        int more = zmq_msg_more (&message);
        zmq_msg_send (&message, backEnd, more? ZMQ_SNDMORE: 0);
        zmq_msg_close (&message);
        if (!more)
          break;
      }
      std::cout << "Message transfered to backend." << std::endl;
    }
    if (items [1].revents & ZMQ_POLLIN)
    {
      std::cout << "We have a message from backend." << std::endl;
      while (1)
      {
        zmq_msg_init (&message);
        zmq_msg_recv (&message, backend, 0);
        int more = zmq_msg_more (&message);
        zmq_msg_send (&message, frontEnd, more? ZMQ_SNDMORE: 0);
        zmq_msg_close (&message);
        if (!more)
          break;
      }
      std::cout << "Message transfered to frontend." << std::endl;
    }
  }
  zmq_close (frontEnd);
  zmq_close (backEnd);
  zmq_ctx_destroy (context);
  return 0;
}