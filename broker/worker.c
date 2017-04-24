#include <unistd.h>

#include "zhelpers.h"

int main (int argc, char **argv) {
  void *context = zmq_ctx_new ();
  void *responder = zmq_socket (context, ZMQ_REP);
  zmq_connect (responder, "tcp://localhost:5560");
  while (1) {
    char *string = s_recv (responder);
    printf ("Received request: [%s]\n", string);
    free (string);
    sleep (1);
    s_send (responder, "World");
  }
  zmq_close (responder);
  zmq_ctx_destroy (context);
  return 0;
}