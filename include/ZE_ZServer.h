/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
    \file ZE_ZServer.h
    \brief Definition file for ZServer.

    Definition file for ZServer, the TCP Server class for ZEngine.
    <br>$ id: $<br>
    \author James Turk
**/

#ifndef __ze_zserver_h__
#define __ze_zserver_h__

#include "ZE_ZEngine.h"

#ifdef USE_SDL_NET

namespace ZE
{

/*!
    \brief ZEngine class for simplified TCP server.

    ZServer server class, used to create a simple TCP game server for use with ZClient.  A very simple turnaround server, all the server does
    is accept connections and relay all recieved data to all other clients.
    \since 0.8.3
**/
class ZServer
{
    private:
        //! Pointer to ZEngine Object.
        ZEngine *rEngine;
        //! SDL_net socket for connection.
        TCPsocket rSocket;
        //! Socket set for client connections.
        SDLNet_SocketSet rSocketSet;
        //! SDL_net TCPSockets for client connections.
        TCPsocket *rClientSockets;
        //! Maximum number of clients.
        int rMaxClients;
        //! Verbose setting for connection logs.
        bool rVerbose;
        //! Wait timeout setting for recieves on connection. [Defaults to 0.]
        int rWaitTime;

        /*!
            \brief Closes a socket.

            Close a socket given by it's number.
            \param num Socket number to close.
        **/
        void CloseSocket(int num);

    public:
        /*!
            \brief Default Constructor.

            Default Constructor, does basic initialization.  If verbose is true connection data will be added to log file.
            \param verbose Sets verbose setting of client. [Defaults to false.]
        **/
        ZServer(bool verbose=false);

        /*!
            \brief Destructor, disconnects server and frees memory.

            Destructor calls ZServer::Stop().
        **/
        virtual ~ZServer();

        /*!
            \brief Starts server.

            Starts server with a number of maximum clients and on a specified port.
            \param maxClients Maximum number of clients possible to connect to server.
            \param port Port to listen on for connections.
            \return True if server started, false otherwise.
        **/
        bool Start(int maxClients, Uint16 port);

        /*!
            \brief Stops server.

            Closes port and disconnects all clients.
        **/
        void Stop();

        /*!
            \brief Sets wait time for recieves.

            Sets wait time in milliseconds , time which ZServer::CheckSockets will wait before returning if there is no activity.
            Before this is called for the first time the wait time is 0.
            \param wait Wait time.
        */
        void SetWaitTime(int wait);

        /*!
            \brief Check sockets for connections or data.

            Check sockets for connections or data, accepting new connections or relaying data from existing connections.  Waits the specified wait
            period.  This should be called very often to keep events flowing.
        **/
        void CheckSockets();

        /*!
            \brief Gets number of clients.

            Finds number of connected clients.
            \return Number of clients.
        **/
        int Clients();

        /*!
            \brief Gets current wait time.

            Gets amount of time in milliseconds that is specified to wait for data on CheckSockets.
            \return Wait time.
        **/
        int WaitTime();
};

} //namespace ZE

#endif //USE_SDL_NET

#endif //__ze_zserver_h__
