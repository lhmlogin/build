using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Sunny.UI;
//using InPlanLib;
using InFlowLib;
using System.Configuration;
using System.IO;

namespace imp2csv
{
    public partial class Form1 : UIForm
    {
        private IApplicationManager app;
        private IJobManager jobManager;
        private IJob my_job;
        private string job_name;
        private string savePath = ConfigurationManager.AppSettings["savePath"];
        public Form1()
        {
            InitializeComponent();
        }

        private void initInFlow()
        {
            // 获取所有命令行参数
            string[] commandLineArgs = Environment.GetCommandLineArgs();
            if (commandLineArgs.Length <= 1)
            {
                UIMessageBox.ShowError("缺少job_name参数，请补充", false, true);
                System.Environment.Exit(0);
            }
            job_name = commandLineArgs[1];
            app = new ApplicationManager();
            jobManager = app.JobManager();
            if (app.ErrorMessage() == "OK")
            {
                my_job = jobManager.OpenJob(job_name);
                if (jobManager.ErrorMessage()!="OK")
                {
                    UIMessageBox.ShowError("打开Job失败", false, true);
                    System.Environment.Exit(0);
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            initInFlow();
        }

        private void export2csv_Click(object sender, EventArgs e)
        {
            string saveP = savePath + "/" + job_name + ".csv";
            List<string> writeList = new List<string>();
            IStackup stackup = my_job.Stackup();
            try
            {
                if (stackup != null)
                {
                    List<IImpedanceConstraint> impedanceConstraints = stackup.ImpedanceConstraints().Cast<IImpedanceConstraint>().ToList();
                    foreach (IImpedanceConstraint imp_item in impedanceConstraints)
                    {
                        ICopperLayer topLayer = imp_item.TopModelLayer();
                        ICopperLayer botLayer = imp_item.BottomModelLayer();
                        ICopperLayer traceLayer = imp_item.ControlledTraceLayer();

                        string topLayerName = topLayer == null ? "\\" : topLayer.OdbLayerName();
                        string botLayerName = botLayer == null ? "\\" : botLayer.OdbLayerName();
                        string traceLayerName = traceLayer == null ? "\\" : traceLayer.OdbLayerName();

                        string lineWidth = imp_item.OriginalTraceWidth(AvailableUnits.MIL).ToString("F3");
                        string impedanceValue = imp_item.CalculationRequiredImpedance(AvailableUnits.OHMS).ToString("F0");
                        string modeName = "";
                        string curModeName = imp_item.ModelName().ToLower();
                        if (curModeName.StartsWith("se"))
                        {
                            modeName = "single-ended";
                            getLine(ref writeList, true, modeName, traceLayerName, topLayerName, botLayerName, lineWidth, "\\","\\", impedanceValue);
                        }
                        else if (curModeName.StartsWith("broadside"))
                        {
                            modeName = "differential";
                            string diffSpacing = imp_item.CustomerRequiredDifferentialSpacing(AvailableUnits.MIL).ToString("F3");
                            getLine(ref writeList, true, modeName, traceLayerName, topLayerName, botLayerName, lineWidth, diffSpacing, "\\", impedanceValue);
                        }
                        else if (curModeName.StartsWith("coplanar_se"))
                        {
                            modeName = "single-ended coplanar";
                            string coplanarSpacing = imp_item.CustomerRequiredCoplanarSpacing(AvailableUnits.MIL).ToString("F3");
                            getLine(ref writeList, true, modeName, traceLayerName, topLayerName, botLayerName, lineWidth, "\\",coplanarSpacing, impedanceValue);
                        }
                        else if (curModeName.StartsWith("diff"))
                        {
                            modeName = "differential";
                            string diffSpacing = imp_item.CustomerRequiredDifferentialSpacing(AvailableUnits.MIL).ToString("F3");
                            getLine(ref writeList, true, modeName, traceLayerName, topLayerName, botLayerName, lineWidth, diffSpacing,"\\", impedanceValue);
                        }
                        else if (curModeName.StartsWith("coplanar_diff"))
                        {
                            modeName = "differential coplanar";
                            string diffSpacing = imp_item.CustomerRequiredDifferentialSpacing(AvailableUnits.MIL).ToString("F3");
                            string coplanarSpacing = imp_item.CustomerRequiredCoplanarSpacing(AvailableUnits.MIL).ToString("F3");
                            getLine(ref writeList, true, modeName, traceLayerName, topLayerName, botLayerName, lineWidth, diffSpacing,coplanarSpacing, impedanceValue);
                        }
                        else
                        {
                            modeName = "differential";
                            string diffSpacing = imp_item.CustomerRequiredDifferentialSpacing(AvailableUnits.MIL).ToString("F3");
                            getLine(ref writeList, true, curModeName, traceLayerName, topLayerName, botLayerName, lineWidth, diffSpacing, "\\", impedanceValue);
                        }

                        using (StreamWriter writer = new StreamWriter(saveP))
                        {
                            foreach (string item in writeList)
                            {
                                writer.WriteLine(item);
                            }
                        }
                    }
                    show_imp.Items.Add("------------输出成功, 路径=》  " + saveP + "  ------------------------");
                }
                else
                {
                    UIMessageBox.ShowError(my_job.ErrorMessage());
                }
            }
            catch (Exception ex)
            {
                UIMessageBox.ShowError("输出失败 =>  " + ex.Message);


            }

        }

        private string setLayerName(string topLayerName)
        {
            topLayerName = topLayerName.ToLower();
            topLayerName = topLayerName.Replace("l", "");
            topLayerName = int.Parse(topLayerName) < 10 ? "l0" + topLayerName : "l"+topLayerName;
            return topLayerName;
        }

        private void getLine(ref List<string> writeList, bool v1, string modeName, string traceLayer, string topLayer, string botLayer, string lineWidth, string diffSpacing, string coplanarSpacing, string impedanceValue)
        {
            string line = modeName + "," + traceLayer + "," + topLayer + "," + botLayer + "," + lineWidth + "," + lineWidth + "," + diffSpacing + "," + diffSpacing + ","+coplanarSpacing+","+ impedanceValue;
            writeList.Add(line);
            if (v1)
            {
                show_imp.Items.Add(modeName + " => 阻抗层： " + traceLayer + "  上参考层: " + topLayer + "  下参考层: " + botLayer + "  线宽: " + lineWidth + "  线距: " + diffSpacing + "  共面距离: " + coplanarSpacing + "  欧姆: " + impedanceValue);
            } else
            {
                show_imp.Items.Add("特别注意： =》 " + modeName + " => 阻抗层： " + traceLayer + "  上参考层: " + topLayer + "  下参考层: " + botLayer + "  线宽: " + lineWidth + "  线距: " + diffSpacing + "  欧姆: " + impedanceValue);
            }
        }
    }
}
