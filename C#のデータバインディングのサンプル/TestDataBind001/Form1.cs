using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TestDataBind001
{
    public partial class Form1 : Form
    {
        private TestData _testdata;
        private BindingSource bindingSource1;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            _testdata = new TestData();
            _testdata.check = true;
            _testdata.text = "hogehoge";
            bindingSource1 = new BindingSource();
            bindingSource1.DataSource = _testdata;
            // チェックボックスに_testdata.checkをバインドする
            checkBox1.DataBindings.Add("Checked", bindingSource1, "check");
            // テキストボックスに_testdata.textをバインドする
            textBox1.DataBindings.Add("Text", bindingSource1, "text");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // テストデータ書き換え
            _testdata.text = textBox2.Text;
            _testdata.check = false;
            // 書き換えをコントロールに通知する
            bindingSource1.ResetBindings(false);
        }
    }

    class TestData
    {
        private bool _check;
        private string _text;

        public bool check
        {
            get
            {
                return _check;
            }
            set
            {
                _check = value;
                
            }
        }
        public string text
        {
            get
            {
                return _text;
            }
            set
            {
                _text = value;
            }
        }
    }
}
