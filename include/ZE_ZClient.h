/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
    \file ZE_ZClient.h
    \brief Definition file for ZClient.

    Definition file for ZClient, the TCP Client class for ZEngine.
    <br>$Id: ZE_ZClient.h,v 1.6 2003/05/13 01:30:51 cozman Exp $<br>
    \author James Turk
**/

#ifndef __ze_zclient_h__
#define __ze_zclient_h__

#include "ZE_ZEngine.h"

#ifdef USE_SDL_NET

namespace ZE
{

/*!
    \brief ZEngine class for a simplified TCP client.

    ZClient net client class, used to create a simple TCP game client for use with ZServer.
    \since 0.8.3
**/
class ZClient
{
    protected:
        //! Pointer to ZEngine Object.
        ZEngine *rEngine;
        //! SDL_net socket for connection.
        TCPsocket rSocket;
        //! Socket set for connection.
        SDLNet_SocketSet rSocketSet;
        //! Verbose setting for connection logs.
        bool rVerbose;
        //! Wait timeout setting for recieves on connection. [Defaults to 0.]
        int rWaitTime;

    public:
        /*!
            \brief Default Constructor.

            Default Constructor, does basic initialization.  If verbose is true connection data will be added to log file.
            \param verbose Sets verbose setting of client. [Defaults to false.]
        **/
        ZClient(bool verbose=false);

        /*!
            \brief Destructor, disconnects and frees memory.

            Destructor calls ZClient::Disconnect().
        **/
        virtual ~ZClient();

        /*!
            \brief Connects to a server on a given port.

            Connects to a server (given in dotted ip form) on a given port.
            \param server Dotted IP address to connect to.
            \param port Port number to connect to.
            \return true if connected, false otherwise.
        **/
        bool Connect(char *server, Uint16 port);

        /*!
            \brief Disconnect client.

            Disconnect from server if connected.
        **/
        void Disconnect();

        /*!
            \brief Sets wait time for recieves.

            Sets wait time in milliseconds , time which ZClient::Recieve will wait before returning if there is no data.
            Before this is called for the first time WaitTime is 0.
            \param wait Wait time.
        */
        void SetWaitTime(int wait);

        /*!
            \brief Send data too connected server.

            Sends data to server if available.
            \param data Pointer to data buffer to send.
            \param size Size of data buffer. (Can't be larger than MAX_MSG_LEN as defined in ZE_Defines.h)
            \return True if data could be sent, false upon error.
        **/
        bool Send(ZByte *data, int size);

        /*!
            \brief Recieve data if available.

            Recieves data from server if available, waiting for timeout period if no data is pending.
            \param data Pointer to buffer to store data in. (Must be large enough, needs not be more than MAX_MSG_LEN as defined in ZE_Defines.h)
            \return Size of recieved data stored to buffer. (<MAX_MSG_LEN)
        **/
        int Receive(ZByte *data);

        /*!
            \brief Return connected state.

            Returns state of connection.
            \return true if connected, false otherwise
        **/
        bool Connected();

        /*!
            \brief Gets current wait time.

            Gets amount of time in milliseconds that is specified to wait for data on Recieve.
            \return Wait time.
        **/
        int WaitTime();
};

} //namespace ZE

#endif //USE_SDL_NET

#endif //__ze_zclient_h__
