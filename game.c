/*
 * game.c file
 * 2022 JH139940 SK139959
 *
 * PLAYER:      X or O 
 * NOTE:        Player is written in capital letters.
 * If you enter X you get first player mode,
 * else you are second no matter what input you enter.
 * 
 * Compilation: make
 * Usage:       ./game INTERFACE_NAME DEST_MAC_ADDR PLAYER 
 * NOTE:        This program requires root privileges.
*/

// Included libs
#include <unistd.h>
#include "./game_confs/tictactoe.h"
#include "./game_confs/receiver.h"
#include "./game_confs/sender.h"

/* 
  // Don't know if it will be used.
  // and if it works.
  // Receive an invitation
  int receive_inv(char* if_name, int receive_sfd){
    // Prepare received frame
    char* frame;
    char* fdata;
    // NOTE 818: REMEMBER TO FREE ALLOCATED FRAME!
    frame = malloc(ETH_FRAME_LEN);
    memset(frame, 0, ETH_FRAME_LEN);
    // Skip eth header length
    fdata = frame + ETH_HLEN;
    // receive frame with ETH_P_CUSTOM
    recvfrom(receive_sfd, frame, ETH_FRAME_LEN, 0, NULL, NULL);
    // Configure sending socket
    int send_sfd = send_conf(if_name, fdata);
    // NOTE 818: Release allocated memory
    free(frame);
    // Return descriptor
    return send_sfd;
  }

  //   int send_sfd = receive_inv(argv[1], receive_sfd);
//*/

int main(int argc, char** argv) {
  // Open descriptors
  int receive_sfd = receive_conf(argv[1]);
  int send_sfd = send_conf(argv[1],argv[2]);
  // Input Output game loops
  if(strcmp(argv[3],"X") == 0){
      // For first player
      first_player_ioLoop(receive_sfd, send_sfd);
  }
  else{
      // For second player
      second_player_ioLoop(receive_sfd, send_sfd);
  }
  // Close descriptors 
  close(receive_sfd);
  close(send_sfd);
  return EXIT_SUCCESS;
}

/* End of game.c file */
