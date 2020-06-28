using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MD.UI
{
    /// <summary>
    /// テキストボックスにメモリダンプを表示する
    /// </summary>
    interface IShowDump
    {
        void Show(UInt32 Address, byte[] data);
    }

    class ShowDump8bit : IShowDump
    {
        private TextBox _textbox;

        public ShowDump8bit(TextBox tb)
        {
            this._textbox = tb;
        }

        public void Show(UInt32 Address, byte[] data)
        {
            // 表示クリア
            _textbox.Clear();
            // ヘッダ表示
            _textbox.Text =  "Address    00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\r\n";
            _textbox.Text += "==========================================================\r\n";
            int rows = data.Length / 16;
            var curAddress = Address;
            int offset = 0;
            for(int i = 0; i < rows; i++)
            {
                var rowStr = curAddress.ToString("X08") + "  ";
                for(int n = 0; n < 16; n++ )
                {
                    rowStr += " " + data[offset + n].ToString("X02");
                }
                rowStr += "    ";
                for (int n = 0; n < 16; n++)
                {
                    var ascii = data[offset + n];
                    if (ascii > 0x20 && ascii < 0x7f) rowStr += (char)ascii;
                    else rowStr += ".";
                }

                rowStr += "\r\n";
                curAddress += 16;
                offset += 16;
                _textbox.Text +=  rowStr;
            }
            int remain = data.Length - offset;
            if ( remain > 0)
            {
                var rowStr = curAddress.ToString("X08") + "  ";
                for (int n = 0; n < remain; n++)
                {
                    rowStr += " " + data[offset + n].ToString("X02");
                }
                rowStr += "    ";
                for (int n = 0; n < remain; n++)
                {
                    rowStr += (char)data[offset + n];
                }
                rowStr += "\r\n";
                _textbox.Text += rowStr;
            }
        }
    }

    class ShowDump16bit : IShowDump
    {
        private TextBox _textbox;
        public ShowDump16bit(TextBox tb)
        {
            this._textbox = tb;
        }

        public void Show(UInt32 Address, byte[] data)
        {
            // 表示クリア
            _textbox.Clear();
            // ヘッダ表示
            _textbox.Text = "Address    0000 0002 0004 0006 0008 000A 000C 000E\r\n";
            _textbox.Text += "=================================================\r\n";
            int rows = data.Length / 16;
            var curAddress = Address;
            int offset = 0;
            for (int i = 0; i < rows; i++)
            {
                var rowStr = curAddress.ToString("X08") + "  ";
                for (int n = 0; n < 8; n++)
                {
                    rowStr += " " + BitConverter.ToUInt16(data, offset+(n*sizeof(UInt16))).ToString("X04");
                }
                rowStr += "\r\n";
                curAddress += 16;
                offset += 16;
                _textbox.Text += rowStr;
            }
            int remain = data.Length - offset;
            if (remain > 0)
            {
                var rowStr = curAddress.ToString("X08") + "  ";
                for (int n = 0; n < remain / sizeof(UInt16); n++)
                {
                    rowStr += " " + BitConverter.ToUInt16(data, offset + (n * sizeof(UInt16))).ToString("X04");
                }
                rowStr += "\r\n";
                _textbox.Text += rowStr;
            }
        }


    }

    class ShowDump32bit : IShowDump
    {
        private TextBox _textbox;
        public ShowDump32bit(TextBox tb)
        {
            this._textbox = tb;
        }

        public void Show(UInt32 Address, byte[] data)
        {
            // 表示クリア
            _textbox.Clear();
            // ヘッダ表示
            _textbox.Text = "Address    00000000 00000004 00000008 0000000C\r\n";
            _textbox.Text += "=============================================\r\n";
            int rows = data.Length / 16;
            var curAddress = Address;
            int offset = 0;
            for (int i = 0; i < rows; i++)
            {
                var rowStr = curAddress.ToString("X08") + "  ";
                for (int n = 0; n < 4; n++)
                {
                    rowStr += " " + BitConverter.ToUInt32(data, offset + (n * sizeof(UInt32))).ToString("X08");
                }
                rowStr += "\r\n";
                curAddress += 16;
                offset += 16;
                _textbox.Text += rowStr;
            }
            int remain = data.Length - offset;
            if (remain > 0)
            {
                var rowStr = curAddress.ToString("X08") + "  ";
                for (int n = 0; n < remain / sizeof(UInt32); n++)
                {
                    rowStr += " " + BitConverter.ToUInt32(data, offset + (n * sizeof(UInt32))).ToString("X04");
                }
                rowStr += "\r\n";
                _textbox.Text += rowStr;
            }
        }
    }

    class ShowDump64bit :IShowDump
    {
        private TextBox _textbox;
        public ShowDump64bit(TextBox tb)
        {
            this._textbox = tb;
        }

        public void Show(UInt32 Address, byte[] data)
        {
            // 表示クリア
            _textbox.Clear();
            // ヘッダ表示
            _textbox.Text = "Address    0000000000000000 0000000000000008\r\n";
            _textbox.Text += "=============================================\r\n";
            int rows = data.Length / 16;
            var curAddress = Address;
            int offset = 0;
            for (int i = 0; i < rows; i++)
            {
                var rowStr = curAddress.ToString("X08") + "  ";
                for (int n = 0; n < 2; n++)
                {
                    rowStr += " " + BitConverter.ToUInt64(data, offset + (n * sizeof(UInt64))).ToString("X16");
                }
                rowStr += "\r\n";
                curAddress += 16;
                offset += 16;
                _textbox.Text += rowStr;
            }
            int remain = data.Length - offset;
            if (remain > 0)
            {
                var rowStr = curAddress.ToString("X08") + "  ";
                for (int n = 0; n < remain / sizeof(UInt64); n++)
                {
                    rowStr += " " + BitConverter.ToUInt64(data, offset + (n * sizeof(UInt64))).ToString("X16");
                }
                rowStr += "\r\n";
                _textbox.Text += rowStr;
            }
        }
    }
}
