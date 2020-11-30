using Microsoft.AspNet.SignalR;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Web;

namespace SignalRHubServer
{
    /// <summary>
    /// The client must use camel-cased names to RPC this Hub and its methods.
    /// JS Example: 
    ///   var chatHub = $.connection.myChatHub;
    ///   chatHub.server.broadcastMessage("dzy", "Hello all!");
    /// </summary>
    public class MyChatHub : Hub
    {
        public async Task BroadcastMessage(string callerName, string message)
        {
            // Case-insensitive when the server RPC the client's methods
            await Clients.All.appendnewmessage(callerName, message);
        }
    }
}