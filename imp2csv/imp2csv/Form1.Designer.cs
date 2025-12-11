namespace imp2csv
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.show_imp = new Sunny.UI.UIListBox();
            this.export2csv = new Sunny.UI.UIButton();
            this.SuspendLayout();
            // 
            // show_imp
            // 
            this.show_imp.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.show_imp.FillColor = System.Drawing.Color.White;
            this.show_imp.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.show_imp.Location = new System.Drawing.Point(4, 40);
            this.show_imp.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.show_imp.MinimumSize = new System.Drawing.Size(1, 1);
            this.show_imp.Name = "show_imp";
            this.show_imp.Padding = new System.Windows.Forms.Padding(2);
            this.show_imp.ShowText = false;
            this.show_imp.Size = new System.Drawing.Size(1113, 568);
            this.show_imp.TabIndex = 0;
            this.show_imp.Text = "show_imp";
            // 
            // export2csv
            // 
            this.export2csv.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.export2csv.Cursor = System.Windows.Forms.Cursors.Hand;
            this.export2csv.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.export2csv.Location = new System.Drawing.Point(1124, 40);
            this.export2csv.MinimumSize = new System.Drawing.Size(1, 1);
            this.export2csv.Name = "export2csv";
            this.export2csv.Size = new System.Drawing.Size(100, 35);
            this.export2csv.TabIndex = 1;
            this.export2csv.Text = "输出CSV";
            this.export2csv.TipsFont = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.export2csv.Click += new System.EventHandler(this.export2csv_Click);
            // 
            // Form1
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.ClientSize = new System.Drawing.Size(1227, 613);
            this.Controls.Add(this.export2csv);
            this.Controls.Add(this.show_imp);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ZoomScaleRect = new System.Drawing.Rectangle(19, 19, 800, 450);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private Sunny.UI.UIListBox show_imp;
        private Sunny.UI.UIButton export2csv;
    }
}

