#include <zmq.h>
#include <string.h>

static int
s_send (void *socket, char *string) {
    int size = zmq_send (socket, string, strlen (string), 0);
    return size;
}

int main (int argc, char **argv) {
  printf ("HELOO");
  void *context = zmq_ctx_new ();
  void *requester = zmq_socket (context, ZMQ_DEALER);
  printf (">>>>>>");
  zmq_connect (requester, "tcp://localhost:5559");
  printf (">>>>>>>>>>>");
  int request_nbr;
  for (request_nbr = 0; request_nbr < 10; request_nbr++) {
    printf("<<<<<s");
    s_send (requester, "Hello");
    printf(">>>>>");
    // char *string = s_recv (requester);
    // printf ("Received reply %d [%s]\n", request_nbr, string);
    // free (string);
  }
  zmq_pollitem_t items [] = {
    { requester, 0, ZMQ_POLLIN, 0 }
  };
  zmq_msg_t message;
  while (1) {
    zmq_poll (items, 1, -1);
    if (items[0].revents & ZMQ_POLLIN) {
      zmq_msg_init (&message);
      zmq_msg_recv (&message, requester, 0);
      printf("===\n");
    }
  }
  zmq_close (requester);
  zmq_ctx_destroy (context);
  printf("BYE");
  return 0;
}