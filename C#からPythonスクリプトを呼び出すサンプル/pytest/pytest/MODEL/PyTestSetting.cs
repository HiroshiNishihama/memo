using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace pytest.CONTROL
{
    public class appConfig
    {
        public string pythoninterpreterpath { get; set; }
        public string pythonscriptpath { get; set; }
    }
    class PyTestSetting
    {
        private appConfig _appConfig;
        private string _configfilename = @"pytestconfig.json";

        public PyTestSetting()
        {
            this.load();
        }

        public void load()
        {
            using (var sr = new StreamReader(_configfilename))
            {
                string json = sr.ReadToEnd();
                _appConfig = JsonSerializer.Deserialize<appConfig>(json);
            }
        }

        public void save()
        {
            using (var sw = new StreamWriter(_configfilename))
            {
                var options = new JsonSerializerOptions
                {
                    WriteIndented = true,   // 整形を有効化
                };
                string json = JsonSerializer.Serialize(_appConfig, options);
                sw.Write(json);
            }
        }

        public string pythoninterpreterpath
        {
            set
            {
                this._appConfig.pythoninterpreterpath = value;
                this.save();
            }
            get
            {
                return this._appConfig.pythoninterpreterpath;
            }
        }

        public string pythonscriptpath
        {
            set
            {
                this._appConfig.pythonscriptpath = value;
                this.save();
            }
            get
            {
                return this._appConfig.pythonscriptpath;
            }
        }
    }
}
