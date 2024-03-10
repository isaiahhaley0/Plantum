using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json;
using PlantumLib.Models;

namespace PlantumLib.Services
{
    public static class APIHandler
    {

        private static string baseEndpoint = "http://192.168.0.47:5000";

        public static async Task<List<string>> GetCams()
        {

            string EndPoint = baseEndpoint + "/camera_info";
            HttpClient client = new HttpClient();
            try
            {
                using HttpResponseMessage response = await client.GetAsync(EndPoint);
                //        response.EnsureSuccessStatusCode();
                string responseBody = await response.Content.ReadAsStringAsync();
                // Above three lines can be replaced with new helper method below
                // string responseBody = await client.GetStringAsync(uri);
                var st_l = JsonSerializer.Deserialize<CameraList>(responseBody);
                Console.WriteLine(responseBody);
                return st_l.Cameras.ToList();
            }
            catch (HttpRequestException e)
            {
                Console.WriteLine("\nException Caught!");
                Console.WriteLine("Message :{0} ", e.Message);
            }
            return new List<string> { };
        }

        public static async Task<Camera> GetCamera(string CamName)
        {
            string EndPoint = baseEndpoint + "/camera_info?Name=" + CamName;
            HttpClient client = new HttpClient();
            
            try
            {
                using HttpResponseMessage response = await client.GetAsync(EndPoint);
                //        response.EnsureSuccessStatusCode();
                string responseBody = await response.Content.ReadAsStringAsync();
                var cam = JsonSerializer.Deserialize<Camera>(responseBody);
                return cam;
            }
            catch (HttpRequestException e)
            {

            }
            return null;
        }

    }
}
