using pytest.CONTROL;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.IO;

namespace pytest.MODEL
{
    class PyCall
    {
        private static readonly log4net.ILog _logger = log4net.LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);
        private PyTestSetting _setting;

        public PyCall(PyTestSetting setting)
        {
            _setting = new PyTestSetting();
            _setting = setting;
        }

        public string call(string PyScriptFile, IReadOnlyCollection<string> ScriptArgments)
        {
            // Pythonインタープリタの存在確認
            if (!File.Exists(_setting.pythoninterpreterpath))
            {
                return getResultErrorString(PyCallStatus.NO_EXIST_INTERPRETER, "no exist python interpreter execution file.");
            }

            // スクリプト格納ディレクトリの存在確認
            if (!Directory.Exists(_setting.pythonscriptpath))
            {
                return getResultErrorString(PyCallStatus.NO_EXIST_INTERPRETER, "no exist directory " + _setting.pythonscriptpath);
            }
            // スクリプトファイルの存在確認
            var scriptFullPath = Path.Combine(_setting.pythonscriptpath, PyScriptFile);
            if (!File.Exists(scriptFullPath))
            {
                return getResultErrorString(PyCallStatus.NO_EXIST_SCRIPT, "no exist file " + PyScriptFile);
            }

            // Pythonスクリプト呼び出し処理
            var processArgs = new List<string>
            {
                PyScriptFile
            };
            processArgs.AddRange(ScriptArgments);

            var process = new Process()
            {
                StartInfo = new ProcessStartInfo(_setting.pythoninterpreterpath)
                {
                    UseShellExecute = false,
                    RedirectStandardOutput = true,
                    RedirectStandardError = true,
                    Arguments = string.Join(" ", processArgs),
                    WorkingDirectory = _setting.pythonscriptpath,
                    CreateNoWindow = true
                },
            };

            process.Start();

            var sr = process.StandardOutput;
            var er = process.StandardError;
            var srResult = sr.ReadToEnd();
            var erResult = er.ReadToEnd();

            // プロセス終了待ち
            process.WaitForExit();
            var ExitCode = process.ExitCode;
            process.Close();

            // 結果格納
            return getResultString(ExitCode, srResult, erResult);
        }

        private string getResultErrorString(PyCallStatus status, string msg)
        {
            _logger.Error(msg);
            PyCallResult result = new PyCallResult();
            result.Status = status;
            result.Msg = msg;
            string json = JsonSerializer.Serialize(result);
            return json;
        }

        private string getResultString(int ExitCode, string stdOut, string stdErr )
        {
            PyCallResult result = new PyCallResult();
            result.Status = PyCallStatus.RESULT_OK;
            result.Msg = "OK";
            result.ExitCode = ExitCode;
            result.StdOut = stdOut;
            result.ErrOut = stdErr;
            string json = JsonSerializer.Serialize(result);
            return json;
        }

    }

    public enum PyCallStatus
    {
        RESULT_OK = 0,                  // プロセスの呼び出しに成功した
        NO_EXIST_WORKDIRECTORY = -9997, // プロセス実行用のワークディレクトリがない
        NO_EXIST_SCRIPT = -9998,        // 指定されたスクリプトファイルがない
        NO_EXIST_INTERPRETER = -9999    // 指定されたインタープリタがない
    }

    public class PyCallResult
    {
        public PyCallStatus Status { get; set; }        // ステータス
        public string Msg { get; set; }                 // メッセージ
        public int ExitCode { get; set; }               // プロセスの戻り値
        public string StdOut { get; set; }              // プロセスの標準出力
        public string ErrOut { get; set; }              // プロセスのエラー出力
    }
}
