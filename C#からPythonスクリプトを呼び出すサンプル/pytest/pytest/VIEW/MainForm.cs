using pytest.CONTROL;
using pytest.MODEL;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace pytest
{
    /// <summary>
    /// メイン画面クラス
    /// </summary>
    public partial class MainForm : Form
    {
        private PyTestSetting _appconfig = null;
        private int _numParameters = 0;
        private int _textoutCount = 0;
        private static readonly log4net.ILog _logger = log4net.LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);

        /// <summary>
        /// 
        /// </summary>
        public MainForm()
        {
            InitializeComponent();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MainForm_Load(object sender, EventArgs e)
        {
            if (_appconfig == null)
            {
                _appconfig = new PyTestSetting();
            }
            textBoxInterpreter.Text = _appconfig.pythoninterpreterpath;
            textBoxScriptPath.Text = _appconfig.pythonscriptpath;
            textBoxNumParams.Text = _numParameters.ToString();
            textBoxStdOut.MaxLength = Constants.TEXT_BOX_MAX_STRS;

            initDataGridView();
        }

        private void textBoxInterpreter_Validated(object sender, EventArgs e)
        {
            if (textBoxInterpreter.Modified)
            {
                _appconfig.pythoninterpreterpath = textBoxInterpreter.Text;
                textBoxInterpreter.Modified = false;
            }

        }

        private void textBoxScriptPath_Validated(object sender, EventArgs e)
        {
            if (textBoxScriptPath.Modified)
            {
                _appconfig.pythonscriptpath = textBoxScriptPath.Text;
                textBoxScriptPath.Modified = false;
            }
        }

        private void textBoxNumParams_Validating(object sender, CancelEventArgs e)
        {
            // テキストボックスに数字以外が入力された場合はその入力を無効にする
            int num;
            bool result = int.TryParse(textBoxNumParams.Text, out num);
            if(result == true)
            {
                _numParameters = num;
            }
            else
            {
                textBoxNumParams.Text = _numParameters.ToString();
                textBoxNumParams.Modified = false;
                e.Cancel = true;
                _logger.Warn("textBoxNumParamsへの入力値が不正です。");
            }
        }

        private void initDataGridView()
        {
            dataGridView1.DataSource = null;
            dataGridView1.ColumnCount = Constants.PARAM_LIST_COLS;
            dataGridView1.Columns[0].HeaderText = Constants.PARAM_LIST_HEADTEXT_NO;
            dataGridView1.Columns[0].Width = 70;
            dataGridView1.Columns[0].ReadOnly = true;
            dataGridView1.Columns[1].HeaderText = Constants.PARAM_LIST_HEADTEXT_NAME;
            dataGridView1.Columns[1].Width = 480;
        }

        private void cleateDataGridView(int nRows )
        {
            dataGridView1.DataSource = null;
            dataGridView1.Rows.Clear();
            for(int i = 0; i<nRows; i++)
            {
                dataGridView1.Rows.Add(i.ToString());
            }
        }

        private void buttonApply_Click(object sender, EventArgs e)
        {
            // パラメータ入力リストテーブルを作成する
            cleateDataGridView(_numParameters);
        }

        private void buttonClearStdOut_Click(object sender, EventArgs e)
        {
            textBoxStdOut.Clear();
            _textoutCount = 0;
        }

        private void buttonExec_Click(object sender, EventArgs e)
        {
            Stopwatch sw = new Stopwatch();

            textout(textBoxScriptName.Text + "を実行します");
            sw.Start();
            // pythonスクリプトの呼び出し処理を以下に実装する
            PyCall python = new PyCall(_appconfig);
            // 引数取得
            var args = new List<string>();
            for(int idx = 0; idx < dataGridView1.RowCount; idx++)
            {
                args.Add(dataGridView1[1, idx].Value.ToString());
            }

            var resultJson = python.call(textBoxScriptName.Text, args);
            sw.Stop();

            // 結果出力
            PyCallResult result = JsonSerializer.Deserialize<PyCallResult>(resultJson);
            textout("実行結果 :" + result.Status.ToString());
            textout("終了コード : " + result.ExitCode.ToString());
            textout("メッセージ :" + result.Msg);
            textout("標準出力:\r\n" + result.StdOut);
            textout("エラー出力:\r\n" + result.ErrOut);
            

            textBoxElapsed.Text = sw.ElapsedMilliseconds.ToString();
        }

        private void textout(string text)
        {
            string t = _textoutCount.ToString() + " : " + text + "\r\n";
            if ( textBoxStdOut.MaxLength < (textBoxStdOut.TextLength + t.Length))
            {
                textBoxStdOut.Clear();
            }
            textBoxStdOut.Text += t;
            textBoxStdOut.SelectionStart = textBoxStdOut.TextLength;
            textBoxStdOut.ScrollToCaret();
            _textoutCount += 1;
        }
    }

    /// <summary>
    /// 定数
    /// </summary>
    public class Constants
    {
        public const int PARAM_LIST_COLS = 2;
        public const string PARAM_LIST_HEADTEXT_NO = "No.";
        public const string PARAM_LIST_HEADTEXT_NAME = "Parameter";
        public const int TEXT_BOX_MAX_STRS = 16777216;

    }


}
