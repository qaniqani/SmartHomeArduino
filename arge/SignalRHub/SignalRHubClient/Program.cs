using Microsoft.AspNet.SignalR.Client.Hubs;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SignalRHubClient
{
    class Program
    {
        static void Main(string[] args)
        {
            // Almost the same usage as JavaScript without generated proxy
            var hubConn = new HubConnection("http://localhost:6473/myhubs");
            var timeHubProxy = hubConn.CreateHubProxy("PascalCasedMyDateTimeHub");
            var chatHubProxy = hubConn.CreateHubProxy("myChatHub");
            chatHubProxy.On("appendNewMessage", delegate(string name, string message)
            {
                Console.WriteLine("{0}: {1}", name, message);
            });

            hubConn.Start().Wait();
            string inputLine;
            while (!string.IsNullOrEmpty(inputLine = Console.ReadLine()))
            {
                Task<DateTime> t = timeHubProxy.Invoke<DateTime>("PascalCasedGetServerDateTime");
                t.Wait();
                Console.WriteLine((DateTime)t.Result);
                chatHubProxy.Invoke("broadcastMessage", "dzy", inputLine).Wait();
            }
        }
    }
}
