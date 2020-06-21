namespace pytest
{
    partial class MainForm
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージド リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.textBoxInterpreter = new System.Windows.Forms.TextBox();
            this.textBoxScriptPath = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textBoxScriptName = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.buttonExec = new System.Windows.Forms.Button();
            this.textBoxNumParams = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.buttonApply = new System.Windows.Forms.Button();
            this.textBoxStdOut = new System.Windows.Forms.TextBox();
            this.buttonClearStdOut = new System.Windows.Forms.Button();
            this.textBoxElapsed = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // textBoxInterpreter
            // 
            this.textBoxInterpreter.Location = new System.Drawing.Point(96, 27);
            this.textBoxInterpreter.Name = "textBoxInterpreter";
            this.textBoxInterpreter.Size = new System.Drawing.Size(648, 19);
            this.textBoxInterpreter.TabIndex = 0;
            this.textBoxInterpreter.Validated += new System.EventHandler(this.textBoxInterpreter_Validated);
            // 
            // textBoxScriptPath
            // 
            this.textBoxScriptPath.Location = new System.Drawing.Point(96, 53);
            this.textBoxScriptPath.Name = "textBoxScriptPath";
            this.textBoxScriptPath.Size = new System.Drawing.Size(648, 19);
            this.textBoxScriptPath.TabIndex = 1;
            this.textBoxScriptPath.Validated += new System.EventHandler(this.textBoxScriptPath_Validated);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(25, 30);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "インタープリタ";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 56);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(81, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "スクリプトフォルダ";
            // 
            // textBoxScriptName
            // 
            this.textBoxScriptName.Location = new System.Drawing.Point(96, 79);
            this.textBoxScriptName.Name = "textBoxScriptName";
            this.textBoxScriptName.Size = new System.Drawing.Size(648, 19);
            this.textBoxScriptName.TabIndex = 4;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(32, 85);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(58, 12);
            this.label3.TabIndex = 5;
            this.label3.Text = "スクリプト名";
            // 
            // buttonExec
            // 
            this.buttonExec.Location = new System.Drawing.Point(283, 103);
            this.buttonExec.Name = "buttonExec";
            this.buttonExec.Size = new System.Drawing.Size(94, 23);
            this.buttonExec.TabIndex = 6;
            this.buttonExec.Text = "スクリプト実行";
            this.buttonExec.UseVisualStyleBackColor = true;
            this.buttonExec.Click += new System.EventHandler(this.buttonExec_Click);
            // 
            // textBoxNumParams
            // 
            this.textBoxNumParams.Location = new System.Drawing.Point(96, 105);
            this.textBoxNumParams.Name = "textBoxNumParams";
            this.textBoxNumParams.Size = new System.Drawing.Size(100, 19);
            this.textBoxNumParams.TabIndex = 7;
            this.textBoxNumParams.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxNumParams_Validating);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(29, 111);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(61, 12);
            this.label4.TabIndex = 8;
            this.label4.Text = "パラメータ数";
            // 
            // dataGridView1
            // 
            this.dataGridView1.AllowUserToAddRows = false;
            this.dataGridView1.AllowUserToDeleteRows = false;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(96, 131);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowTemplate.Height = 21;
            this.dataGridView1.Size = new System.Drawing.Size(640, 150);
            this.dataGridView1.TabIndex = 9;
            // 
            // buttonApply
            // 
            this.buttonApply.Location = new System.Drawing.Point(202, 103);
            this.buttonApply.Name = "buttonApply";
            this.buttonApply.Size = new System.Drawing.Size(75, 23);
            this.buttonApply.TabIndex = 10;
            this.buttonApply.Text = "apply";
            this.buttonApply.UseVisualStyleBackColor = true;
            this.buttonApply.Click += new System.EventHandler(this.buttonApply_Click);
            // 
            // textBoxStdOut
            // 
            this.textBoxStdOut.Location = new System.Drawing.Point(12, 314);
            this.textBoxStdOut.Multiline = true;
            this.textBoxStdOut.Name = "textBoxStdOut";
            this.textBoxStdOut.ReadOnly = true;
            this.textBoxStdOut.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBoxStdOut.Size = new System.Drawing.Size(747, 296);
            this.textBoxStdOut.TabIndex = 11;
            // 
            // buttonClearStdOut
            // 
            this.buttonClearStdOut.Location = new System.Drawing.Point(684, 287);
            this.buttonClearStdOut.Name = "buttonClearStdOut";
            this.buttonClearStdOut.Size = new System.Drawing.Size(75, 23);
            this.buttonClearStdOut.TabIndex = 12;
            this.buttonClearStdOut.Text = "Clear";
            this.buttonClearStdOut.UseVisualStyleBackColor = true;
            this.buttonClearStdOut.Click += new System.EventHandler(this.buttonClearStdOut_Click);
            // 
            // textBoxElapsed
            // 
            this.textBoxElapsed.Location = new System.Drawing.Point(442, 103);
            this.textBoxElapsed.Name = "textBoxElapsed";
            this.textBoxElapsed.ReadOnly = true;
            this.textBoxElapsed.Size = new System.Drawing.Size(134, 19);
            this.textBoxElapsed.TabIndex = 13;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(383, 108);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(53, 12);
            this.label5.TabIndex = 14;
            this.label5.Text = "処理時間";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(771, 622);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.textBoxElapsed);
            this.Controls.Add(this.buttonClearStdOut);
            this.Controls.Add(this.textBoxStdOut);
            this.Controls.Add(this.buttonApply);
            this.Controls.Add(this.dataGridView1);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.textBoxNumParams);
            this.Controls.Add(this.buttonExec);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.textBoxScriptName);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBoxScriptPath);
            this.Controls.Add(this.textBoxInterpreter);
            this.Name = "MainForm";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.MainForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBoxInterpreter;
        private System.Windows.Forms.TextBox textBoxScriptPath;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBoxScriptName;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button buttonExec;
        private System.Windows.Forms.TextBox textBoxNumParams;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.Button buttonApply;
        private System.Windows.Forms.TextBox textBoxStdOut;
        private System.Windows.Forms.Button buttonClearStdOut;
        private System.Windows.Forms.TextBox textBoxElapsed;
        private System.Windows.Forms.Label label5;
    }
}

