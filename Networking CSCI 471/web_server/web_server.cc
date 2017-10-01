//Please note that most of the included code was pasted with slight modification from the lecture slides


// **************************************************************************************
// * Echo Strings (web_server.cc)
// * -- Accepts TCP connections and then echos back each string sent.
// **************************************************************************************
#include "web_server.h"


// **************************************************************************************
// * processConnection()
// * - Handles reading the line from the network and sending it back to the client.
// * - Returns 1 if the client sends "QUIT" command, 0 if the client sends "CLOSE".
// **************************************************************************************

// This is used to reduce duplicate code and to make the HTTP responses below easier to see.
std::string httpresponse(std::string code, std::string content, std::string length) {
  return "HTTP/1.0 " + code + "\nAccept-Ranges: bytes\nContent-Type: " + content + "\nContent-Length: " + length + "\r\n\r\n";
}

//INTERUPT HANDLING GOOD PRACTICE:
//    http://zguide.zeromq.org/cpp:interrupt
static int s_interrupted = 0;
static void s_signal_handler (int signal_value) {
    s_interrupted = 1;
    
}

static void s_catch_signals (void) {
    struct sigaction action;
    action.sa_handler = s_signal_handler;
    action.sa_flags = 0;
    sigemptyset (&action.sa_mask);
    sigaction (SIGINT, &action, NULL);
    sigaction (SIGTERM, &action, NULL);
}


int processConnection(int sockFd) {

  int keepGoing = 1;
  std::string message = "";   // Used to amalgamate incoming packets
  
  s_catch_signals ();

  while (keepGoing) {
    
      if (s_interrupted) { // If an interupt was caught, close the socket
      std::cout << "Interupt caught, closing socket" << std::endl;
      close(sockFd);
      exit(0);
    }

    // Call read() call to get a buffer/line from the client.
    char buffer[1024];
    bzero(buffer, sizeof(buffer)/sizeof(*buffer));
    read(sockFd, buffer, 10);
    std::string _read(buffer); //Convert to string
    
    message += _read;   //Append packet to overall message.
    
    //If the message is complete, it should have 2 carriage returns.
    //      If we have a complete message, it's time to process it
    if (message.substr(message.length()-5, message.length()).find("\r\n\r\n") != std::string::npos) {
      DEBUG << message << std::endl;
      
      //Split the message across its newlines so we can properly process its content
      std::vector<std::string> lines;
      std::stringstream ss;
      ss.str(message);
      std::string item;
      while (std::getline(ss, item, '\n')) lines.push_back(item);
      
      //Extract the exact file the request wants
      std::string resource = lines[0].substr(lines[0].find("GET")+5, lines[0].find("HTTP")-6);
      if (resource == "") resource = "file1.html";
            
      //See if we have the file on the server
      DEBUG << "Attempting to load " << resource << std::endl;
      std::ifstream file(resource);
      std::string response;
      
      if (file.fail()) {  //If we don't have the file
        DEBUG << "Can't find " + resource + "; sending 404" << std::endl;
        
        //Let browser know it was an invalid request.
        response = httpresponse("404 Not Found", "text/html", "0");
        DEBUG << response << std::endl;
        
        //Send the response
        write(sockFd, response.data(), response.length());
      } 
      
      else {      //If we found the file, there's more to be done.    
        
        //If the file isn't of the specified format or the request is bad:
        if ((resource.find("file") == std::string::npos && resource.find("image") == std::string::npos) || (lines[0].find("GET") == std::string::npos)) {
          DEBUG << resource << " invalid file format request, sending 400" << std::endl;
          response = httpresponse("400 Bad Request", "html", "0");
          write(sockFd, response.data(), response.length());
          DEBUG << response << std::endl;
        }
        
        //Send the file if it fits the criteria:
        else {
          DEBUG << "Found " + resource + "; sending 200 and content" << std::endl;
          
          //Get extension so we know how to send the file.       
          std::string extension = resource.substr(resource.find('.')+1, resource.length());
          
          //Supported image formats
          if (extension == "jpg" || extension == "png" || extension == "ico") {
            extension = "image/" + extension;
            
            //Send a buffer of binary image data of the exact size of the image
            //Code influenced by http://www.cplusplus.com/reference/fstream/ifstream/rdbuf/
            std::filebuf* pbuf = file.rdbuf();
            std::size_t size = pbuf->pubseekoff (0,file.end,file.in);
            pbuf->pubseekpos (0,file.in);
            char* _buffer=new char[size];
            pbuf->sgetn (_buffer,size);

            //Let the browser know the request was valid
            response = httpresponse("200 OK", extension, std::to_string(size));
            DEBUG << response << std::endl;
            
            //Send response+content
            write(sockFd, response.data(), response.length());
            write(sockFd, _buffer, size);
          }
          
          //Treat everything else as rawtext
          else if (extension == "html" || extension == "css")  {
            extension = "text/" + extension;
            
            //Read in entire text buffer, send it all at once.
            std::string html_out = "";
            while (std::getline(file, item)) html_out += item;
            
            //Let the browser know the request was valid
            response = httpresponse("200 OK", extension, std::to_string(html_out.length()));
            DEBUG << response << std::endl;

            //Send response+content
            write(sockFd, response.data(), response.length());
            write(sockFd, html_out.data(), html_out.length());
            DEBUG << "Preview of content sent:\n" << html_out.substr(0,200) << std::endl;
          }
          
         //Asking for a valid file but one that's not allowed.
         else {
            DEBUG << resource << " requesting unauthorized file, sending 403" << std::endl;
            response = httpresponse("403 Forbidden", "html", "0");
            write(sockFd, response.data(), response.length());
            DEBUG << response << std::endl;
          }
        }
      }
      break;
    }
  }
}


