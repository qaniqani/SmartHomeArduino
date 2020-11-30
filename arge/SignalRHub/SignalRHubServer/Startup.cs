using Microsoft.AspNet.SignalR;
using Microsoft.Owin;
using Owin;
[assembly: OwinStartupAttribute(typeof(SignalRHubServer.Startup))]
//[assembly: OwinStartup(typeof(SignalRTest.Startup))]

namespace SignalRHubServer
{
    public partial class Startup
    {
        public void Configuration(IAppBuilder app)
        {
            app.MapHubs("/myhubs", new HubConfiguration());
        }
    }
}
