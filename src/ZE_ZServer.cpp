/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/*!
\par File Header: 
File: ZE_ZServer.cpp <br>
Description: Implementation source file for core ZEngine TCP Server Object. <br>
Author(s): James Turk <br>
$Id: ZE_ZServer.cpp,v 1.4 2003/04/08 03:30:50 cozman Exp $<br>

    \file ZE_ZServer.cpp
    \brief Source file for ZServer.

    Implementation file for ZServer, the TCP Server class for ZEngine.
**/

#include "ZE_ZServer.h"

#ifdef USE_SDL_NET

namespace ZE
{

void ZServer::CloseSocket(int num)
{
    SDLNet_TCP_Close(rClientSockets[num]);
    rClientSockets[num] = NULL;
    if(rVerbose)
        rEngine->WriteLog(FormatStr("Closing socket #%d",num));
}

ZServer::ZServer(bool v)
{
    rEngine = ZEngine::GetInstance();

    rSocket = NULL;
    rSocketSet = NULL;
    rClientSockets = NULL;
    rMaxClients = 0;
    rVerbose = v;
    rWaitTime = 0;
}

ZServer::~ZServer()
{
    Stop();
}

bool ZServer::Start(int maxClients, Uint16 port)
{
    IPaddress ip;

    rMaxClients = maxClients;
    rClientSockets = new TCPsocket[rMaxClients];

    rSocketSet = SDLNet_AllocSocketSet(rMaxClients+1);  //need one more (for server socket)
    if(!rSocketSet)
    {
        rEngine->ReportError(ZERR_NET_SERVER,FormatStr("Failed to create sockets (%s).",SDLNet_GetError()));
        Stop();
        return false;
    }
    else if(rVerbose)
        rEngine->WriteLog(FormatStr("ZServer: Created server with %d available sockets.",rMaxClients));

    for(int i=0; i < rMaxClients; ++i)
        rClientSockets[i] = NULL;

    if(SDLNet_ResolveHost(&ip,NULL,port) < 0)   //try to resolve the host
        rEngine->ReportError(ZERR_NET_SERVER,FormatStr("Failed to create host server on port %d (%s).",port,SDLNet_GetError()));
    else if(rVerbose)
        rEngine->WriteLog(FormatStr("ZServer: Created host server on port %d.",port));

    rSocket = SDLNet_TCP_Open(&ip); //try to open socket
    if(!rSocket || SDLNet_TCP_AddSocket(rSocketSet,rSocket) == -1)
    {
        rEngine->ReportError(ZERR_NET_SERVER,"Failed to open server TCP socket.");
        Stop();
        return false;
    }

    return true;
}

void ZServer::Stop()
{
    if(rSocket)
    {
        SDLNet_TCP_Close(rSocket);
        rSocket = NULL;
    }
    if(rSocketSet)
    {
        SDLNet_FreeSocketSet(rSocketSet);
        rSocketSet = NULL;
    }
    if(rClientSockets)
    {
        for(int i=0; i < rMaxClients; ++i)
        {
            if(rClientSockets[i])
            {
                CloseSocket(i);
            }
        }
        delete[] rClientSockets;
    }

    rMaxClients = 0;
}

void ZServer::SetWaitTime(int wait)
{
    rWaitTime = wait;
}

void ZServer::CheckSockets()
{
    ZByte buf[MAX_MSG_LEN];
    int result,size,count;

    SDLNet_CheckSockets(rSocketSet, rWaitTime);

    if(SDLNet_SocketReady(rSocket))  //new client
    {
        for(count=0; count < rMaxClients; ++count)  //find first open socket
        {
            if(!rClientSockets[count]) 
                break;
        }

        if(rClientSockets[count])   //if it exists the set is full
        {
            rEngine->ReportError(ZERR_NET_SERVER,FormatStr("All %d ports full.",rMaxClients));
        }
        else
        {
            rClientSockets[count] = SDLNet_TCP_Accept(rSocket);
            SDLNet_TCP_AddSocket(rSocketSet, rClientSockets[count]);
            if(rVerbose)
                rEngine->WriteLog(FormatStr("ZServer: Adding socket #%d.",count+1));
        }
    }

    //check all sockets for activity//
    for(int i=0; i < rMaxClients; ++i)
    {
        if(SDLNet_SocketReady(rClientSockets[i]))   //incoming message
        {
            result = SDLNet_TCP_Recv(rClientSockets[i], buf, MAX_MSG_LEN);

            if(result <= 0)    //disconnect bad sockets
                CloseSocket(i);
            else if(rVerbose)
                rEngine->WriteLog(FormatStr("ZServer: Received %d bytes on Port %d",result,i));

            size = result;
            if(rVerbose)
                rEngine->WriteLog("ZServer: Mirroring data: ");
            for(int j=0; j < rMaxClients; ++j)
            {
                if(rClientSockets[j] && i != j) //send to open sockets that aren't the same
                {
                    result = SDLNet_TCP_Send(rClientSockets[j],buf,size);
                    if(rVerbose)
                        rEngine->WriteLog(FormatStr("    +%d bytes on socket %d.",size,j));
                }
            }
        }
    }
}

int ZServer::Clients()
{
    int numClients=0;

    for(int i=0; i < rMaxClients; ++i)
    {
        if(rClientSockets[i])
            ++numClients;
    }

    return numClients;
}

int ZServer::WaitTime()
{
    return rWaitTime;
}

}    //namespace ZE

#endif //USE_SDL_NET
