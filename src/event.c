#if defined _WIN32 || defined _WIN64
  /*
    Very buggy and might not work properly , but work ;)
    TODO: fix this
  */
  #ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
  #endif
  #include <winsock2.h>
  #include <synchapi.h>
char keypress(){
    HANDLE  hStdin = GetStdHandle(STD_INPUT_HANDLE);
     DWORD val = WaitForSingleObject(hStdin,0);;
     switch(val){
     case WAIT_TIMEOUT:{
      return 0;
     }
     case WAIT_FAILED:{
      return 0;
     }
     case WAIT_OBJECT_0:{
        struct _INPUT_RECORD *buffer=malloc(sizeof(*buffer));
        DWORD *out=malloc(sizeof(DWORD));
        if(!ReadConsoleInput(hStdin,buffer,1,out))
        MessageBox(NULL, TEXT("WAS HERE FAILED"), TEXT("FAILED POLL"),
              MB_OK);
        return buffer->Event.KeyEvent.uChar.AsciiChar;
     }
   case WAIT_ABANDONED_0:{
    return 0;
   }
     default:{
      MessageBox(NULL, TEXT("POLLING FAILED"), TEXT("FAILED POLL"),
            MB_OK);
      exit(GetLastError());
     }

     }
    return 0;
  }

#else
  #include <poll.h>
  #include <unistd.h>
  char keypress() {
    int poll_count = 1;
    int timeout = 0;
    struct pollfd input[] = {{.events = POLLIN}};
    if (poll(input, poll_count, timeout)) {
      char buffer;
      if (read(0, &buffer, sizeof(buffer))>0) {
        return buffer;
      }
    }
    return 0;
  }
#endif