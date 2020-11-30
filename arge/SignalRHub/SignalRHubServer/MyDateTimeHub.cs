using Microsoft.AspNet.SignalR;
using Microsoft.AspNet.SignalR.Hubs;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Web;

namespace SignalRHubServer
{
    /// <summary>
    /// The client must use the names defined by HubName and HubMethodName 
    /// to RPC this Hub and its methods.
    /// JS Example: 
    ///   var timeHub = $.connection.PascalCasedMyDateTimeHub;
    ///   var serverTime = chatHub.server.PascalCasedGetServerDateTime();
    /// </summary>
    [HubName("PascalCasedMyDateTimeHub")]
    public class MyDateTimeHub : Hub
    {
        [HubMethodName("PascalCasedGetServerDateTime")]
        public async Task<DateTime> GetServerDateTime()
        {
            return await Task.Run<DateTime>(() => DateTime.Now);
        }
    }
}