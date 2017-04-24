#include <unistd.h>

#include "zhelpers.h"

int main (int argc, char **argv) {
  void *context = zmq_ctx_new ();
  void *responder = zmq_socket (context, ZMQ_ROUTER);
  zmq_bind (responder, "tcp://*:5559");
  zmq_pollitem_t items [] = {
    { responder, 0, ZMQ_POLLIN, 0 }
  };
  zmq_msg_t message;
  while (1) {
    zmq_poll (items, 1, -1);
    if (items[0].revents & ZMQ_POLLIN) {
      zmq_msg_init (&message);
      zmq_msg_recv (&message, responder, 0);
      sleep (1);
      s_send (responder, "World");
    }
  }
  // while (1) {
  //   char *string = s_recv (responder);
  //   printf ("Received request: [%s]\n", string);
  //   free (string);
  //   sleep (1);
  //   s_send (responder, "World");
  // }
  zmq_close (responder);
  zmq_ctx_destroy (context);
  return 0;
}