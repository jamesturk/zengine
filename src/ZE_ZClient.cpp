/*******************************************************************************
        This file is Part of the ZEngine Library for 2D game development.
                   Copyright (C) 2002, 2003 James Turk

                     Licensed under a BSD-style license.

    The maintainer of this library is James Turk (james@conceptofzero.net) 
     and the home of this Library is http://www.zengine.sourceforge.net
*******************************************************************************/

/**
    \file ZE_ZClient.cpp
    \brief Source file for ZClient.

    Implementation file for ZClient, the TCP Client class for ZEngine.
    <br>$Id: ZE_ZClient.cpp,v 1.8 2003/06/11 00:15:08 cozman Exp $<br>
    \author James Turk
**/

#include "ZE_ZClient.h"

#ifdef USE_SDL_NET

namespace ZE
{

std::string num2dotted4(unsigned int num)
{
    vector<int> ip;
    int d=16777216; //2^24
    int m;
    
    while(d > 0)
    {
        m = num/d;
        num %= d;
        ip.push_back(m);
        d /= 256;
    }

    return FormatStr("%d.%d.%d.%d",ip[3],ip[2],ip[1],ip[0]);
}

ZClient::ZClient(bool verbose)
{
    rEngine = ZEngine::GetInstance();
    rSocket = NULL;
    rSocketSet = NULL;
    rVerbose = verbose;
    rWaitTime = 0;
}

ZClient::~ZClient()
{
    Disconnect();
}

bool ZClient::Connect(char *server, Uint16 port)
{
    IPaddress ip;

    if(SDLNet_ResolveHost(&ip,server,port) < 0)
        rEngine->ReportError(ZERR_NET_CLIENT,FormatStr("Failed to resolve host: %s:%d",server,port));
    else if(rVerbose)
        rEngine->WriteLog(FormatStr("ZClient: resolved host: %s:%d",server,port));

    rEngine->WriteLog(FormatStr("IP: %s",num2dotted4(ip.host).c_str()));

    rSocket = SDLNet_TCP_Open(&ip); //try to open rSocket

    if(!rSocket)
    {
        rEngine->ReportError(ZERR_NET_CLIENT,"Failed to open TCP socket.");
        Disconnect();
        return false;
    }

    rSocketSet = SDLNet_AllocSocketSet(1);  //get a set for the single socket
    if(!rSocketSet || SDLNet_TCP_AddSocket(rSocketSet,rSocket) == -1)
    {
        rEngine->ReportError(ZERR_NET_CLIENT,"Failed to create socket set.");
        Disconnect();
        return false;
    }

    return true;
}

void ZClient::Disconnect()
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
}

void ZClient::SetWaitTime(int wait)
{
    rWaitTime = wait;
}

bool ZClient::Send(ZByte *data, int size)
{
    int sent = 0;

    if(rSocket)
    {
        sent = SDLNet_TCP_Send(rSocket,data,size);

        if(sent < size)
        {
            rEngine->ReportError(ZERR_NET_CLIENT,FormatStr("Failed to send data, closing socket: %s", SDLNet_GetError()));
            Disconnect();
            return false;
        }
        else if(rVerbose)
            rEngine->WriteLog(FormatStr("ZClient: Sent %d bytes to server.",sent));

        return true;
    }
    else
    {
        rEngine->ReportError(ZERR_NOSOCKET,"Send");
        return false;
    }
}

int ZClient::Receive(ZByte *data)
{
    int received = 0;

    if(rSocket)
    {
        if(SDLNet_CheckSockets(rSocketSet, rWaitTime) > 0 && SDLNet_SocketReady(rSocket))
        {
            received = SDLNet_TCP_Recv(rSocket,data,MAX_MSG_LEN);
            if(received <= 0)
            {
                Disconnect();
                rEngine->ReportError(ZERR_NET_CLIENT,FormatStr("TCP_Recv failed [%s]",SDLNet_GetError()));
            }
            else if(rVerbose)
                rEngine->WriteLog(FormatStr("ZClient: received %d bytes.",received));
        }
    }
    else
        rEngine->ReportError(ZERR_NOSOCKET,"Receive");

    return received;
}

bool ZClient::Connected()
{
    return rSocket?true:false;
}

int ZClient::WaitTime()
{
    return rWaitTime;
}

}    //namespace ZE

#endif //USE_SDL_NET