// **************************************************************************************
// * main()
// * - Sets up the sockets and accepts new connection until processConnection() returns 1
// **************************************************************************************

int main (int argc, char *argv[]) {

  // ********************************************************************
  // * Process the command line arguments
  // ********************************************************************
  boost::log::add_console_log(std::cout, boost::log::keywords::format = "%Message%");
  boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);

  // ********************************************************************
  // * Process the command line arguments
  // ********************************************************************
  int opt = 0;
  while ((opt = getopt(argc,argv,"v")) != -1) {
    
    switch (opt) {
    case 'v':
      boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::debug);
      break;
    case ':':
    case '?':
    default:
      std::cout << "useage: " << argv[0] << " -v" << std::endl;
      exit(-1);
    }
  }

  // *******************************************************************
  // * Creating the inital socket is the same as in a client.
  // ********************************************************************
  int     listenFd = -1;
       // Call socket() to create the socket you will use for lisening.
  DEBUG << "Calling Socket() assigned file descriptor " << listenFd << ENDL;
  listenFd = socket(AF_INET, SOCK_STREAM, 0);

  
  // ********************************************************************
  // * The bind() and calls take a structure that specifies the
  // * address to be used for the connection. On the cient it contains
  // * the address of the server to connect to. On the server it specifies
  // * which IP address and port to lisen for connections.
  // ********************************************************************
  struct sockaddr_in servaddr;
  srand(time(NULL));
  int port = (rand() % 10000) + 1024;
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = PF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);


  // ********************************************************************
  // * Binding configures the socket with the parameters we have
  // * specified in the servaddr structure.  This step is implicit in
  // * the connect() call, but must be explicitly listed for servers.
  // ********************************************************************
  DEBUG << "Calling bind(" << listenFd << "," << &servaddr << "," << sizeof(servaddr) << ")" << ENDL;
  int bindSuccesful = 0;
  while (!bindSuccesful) {
    // You may have to call bind multiple times if another process is already using the port
    // your program selects.
    bindSuccesful = bind(listenFd, (sockaddr *) &servaddr, sizeof(servaddr));
  }
  std::cout << "Using port " << port << std::endl;


  // ********************************************************************
  // * Setting the socket to the listening state is the second step
  // * needed to being accepting connections.  This creates a queue for
  // * connections and starts the kernel listening for connections.
  // ********************************************************************
  int listenQueueLength = 1;
  DEBUG << "Calling listen(" << listenFd << "," << listenQueueLength << ")" << ENDL;
  listen(listenFd, listenQueueLength);
 

  // ********************************************************************
  // * The accept call will sleep, waiting for a connection.  When 
  // * a connection request comes in the accept() call creates a NEW
  // * socket with a new fd that will be used for the communication.
  // ********************************************************************
  int quitProgram = 0;
  while (true) {
    int connFd = 0;

    DEBUG << "Calling accept(" << listenFd << " NULL,NULL)." << ENDL << "\nProgram will now block until accepted.\n";

    // The accept() call checks the listening queue for connection requests.
    // If a client has already tried to connect accept() will complete the
    // connection and return a file descriptor that you can read from and
    // write to. If there is no connection waiting accept() will block and
    // not return until there is a connection.
    
    connFd = accept(listenFd, (sockaddr *) NULL, NULL);
    
    DEBUG << "We have recieved a connection on " << connFd << ENDL;

    
    quitProgram = processConnection(connFd);
   
    close(connFd);
  }

  close(listenFd);
  DEBUG << "Connection closed." << ENDL;
  return(0);
}
