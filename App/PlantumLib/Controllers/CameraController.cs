using PlantumLib.Models;
using PlantumLib.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PlantumLib.Controllers
{
    public class CameraController
    {
        public List<Camera> Cameras { get; set; }
        public async Task<List<Camera>> PopulateCams()
        {
       
                var camList =await APIHandler.GetCams();
                
                List<Camera> cams = new List<Camera>(); 
                foreach (var cam in camList) { 
                    Camera camera = await APIHandler.GetCamera(cam);
                
                    

                    cams.Add(camera);
                }

                return cams;
           
        }

    }
}
