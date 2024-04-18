#!/usr/bin/python3
# -*- coding: utf-8 -*-

import os,re,sys,json
import time
import incam
import platform

from reportlab.lib import colors
from reportlab.lib.pagesizes import A4
from reportlab.lib.units import inch
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.pdfgen.canvas import Canvas
from reportlab.lib.styles import ParagraphStyle
from reportlab.platypus import Spacer, SimpleDocTemplate, Table, Paragraph, Image
from pypdf import PdfMerger

from PyQt5 import QtCore, QtGui, QtWidgets,uic
from PyQt5.QtGui import QStandardItem
from PyQt5.QtWidgets import QHeaderView,QAbstractItemView,QFileDialog,QMessageBox,QMenu,QComboBox


# reload(sys)
# sys.setdefaultencoding('utf8')


# dueTime=1693497540
# 注册字体
msyh = "msyh"
msyhbd = "msyhbd"
pdfmetrics.registerFont(TTFont(msyh, "msyh.ttc"))
pdfmetrics.registerFont(TTFont(msyhbd, "msyhbd.ttc"))

PAGE_HEIGHT = A4[1]
PAGE_WIDTH = A4[0]

# 设置段落格式bigunits

titleName="KLA板内阻抗量测"
titleStyle = ParagraphStyle(
    name="titleStyle",
    alignment=1,
    fontName=msyhbd,
    fontSize=20,
    textColor=colors.black,
    # backColor=HexColor(0xF2EEE9),
    borderPadding=(5, 5)
)



# try:
#     _fromUtf8 = QtCore.QString.fromUtf8
# except AttributeError:
#     def _fromUtf8(s):
#         return s

# try:
#     _encoding = QtGui.QApplication.UnicodeUTF8
#     def _translate(context, text, disambig):
#         return QtGui.QApplication.translate(context, text, disambig, _encoding)
# except AttributeError:
#     def _translate(context, text, disambig):
#         return QtGui.QApplication.translate(context, text, disambig)

if getattr(sys,'frozen',False):
    scriptDir=os.path.dirname(sys.executable)
else:
    scriptDir=os.path.dirname(os.path.abspath(__file__))

# qtCreatorFile = scriptDir+"/main.ui"
# Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile)

# paramUIFile = scriptDir+"/param.ui"
# Ui_MainWindow_Param, QtBaseClass = uic.loadUiType(paramUIFile)

units="mil"
bigunits="inch"


f=incam.InCAM()
jobName=os.environ['JOB']
stepName=os.environ['STEP']
f.COM("get_job_path,job="+jobName)
# outputLogFile = f.COMANS+"/user/data_output.log"
# outputParamsFile = f.COMANS+"/user/output_params.txt"
userDir=f.COMANS+"/user"
f.COM("get_user_name")
userName = f.COMANS
pid = str(os.getpid())

jsonFilePath=scriptDir+"/param.json"
paramDict={}

os_type=platform.system()

failreason=[u"有外层测点",u"不满足最小pad大小",u"线经过孔pad",u"不满足最小覆盖率",u"不满足最小长度",u"不满足最小长度和覆盖率",u"没有识别到阻抗线"]

def saveJsonFile(ips):
    with open(jsonFilePath, 'w') as f:
        json.dump(ips, f, indent=4)

def loadJsonFile(jsonFilePath):
    #must define globla valuey, or it will be empty in class MyApp
    global paramDict
    if os.path.exists(jsonFilePath):
        jsonFile = open(jsonFilePath, 'r')
        paramDict = json.load(jsonFile)
        jsonFile.close()

unitValueList=["diff_min_len","trace_width_tol","spacing_tol","tp_imp_min_len","tp_min_width","tp_max_width","tp_pgpad_max_dist","ila_min_cu_dist","ila_min_cu_dist","ila_min_drill_dist","ila_spacing_search_dist"]

if os.path.exists(jsonFilePath):
    loadJsonFile(jsonFilePath)


    if paramDict['units']=="mm":
        units="um"
        bigunits="mm"
        for el in unitValueList:
            paramDict[el]=str(round(float(paramDict[el])/25.4,3))

    if paramDict['units']=="inch":
        units="mil"
        bigunits="inch"




class MyApp(QtWidgets.QMainWindow):
    global paramDict
    # global dueTime
    global units,bigunits
    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        self.setupUi(self)

# class MyApp(QtWidgets.QMainWindow, Ui_MainWindow):
#     global paramDict
#     global dueTime
#     def __init__(self):
#         # QtGui.QMainWindow.__init__(self)
#         # Ui_MainWindow.__init__(self)
#         # self.setupUi(self)
#         QtWidgets.QMainWindow.__init__(self)
#         Ui_MainWindow.__init__(self)
#         self.setupUi(self)

        # curTime=time.time()
        # if curTime>dueTime:
        #     QMessageBox.information(self,u"info",u"License is expired, please contact KLA",QMessageBox.Ok)
        #     exit(0)
        


        self.impList=[]
        self.rawImpList=[]
        self.keyNameList=['type','lyr','top_ref','bot_ref','line_width','req_line_width','spacing','req_spacing','imp_value']
        self.tmpDir="/tmp/imp_tp."+pid
        if not os.path.exists(self.tmpDir):
            os.mkdir(self.tmpDir)
        self.tmpDir=self.tmpDir+"/"
        paramDict['rep_filename']=jobName
        self.theOnepdfName=paramDict['rep_path']+"/"+paramDict['rep_filename']+".pdf"
        self.runILRFlag=0

        # f.COM("affected_filter,filter=(type=signal|power_ground|mixed&context=board)") //can't get correct order
        self.boardLyrList=[""]
        info=f.DO_INFO("-t matrix -e %s/matrix -d ROW -p context+layer_base_type+name"%(jobName))
        for i in range(len(info['gROWcontext'])):
            if info['gROWcontext'][i]=='board' and (info['gROWlayer_base_type'][i] == 'signal' or info['gROWlayer_base_type'][i] == 'power_ground' or info['gROWlayer_base_type'][i] == 'mixed'):
                self.boardLyrList.append(info['gROWname'][i])
        self.boardLyrList.append("")

        self.pushButton_selectImpListFile.clicked.connect(self.pushButton_selectImpListFile_clicked)
        self.pushButton_pause.clicked.connect(self.pause)
        self.pushButton_param.clicked.connect(self.openParamWindow)
        self.pushButton_exit.clicked.connect(self.exit)
        self.pushButton_saveAsImpList.clicked.connect(self.pushButton_saveAsImpList_clicked)
        self.pushButton_saveImpList.clicked.connect(self.pushButton_saveImpList_clicked)

        self.realModel = QtGui.QStandardItemModel()
        # ['type','lyr','top_ref','bot_ref','line_width','req_line_width','spacing','req_spacing','imp_value']
        # self.realModel.setHorizontalHeaderLabels(["Type","Layer",u"top ref layer",'bot ref layer',u"line width",u"required line width",u"spacing",u"required spacing",u"coplanar Dist",u"imp Value"])
        self.realModel.setHorizontalHeaderLabels([u"类型",u"层",u"顶层参考层",u"底层参考层",u"线宽("+units+")",u"目标线宽("+units+")",u"间距("+units+")",u"目标间距("+units+")",u"阻值(Ω)"])

        self.tableView_ImpList.setModel(self.realModel)
        self.tableView_ImpList.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeToContents) #设置完全填充列表组件
        self.tableView_ImpList.horizontalHeader().setDefaultAlignment(QtCore.Qt.AlignLeft)
        # # self.tableWidget.setEditTriggers(QAbstractItemView.AllEditTriggers)
        self.tableView_ImpList.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.tableView_ImpList.setSelectionMode(QAbstractItemView.SingleSelection)
        self.tableView_ImpList.setContextMenuPolicy(QtCore.Qt.CustomContextMenu)
        self.tableView_ImpList.customContextMenuRequested.connect(self.tableViewRightMenu)

        self.pushButton_ILR.clicked.connect(self.runILR)
        self.pushButton_ILA.clicked.connect(self.runILA)
        self.pushButton_createMiscLyr.clicked.connect(self.createImpMiscLyr)
        self.pushButton_createTPReport.clicked.connect(self.createTP)
        self.pushButton_addImp.clicked.connect(self.pushButton_addImp_clicked)
        self.pushButton_ILA.hide()
        self.pushButton_createTP.hide()

        # debug setting
        # param="/home/incam/Documents/ilr/source_code.hdi/imp_lines-hdi.csv"
        # self.lineEdit_ImpListFilePath.setText(param)
        # self.load_impList(param)




    def createImpList(self):
        self.impList=[]
        row=self.realModel.rowCount()
        col=self.realModel.columnCount()
        # if row!=len(self.impList):
        #     self.impList=[]
        # else:
        #     return
        for i in range(row):
            tmpImpDict={}
            tmpImpDict['id']=i+1
            for j in range(col):
                try:
                    value=str(self.realModel.item(i,j).text())
                except:
                    value=str(self.tableView_ImpList.indexWidget(self.realModel.index(i,j)).currentText())
                if value == "":
                    if j <4 :
                        value=""
                    else:
                        value='0'
                tmpImpDict[self.keyNameList[j]]=value
            if tmpImpDict['req_line_width']=='0':
                tmpImpDict['req_line_width']=tmpImpDict['line_width']
            
            # if tmpImpDict['type'] == 'differential':
            #     tmpImpDict['shotrtype']="diff"
            # if tmpImpDict['type'] == 'single-ended':
            #     tmpImpDict['shotrtype']="sing"

            if tmpImpDict['req_spacing']=='0' and tmpImpDict['type'] == 'differential':
                tmpImpDict['req_spacing']=str(float(tmpImpDict['spacing'])-(float(tmpImpDict['req_line_width'])-float(tmpImpDict['line_width'])))
                # print(str(i)+str(j)+txt)
                # pass
            # ['type','lyr','top_ref','bot_ref','line_width','req_line_width','spacing','req_spacing','cop_dist','imp_value']
            if units=="um":
                tmpImpDict['line_width_mil']=str(round(float(tmpImpDict['line_width'])/25.4,2))
                tmpImpDict['req_line_width_mil']=str(round(float(tmpImpDict['req_line_width'])/25.4,2))
                tmpImpDict['spacing_mil']=str(round(float(tmpImpDict['spacing'])/25.4,2))
                tmpImpDict['req_spacing_mil']=str(round(float(tmpImpDict['req_spacing'])/25.4,2))

                tmpImpDict['line_width_print']=tmpImpDict['line_width']
                tmpImpDict['req_line_width_print']=tmpImpDict['req_line_width']
                tmpImpDict['spacing_print']=tmpImpDict['spacing']
                tmpImpDict['req_spacing_print']=tmpImpDict['req_spacing']
            else:
                tmpImpDict['line_width_mil']=tmpImpDict['line_width']
                tmpImpDict['req_line_width_mil']=tmpImpDict['req_line_width']
                tmpImpDict['spacing_mil']=tmpImpDict['spacing']
                tmpImpDict['req_spacing_mil']=tmpImpDict['req_spacing']

                tmpImpDict['line_width_print']=tmpImpDict['line_width']
                tmpImpDict['req_line_width_print']=tmpImpDict['req_line_width']
                tmpImpDict['spacing_print']=tmpImpDict['spacing']
                tmpImpDict['req_spacing_print']=tmpImpDict['req_spacing']
            # tmpImpDict['cop_dist_mil']=tmpImpDict['cop_dist']

            tmpImpDict['line_width']=float(tmpImpDict['line_width_mil'])/1000
            tmpImpDict['req_line_width']=float(tmpImpDict['req_line_width_mil'])/1000
            tmpImpDict['spacing']=float(tmpImpDict['spacing_mil'])/1000
            tmpImpDict['req_spacing']=float(tmpImpDict['req_spacing_mil'])/1000
            self.impList.append(tmpImpDict)

    def importImpList(self):
        # if len(self.impList) == 0:
        self.createImpList()
        # print(self.impList)
        for i in range(1,100):
            f.VOF()
            f.COM("imp_cnsts_del,imp_id=%s,refresh_table=no"%(i))
            curStatus=f.STATUS
            f.VON()
            if curStatus != 0:
                break
        # f.COM("imp_refresh_tbl,refresh_table=yes")

        f.COM("chklist_single,action=frontline_imp_rec_simp,show=no")
        f.COM("units,type=inch")
        f.COM("chklist_cupd,chklist=frontline_imp_rec_simp,nact=1,params=((pp_min_length=0)(pp_min_length_short=0)(pp_diff_length=%s)(pp_diff_poly_length_max=0)(pp_diff_percent=%s)(pp_diff_percent_short=%s)(pp_min_cover=50)(pp_min_coplanar_percent=0)(pp_width_tol=%s)(pp_diff_spacing=%s)(pp_exist_mode=Clear)(pp_reset_lw=)),mode=regular"%(paramDict['diff_min_len'],paramDict['min_diff_percent'],paramDict['min_diff_percent'],paramDict['trace_width_tol'],paramDict['spacing_tol']))
        f.COM("chklist_cnf_act,chklist=frontline_imp_rec_simp,nact=1,cnf=no")
        f.COM("chklist_run,chklist=frontline_imp_rec_simp,nact=1")

        for imp in self.impList:
            f.COM("imp_cnsts_add,test_layer=%s,model=%s,top_ref_layer=%s,bot_ref_layer=%s,orig_lw=%s,req_lw=%s,orig_spacing=%s,refresh_table=yes,ilr_dfm_use=yes"%(imp['lyr'],imp['type'],imp['top_ref'],imp['bot_ref'],imp['line_width'],imp['req_line_width'],imp['spacing']))
            f.COM("imp_cnsts_change,imp_id=%s,imp_val=%s"%(imp['id'],imp['imp_value']))
            if imp['type'] == "differential":
                f.COM("imp_cnsts_change,imp_id=%s,req_spacing=%s"%(imp['id'],imp['req_spacing']))


    def runILR(self):
        self.importImpList()
        self.runILRFlag=1
        info=f.DO_INFO("-t check -e %s/%s/frontline_imp_rec_simp -d EXISTS"%(jobName,stepName))
        if info['gEXISTS'] == "yes":
            f.COM("chklist_delete,chklist=frontline_imp_rec_simp")

        
        f.COM("chklist_single,action=frontline_imp_rec_simp,show=no")

        f.COM("units,type=inch")
        f.COM("chklist_cupd,chklist=frontline_imp_rec_simp,nact=1,params=((pp_min_length=0)(pp_min_length_short=0)(pp_diff_length=%s)(pp_diff_poly_length_max=0)(pp_diff_percent=%s)(pp_diff_percent_short=%s)(pp_min_cover=50)(pp_min_coplanar_percent=0)(pp_width_tol=%s)(pp_diff_spacing=%s)(pp_exist_mode=Clear)(pp_reset_lw=)),mode=regular"%(paramDict['diff_min_len'],paramDict['min_diff_percent'],paramDict['min_diff_percent'],paramDict['trace_width_tol'],paramDict['spacing_tol']))
        f.COM("chklist_cnf_act,chklist=frontline_imp_rec_simp,nact=1,cnf=no")
        # f.COM("chklist_run_act,chklist=frontline_imp_rec_simp,nact=1")
        f.COM("chklist_run,chklist=frontline_imp_rec_simp,nact=1")
        f.COM("units,type=inch")
        # COM chklist_run,chklist=frontline_imp_rec_simp,nact=1

        for imp in self.impList:
            f.COM("clear_layers")
            f.COM("affected_layer,name=,mode=all,affected=no")
            f.COM("display_layer,name=%s,display=yes"%(imp['lyr']))
            f.COM("work_layer,name=%s"%(imp['lyr']))
            f.COM("reset_filter_criteria,filter_name=,criteria=all")
            f.COM("set_filter_type,filter_name=,lines=yes,pads=no,surfaces=no,arcs=yes,text=no")
            f.COM("set_filter_attributes,filter_name=popup,exclude_attributes=no,condition=yes,attribute=.imp_constraint_id,min_int_val=%s,max_int_val=%s,min_float_val=0,max_float_val=0,option=,text="%(imp['id'],imp['id']))
            f.COM("set_filter_and_or_logic,filter_name=popup,criteria=inc_attr,logic=and")
            f.COM("adv_filter_reset")
            f.COM("filter_area_strt")
            f.COM("filter_area_end,filter_name=popup,operation=select")
            f.COM("get_select_count")
            selectCount=int(f.COMANS)
            if selectCount != 0:
                # ['type','lyr','top_ref','bot_ref','line_width','req_line_width','spacing','req_spacing','cop_dist','imp_value']
                if imp['type'] == 'differential':
                    # impLayerName="_imp-%s-%sou-diff-%s-%s".format(imp['lyr'],imp['imp_value'],float(imp['line_width'])*1000,float(imp['spacing'])*1000))
                    impLayerName=str(imp['id'])+"_imp-"+imp['lyr']+"-"+imp['imp_value']+"ohm-diff-"+imp['line_width_print']+"-"+imp['spacing_print']
                    info=f.DO_INFO("-t layer -e %s/%s/%s -d EXISTS"%(jobName,stepName,impLayerName))
                    if info['gEXISTS'] == "yes":
                        f.COM("delete_layer, layer=%s"%(impLayerName))
                    f.COM("sel_copy_other,dest=layer_name,target_layer=%s,invert=no,dx=0,dy=0,size=0,x_anchor=0,y_anchor=0"%(impLayerName))
                elif imp['type'] == 'single-ended':
                    # impLayerName="_imp-%s-%sou-diff-%s-%s"%(imp['lyr'],imp['imp_value'],float(imp['line_width'])*1000)
                    impLayerName=str(imp['id'])+"_imp-"+imp['lyr']+"-"+imp['imp_value']+"ohm-sing-"+imp['line_width_print']
                    info=f.DO_INFO("-t layer -e %s/%s/%s -d EXISTS"%(jobName,stepName,impLayerName))
                    if info['gEXISTS'] == "yes":
                        f.COM("delete_layer, layer=%s"%(impLayerName))
                    f.COM("sel_copy_other,dest=layer_name,target_layer=%s,invert=no,dx=0,dy=0,size=0,x_anchor=0,y_anchor=0"%(impLayerName))

        self.pause()

    def runImpIndexing_old(self):
        if self.runILRFlag == 0:
            self.importImpList()

        for imp in self.impList:
            if imp['type'] == 'differential':
                impLayerName=str(imp['id'])+"_imp-"+imp['lyr']+"-"+imp['imp_value']+"ohm-diff-"+imp['line_width_print']+"-"+imp['spacing_print']
            elif imp['type'] == 'single-ended':
                impLayerName=str(imp['id'])+"_imp-"+imp['lyr']+"-"+imp['imp_value']+"ohm-sing-"+imp['line_width_print']
            f.COM("units,type=inch")
            info = f.DO_INFO('-t layer -e %s/%s/%s -d EXISTS'%(jobName,stepName,impLayerName))
            if info['gEXISTS'] == "yes":
                f.COM("chklist_single,show=no,action=frontline_impline_indexing")
                f.COM("chklist_cupd,chklist=frontline_impline_indexing,nact=1,params=((pp_ref_layer=%s)(pp_copper_layer=%s)(pp_imp_id=%s)(pp_type=%s)(pp_spacing=%s)(pp_spacing_tol=%s)),mode=regular"%(impLayerName,imp['lyr'],imp['id'],imp['type'],imp['spacing_mil'],paramDict['spacing_tol']))
                f.COM("chklist_run,chklist=frontline_impline_indexing,nact=1")

    def runImpIndexing(self):
        if self.runILRFlag == 0:
            self.importImpList()
        check_layer=1
        f.COM("chklist_single,show=no,action=frontline_impline_indexing")
        
        for imp in self.impList:
            if imp['type'] == 'differential':
                impLayerName=str(imp['id'])+"_imp-"+imp['lyr']+"-"+imp['imp_value']+"ohm-diff-"+imp['line_width_print']+"-"+imp['spacing_print']
            elif imp['type'] == 'single-ended':
                impLayerName=str(imp['id'])+"_imp-"+imp['lyr']+"-"+imp['imp_value']+"ohm-sing-"+imp['line_width_print']
            f.COM("units,type=inch")
            info = f.DO_INFO('-t layer -e %s/%s/%s -d EXISTS'%(jobName,stepName,impLayerName))
            if info['gEXISTS'] == "yes":
                
                f.COM("chklist_cupd,chklist=frontline_impline_indexing,nact=1,params=((pp_ref_layer=%s)(pp_copper_layer=%s)(pp_imp_id=%s)(pp_type=%s)(pp_spacing=%s)(pp_spacing_tol=%s)),mode=regular"%(impLayerName,imp['lyr'],imp['id'],imp['type'],imp['spacing_mil'],paramDict['spacing_tol']))
                f.COM("chklist_run,chklist=frontline_impline_indexing,nact=1")
                check_layer=0
        if check_layer:
            QMessageBox.information(self,u"info",u"辅助层命名不正确或不存在，请检查！",QMessageBox.Ok)
            return

    def createTP(self):
        self.runImpIndexing()
        for imp in self.impList:
            f.COM("imp_cnsts_change,imp_id=%s,ilr_dfm_use=yes"%(imp['id']))

        f.COM("units,type=inch")
        f.COM("chklist_single,show=no,action=frontline_imp_test_points_creator")
        if paramDict['need_shortest'] == "yes":
            need_shortest = "need_medium_test_pad"
        else:
            need_shortest = ""
        if paramDict['need_middle'] == "yes":
            need_middle = "need_shortest_test_pad"
        else:
            need_middle = ""
        
        info=f.DO_INFO("-t netlist -e %s/%s/curnet -d EXISTS"%(jobName,stepName))
        if info['gEXISTS'] == "no":
            # f.COM("netlist_recalc,job=%s,step=%s,type=cur,etset=,display=top,use_cad_names=no,layers_list=,job_cad_net,step_cad_net=,recalc_cur=yes"%(jobName,stepName))
            f.COM("netlist_recalc,job=%s,step=%s,type=cur,etset=,display=top,use_cad_names=no,layers_list=,recalc_cur=yes"%(jobName,stepName))
        
        f.COM("chklist_cupd,chklist=frontline_imp_test_points_creator,nact=1,params=((pp_tp_min_width=%s)(pp_tp_max_width=%s)(pp_imp_min_len=%s)(pp_imp_min_coverage=%s)(pp_tp_good_pair_num=1)(pp_pgtp_max_search_dist=%s)(pp_pgtp_min_width=%s)(pp_allow_middle_pad=allow_middle_pad)(pp_imp_min_avail_percent=10.000000)(pp_imp_has_best_len=)(pp_imp_best_len=4)(pp_tp_need_middle=%s)(pp_tp_need_shortest=%s)(pp_all_need_len_cov=all_need_len_cov)(ignore_attrs=.gold_finger)),mode=regular"%(paramDict['tp_min_width'],paramDict['tp_max_width'],paramDict['tp_imp_min_len'],paramDict['tp_min_coverage_percent'],paramDict['tp_pgpad_max_dist'],paramDict['tp_min_width'],need_shortest,need_middle))
        f.COM("chklist_run,chklist=frontline_imp_test_points_creator,nact=1")


        #grep tp_id here
        tp_dict={}
        impline_dict={}
        lineList=f.INFO("-t check -e %s/%s/frontline_imp_test_points_creator -d MEAS -o action=1"%(jobName,stepName))

        for line in lineList:
            m = re.match('^tp_info (.*?) .*(tpid=.*?) .*',line)
            if m:
                tp_layer=m.group(1)
                tp_info=m.group(2)
                # print(tp_info)
                tp_info_list=tp_info.split('_')
                tp_info_dict={}
                tp_info_dict['tp_layer']=tp_layer
                for el in tp_info_list:
                    elList=el.split("=")
                    tp_info_dict[elList[0]]=elList[1]
                # print(tp_info_dict)

                if tp_layer not in tp_dict.keys():
                    tp_dict[tp_layer]={}
                if tp_info_dict['tpid'] not in tp_dict[tp_layer].keys():
                    tp_dict[tp_layer][tp_info_dict['tpid']]={}
                    tp_dict[tp_layer][tp_info_dict['tpid']]['tpid']=tp_info_dict['tpid']
                    tp_dict[tp_layer][tp_info_dict['tpid']]['polyid']=tp_info_dict['polyid']
                    tp_dict[tp_layer][tp_info_dict['tpid']]['cov']=tp_info_dict['cov']
                    tp_dict[tp_layer][tp_info_dict['tpid']]['len']=tp_info_dict['len']
                    tp_dict[tp_layer][tp_info_dict['tpid']]['padnum']=tp_info_dict['padnum']
                    tp_dict[tp_layer][tp_info_dict['tpid']]['bdnet']=[]
                    tp_dict[tp_layer][tp_info_dict['tpid']]['bdnet'].append(tp_info_dict['bdnet'])
                    tp_dict[tp_layer][tp_info_dict['tpid']]['nf']=[]
                    tp_dict[tp_layer][tp_info_dict['tpid']]['nf'].append(tp_info_dict['nf'])
                    tp_dict[tp_layer][tp_info_dict['tpid']]['type']=[]
                    tp_dict[tp_layer][tp_info_dict['tpid']]['type'].append(tp_info_dict['type'])
                else:
                    tp_dict[tp_layer][tp_info_dict['tpid']]['bdnet'].append(tp_info_dict['bdnet'])
                    tp_dict[tp_layer][tp_info_dict['tpid']]['nf'].append(tp_info_dict['nf'])
                    tp_dict[tp_layer][tp_info_dict['tpid']]['type'].append(tp_info_dict['type'])

            m = re.match('^impline_info .*(impid=.*?) .*',line)
            if m:
                impline_info=m.group(1)
                # print(tp_info)
                impline_info_list=impline_info.split('_')
                impline_info_dict={}
                for el in impline_info_list:
                    elList=el.split("=")
                    impline_info_dict[elList[0]]=elList[1]
                # print("print dict here:")
                # print(impline_info_dict)
                impid = impline_info_dict['impid']
                impline_dict[impid]={}
                # if impid not in impline_dict.keys():
                #     exit()
                impline_dict[impid]['impid']=impline_info_dict['impid']
                impline_dict[impid]['failnum']=impline_info_dict['failnum']
                impline_dict[impid]['totalcount']=impline_info_dict['totalcount']
                impline_dict[impid]['goodcount']=impline_info_dict['goodcount']
                impline_dict[impid]['biggestlen']=impline_info_dict['biggestlen']
                impline_dict[impid]['biggestcov']=impline_info_dict['biggestcov']
                impline_dict[impid]['biggestrank']=impline_info_dict['biggestrank']
                impline_dict[impid]['biggestpolyid']=impline_info_dict['biggestpolyid']
        
        for i in range(1,len(self.impList)+1):
            if str(i) in impline_dict.keys(): 
                self.impList[i-1]['imp_info']=impline_dict[ str(i)]
            else:
                # print("No chains found for imp id: %s\n"%(i))
                QMessageBox.information(self,u"info",u"网络可能存在问题，请检查整板网络是否正确",QMessageBox.Ok)
                return 
        ##end
        # print(tp_dict)

        #decide test point side strategy

        #get top/bot outer layer name
        f.COM("clear_layers")
        f.COM("affected_layer,name=,mode=all,affected=no")
        f.COM("affected_filter,filter=(type=signal|mixed&context=board&side=top&pol=positive)")
        f.COM("get_affect_layer")
        topLayerName=f.COMANS.strip()
        f.COM("clear_layers")
        f.COM("affected_layer,name=,mode=all,affected=no")
        f.COM("affected_filter,filter=(type=signal|mixed&context=board&side=bottom&pol=positive)")
        f.COM("get_affect_layer")
        botLayerName=f.COMANS.strip()
        impLayerSet=set()
        for imp in self.impList:
            impLayerSet.add(imp['lyr'])
        
        sideDecideNum=0
        if topLayerName in impLayerSet and botLayerName not in impLayerSet:
            sideDecideNum=1
        elif topLayerName not in impLayerSet and botLayerName in impLayerSet:
            sideDecideNum=2
        elif topLayerName in impLayerSet and botLayerName in impLayerSet:
            sideDecideNum=3
            #judge the distance
        else:
            sideDecideNum=0
            #get tp number in top and bot, if top>bot, choose top

        #get layerNumDict
        layerNumDict={}
        info = f.DO_INFO("-t matrix -e %s/matrix -d ROW -p name+row"%(jobName))
        for i in range(len(info['gROWname'])):
            if info['gROWname'][i] != "":
                layerNumDict[info['gROWname'][i]]=info['gROWrow'][i]

        # print(impLayerSet)
        # f.PAUSE("==%s==%s==%s= ="%(sideDecideNum,topLayerName,botLayerName))
        
        for imp in self.impList:
            # f.PAUSE("%s==%s==%s"%(imp['lyr'],imp['top_ref'],imp['bot_ref']))
            if sideDecideNum==0:
                if topLayerName in tp_dict.keys() and botLayerName in tp_dict.keys():
                    if len(tp_dict[topLayerName].keys())>len(tp_dict[botLayerName].keys()):
                        outerLayer=topLayerName
                    else:
                        outerLayer=botLayerName
                elif topLayerName not in tp_dict.keys() and botLayerName in tp_dict.keys():
                    outerLayer=botLayerName
                elif topLayerName in tp_dict.keys() and botLayerName not in tp_dict.keys():
                    outerLayer=topLayerName
                furtherSearch=1

            elif sideDecideNum==1:
                outerLayer=topLayerName
                if imp['lyr']==topLayerName:
                    furtherSearch=0
                else:
                    furtherSearch=1
            elif sideDecideNum==2:
                outerLayer=botLayerName
                if imp['lyr']==botLayerName:
                    furtherSearch=0
                else:
                    furtherSearch=1
            elif sideDecideNum==3:
                if imp['lyr']==topLayerName:
                    outerLayer=topLayerName
                    furtherSearch=0
                elif imp['lyr']==botLayerName:
                    outerLayer=botLayerName
                    furtherSearch=0
                else:
                    topDist=int(layerNumDict[imp['lyr']])-int(layerNumDict[topLayerName])
                    botDist=int(layerNumDict[botLayerName])-int(layerNumDict[imp['lyr']])
                    if topDist<=botDist:
                        outerLayer=topLayerName
                    else:
                        outerLayer=botLayerName
                    furtherSearch=1
            else:
                continue
            


            imp["tp_layer"]=outerLayer
            imp['has_tp']=0
            imp['tpLayerName']=""
            imp['pgtpLayerName']=""
            imp['tpLimitMinX']=[]
            imp['tpLimitMinY']=[]
            imp['tpLimitMaxX']=[]
            imp['tpLimitMaxY']=[]
            imp['tpLimitCenterX']=[]
            imp['tpLimitCenterY']=[]
            imp['impLen']=[]
            imp['impCov']=[]
            imp['tp_nf'] = []
            imp['tp_bdnet'] = []
            imp['pgtp_nf_list']=[]
            tp_id_num_list=[]

            tp_id_num_list.append(str(imp['id']*10000+1000+1))
            if paramDict['need_shortest'] == "yes":
                tp_id_num_list.append(str(imp['id']*10000+2000+1))

            if paramDict['need_middle'] == "yes":
                tp_id_num_list.append(str(imp['id']*10000+3000+1))


            tp_id_loop=0
            for tp_id_num in tp_id_num_list:
                if outerLayer in tp_dict.keys() and tp_id_num in tp_dict[outerLayer].keys():
                    f.COM("clear_layers")
                    f.COM("affected_layer,name=,mode=all,affected=no")
                    f.COM("display_layer,name=%s,display=yes"%(outerLayer))
                    f.COM("work_layer,name=%s"%(outerLayer))

                    # for nf_index in tp_dict[outerLayer][tp_id_num]['nf']:
                    #     f.COM("sel_layer_feat,operation=select,layer=%s,index=%s"%(outerLayer,nf_index))
                    for i in range(len(tp_dict[outerLayer][tp_id_num]['nf'])):
                        f.COM("sel_layer_feat,operation=select,layer=%s,index=%s"%(outerLayer,tp_dict[outerLayer][tp_id_num]['nf'][i]))
                        
                        if tp_dict[outerLayer][tp_id_num]['type'][i] == '4':
                            imp['pgtp_nf_list'].append(tp_dict[outerLayer][tp_id_num]['nf'][i])
                        else:
                            imp['tp_bdnet'].append(tp_dict[outerLayer][tp_id_num]['bdnet'][i])
                else:
                    if furtherSearch == 1:
                        if outerLayer==topLayerName:
                            outerLayer = botLayerName
                        elif outerLayer==botLayerName:
                            outerLayer=topLayerName

                        imp["tp_layer"]=outerLayer

                        f.COM("clear_layers")
                        f.COM("affected_layer,name=,mode=all,affected=no")
                        f.COM("display_layer,name=%s,display=yes"%(outerLayer))
                        f.COM("work_layer,name=%s"%(outerLayer))
                        if outerLayer in tp_dict.keys() and tp_id_num in tp_dict[outerLayer].keys():
                            for i in range(len(tp_dict[outerLayer][tp_id_num]['nf'])):
                                f.COM("sel_layer_feat,operation=select,layer=%s,index=%s"%(outerLayer,tp_dict[outerLayer][tp_id_num]['nf'][i]))
                                if tp_dict[outerLayer][tp_id_num]['type'][i] == '4':
                                    imp['pgtp_nf_list'].append(tp_dict[outerLayer][tp_id_num]['nf'][i])
                                else:
                                    imp['tp_bdnet'].append(tp_dict[outerLayer][tp_id_num]['bdnet'][i])
                    else:
                        continue

                f.COM("get_select_count")
                selectCount=int(f.COMANS)
                if selectCount != 0:
                    # ['type','lyr','top_ref','bot_ref','line_width','req_line_width','spacing','req_spacing','cop_dist','imp_value']
                    
                    info=f.DO_INFO("-t layer -e %s/%s/%s -d LIMITS -o consider_origin+select"%(jobName,stepName,outerLayer))
                    imp['tpLimitMinX'].append(float(info['gLIMITSxmin'])-0.003)
                    imp['tpLimitMinY'].append(float(info['gLIMITSymin'])-0.003)
                    imp['tpLimitMaxX'].append(float(info['gLIMITSxmax'])+0.003)
                    imp['tpLimitMaxY'].append(float(info['gLIMITSymax'])+0.003)
                    imp['tpLimitCenterX'].append(float(info['gLIMITSxcenter']))
                    imp['tpLimitCenterY'].append(float(info['gLIMITSycenter']))
                    imp['tp_nf'].append(tp_dict[outerLayer][tp_id_num]['nf'])
                    # imp['tp_id_num_list'].append(tp_id_num)
                    
                    imp['impLen'].append(str(round(float(tp_dict[outerLayer][tp_id_num]['len']),2)))
                    imp['impCov'].append(str(round(float(tp_dict[outerLayer][tp_id_num]['cov']),2)))
                    

                    # lineList=f.INFO("-t layer -e %s/%s/%s -d FEATURES -o select+f0"%(jobName,stepName,outerLayer))
                        
                    # for line in lineList:
                    #     m = re.match('.*;\.tp_info=(.*?),.*',line)
                    #     if m:
                    #         tp_info=m.group(1)
                    #         # print(tp_info)
                    #         tp_info_list=tp_info.split('_')
                    #         tp_info_dict={}
                    #         for el in tp_info_list:
                    #             elList=el.split("=")
                    #             tp_info_dict[elList[0]]=elList[1]
                    #         # round(float(tp_info_dict['len']),2)
                    #         imp['impLen'].append(str(round(float(tp_info_dict['len']),2)))
                    #         f.PAUSE("===imp_id%s:%s==="%(tp_id_num,tp_info_dict['len']))
                    #         break

                    if imp['type'] == 'differential':
                        tpLayerName=str(imp['id'])+"_tp_"+outerLayer+"-"+imp['lyr']+"-"+imp['imp_value']+"ohm-diff-"+imp['line_width_print']+"-"+imp['spacing_print']
                    elif imp['type'] == 'single-ended':
                        tpLayerName=str(imp['id'])+"_tp_"+outerLayer+"-"+imp['lyr']+"-"+imp['imp_value']+"ohm-sing-"+imp['line_width_print']
                    info=f.DO_INFO("-t layer -e %s/%s/%s -d EXISTS"%(jobName,stepName,tpLayerName))
                    if info['gEXISTS'] == "yes" and tp_id_loop==0:
                        f.COM("delete_layer, layer=%s"%(tpLayerName))

                    imp['tpLayerName']=tpLayerName
                    f.COM("sel_copy_other,dest=layer_name,target_layer=%s,invert=no,dx=0,dy=0,size=0,x_anchor=0,y_anchor=0"%(tpLayerName))
                    imp['has_tp']=1
                    tp_id_loop=1
                    furtherSearch=0

            if tp_id_loop == 1 and imp['type'] == 'single-ended':
                pgtpLayerName=str(imp['id'])+"_tp_"+outerLayer+"-"+imp['lyr']+"-"+imp['imp_value']+"ohm-sing-"+imp['line_width_print']+"-pglayer"
                imp['pgtpLayerName']=pgtpLayerName
                for pg_nf in imp['pgtp_nf_list']:
                    f.COM("sel_layer_feat,operation=select,layer=%s,index=%s"%(outerLayer,pg_nf))
                f.COM("sel_copy_other,dest=layer_name,target_layer=%s,invert=no,dx=0,dy=0,size=0,x_anchor=0,y_anchor=0"%(pgtpLayerName))

            if tp_id_loop == 1:
                f.COM("clear_layers")
                f.COM("affected_layer,name=,mode=all,affected=no")
                f.COM("display_layer,name=%s,display=yes"%(tpLayerName))
                f.COM("work_layer,name=%s"%(tpLayerName))
                for i in range(len(imp['tpLimitMinX'])):
                    f.COM("add_polyline_strt")
                    f.COM("add_polyline_xy,x=%s,y=%s"%(imp['tpLimitMinX'][i],imp['tpLimitMinY'][i]))
                    f.COM("add_polyline_xy,x=%s,y=%s"%(imp['tpLimitMinX'][i],imp['tpLimitMaxY'][i]))
                    f.COM("add_polyline_xy,x=%s,y=%s"%(imp['tpLimitMaxX'][i],imp['tpLimitMaxY'][i]))
                    f.COM("add_polyline_xy,x=%s,y=%s"%(imp['tpLimitMaxX'][i],imp['tpLimitMinY'][i]))
                    f.COM("add_polyline_xy,x=%s,y=%s"%(imp['tpLimitMinX'][i],imp['tpLimitMinY'][i]))
                    f.COM("add_polyline_end,polarity=positive,attributes=no,symbol=r1,bus_num_lines=0,bus_dist_by=pitch,bus_distance=0,bus_reference=left")
                    text_xcoord=imp['tpLimitCenterX'][i]-0.008
                    text_ycoord=imp['tpLimitCenterY'][i]-0.005
                    f.COM("add_text,type=string,polarity=positive,x=%s,y=%s,text=(%s),fontname=standard,mirror=no,angle=0,direction=cw,x_size=0.006,y_size=0.01,w_factor=0.08"%(text_xcoord,text_ycoord,i+1))
        
        self.takeSnapShot()
        self.createPDF()
        self.createTPReport()
        self.mergePDF3()
        
        

    def takeSnapShot(self):
        f.COM("zoom_home")
        for imp in self.impList:
            if imp['has_tp']==1:

                f.COM("clear_layers")
                f.COM("affected_layer,name=,mode=all,affected=no")
                f.COM("display_layer,name=%s,display=yes"%(imp['tp_layer']))
                f.COM("work_layer,name=%s"%(imp['tp_layer']))

                for i in range(len(imp['tpLimitMinX'])):
                    index_str="\\;".join(imp['tp_nf'][i])
                    f.COM("reset_filter_criteria,filter_name=,criteria=all")
                    f.COM("set_filter_type,filter_name=,lines=no,pads=yes,surfaces=no,arcs=no,text=no")
                    f.COM("set_filter_and_or_logic,filter_name=popup,criteria=inc_attr,logic=and")
                    f.COM("adv_filter_reset")
                    # f.COM("filter_area_strt")
                    f.COM("adv_filter_set,filter_name=popup,active=yes,limit_box=no,bound_box=no,indexes=%s,srf_values=no,srf_area=no,mirror=any,ccw_rotations="%(index_str))
                    f.COM("filter_highlight,layer=,filter_name=popup,lines_only=no,ovals_only=no,min_len=0,max_len=0,min_angle=0,max_angle=0")

                    f.COM("zoom_pv_open,x1=%s,y1=%s,x2=%s,y2=%s,x_win=-50,y_win=%s,w_win=260,h_win=260"%(imp['tpLimitMinX'][i]-0.05,imp['tpLimitMinY'][i]-0.05,imp['tpLimitMaxX'][i]+0.05,imp['tpLimitMaxY'][i]+0.05,i*300))


                bdnetStr="\\;".join(imp['tp_bdnet'])
                f.COM("display_net,job=%s,step=%s,netlist=cur,color=5,section=first,nets=%s\;,disp_mode=outline,all_lyrs=yes,top_tp=no,bot_tp=no,drl_tp=no,npth_tp=no,inner_tp=no"%(jobName,stepName,bdnetStr))

                picPathName=self.tmpDir+str(imp['id'])+".png"
                
                # f.COM("create_snapshot")
                #note:l4/l5/l6-diff-3/3-85ohm
                if imp['type'] == 'differential':
                    note1=imp['top_ref']+"/"+imp['lyr']+"/"+imp['bot_ref']+"-diff-"+imp['line_width_print']+"/"+imp['spacing_print']+"-"+imp['imp_value']+"ohm"+"-"+imp['impLen'][0]+"inch"
                elif imp['type'] == 'single-ended':
                    note1=imp['top_ref']+"/"+imp['lyr']+"/"+imp['bot_ref']+"-single-"+imp['line_width_print']+"-"+imp['imp_value']+"ohm"+"-"+imp['impLen'][0]+"inch"
                
                f.COM("save_snapshot,path=%s,note1=%s"%(picPathName,note1))
                f.COM("zoom_pv_close,all=yes")
                f.COM("clear_highlight")
                f.COM("display_net,color=0,section=first,disp_mode=clear")
                f.COM("display_net,color=0,section=second,disp_mode=clear")

    def createPDF(self):
        for imp in self.impList:
            if imp['has_tp']==1:
                # fullLayerName=imp['top_ref']+"/"+imp['lyr']+"/"+imp['bot_ref']
                if imp['type'] == 'differential':
                    type_cn=u"差分阻抗"
                    orig_width=imp['line_width_print']+"/"+imp['spacing_print']
                    req_width=imp['req_line_width_print']+"/"+imp['req_spacing_print']
  
                elif imp['type'] == 'single-ended':
                    type_cn=u"单端阻抗"
                    orig_width=imp['line_width_print']
                    req_width=imp['req_line_width_print']
                finishValue=imp['imp_value']

                lenStr1=imp['impLen'][0]+"\""
                covStr1=imp['impCov'][0]+"%"
                lenStr2=""
                lenStr3=""
                covStr2=""
                covStr3=""
                if len(imp['impLen'])==2:
                    lenStr2=imp['impLen'][1]+"\""
                    covStr2=imp['impCov'][1]+"%"
                if len(imp['impLen'])==3:
                    lenStr2=imp['impLen'][1]+"\""
                    covStr2=imp['impCov'][1]+"%"
                    lenStr3=imp['impLen'][2]+"\""
                    covStr3=imp['impCov'][2]+"%"
                if units=="um":
                    lenStr1=str(round(float(imp['impLen'][0])*25.4,1))+"mm"
                    covStr1=imp['impCov'][0]+"%"
                    lenStr2=""
                    lenStr3=""
                    covStr2=""
                    covStr3=""
                    if len(imp['impLen'])==2:
                        lenStr2=str(round(float(imp['impLen'][1])*25.4,1))+"mm"
                        covStr2=imp['impCov'][1]+"%"
                    if len(imp['impLen'])==3:
                        lenStr2=str(round(float(imp['impLen'][1])*25.4,1))+"mm"
                        covStr2=imp['impCov'][1]+"%"
                        lenStr3=str(round(float(imp['impLen'][2])*25.4,1))+"mm"
                        covStr3=imp['impCov'][2]+"%"

                # data= [[u"序号",u"类型",u"成品Ω",u"层别",u"上/下参考层",u"原稿mil",u"成品mil",u"视图面次",u"达标线段数",u"1线长/覆盖率","",u"2线长/覆盖率","",u"3线长/覆盖率",""],
                #         [imp['id'],type_cn,finishValue,imp['lyr'],imp['top_ref']+"/"+imp['bot_ref'],orig_width,req_width,imp['tp_layer'],imp['imp_info']['goodcount'],lenStr1,covStr1,lenStr2,covStr2,lenStr3,covStr3]]
                # t = Table(data, style={
                #     ("FONT", (0, 0), (-1, -1), msyh, 8),
                #     ("GRID",(0,0),(8,0),1,colors.black),
                #     ("GRID",(0,1),(-1,1),1,colors.black),
                #     ("BOX",(9,0),(10,0),1,colors.black),
                #     ("BOX",(11,0),(12,0),1,colors.black),
                #     ("BOX",(13,0),(14,0),1,colors.black),
                #     ("TEXTCOLOR", (0, 0), (-1, -1), colors.black),
                #     ('ALIGN', (1, 0), (1, -1), 'CENTER'),
                #     # ('SPAN',(9,0),(10,0)), //can only support 2 span
                #     # ('SPAN',(11,0),(12,0)),
                #     # ('SPAN',(13,0),(14,0)),
                # })

                # for i in range(len(t._argW)):
                #     if i == 0 or i == 2 or i == 3 or i==9 or i == 11 or i == 13:
                #         t._argW[i] = 30
                #         continue
                #     if i == 4 or i == 8:
                #         t._argW[i] = 50
                #         continue
                #     t._argW[i] = 40
                if len(imp['impLen'])==3:
                    data= [[u"序号",u"类型",u"成品Ω",u"层别",u"上/下参考层",u"原稿"+units,u"成品"+units,u"视图面次",u"1线长/覆盖率","",u"2线长/覆盖率","",u"3线长/覆盖率",""],
                            [imp['id'],type_cn,finishValue,imp['lyr'],imp['top_ref']+"/"+imp['bot_ref'],orig_width,req_width,imp['tp_layer'],lenStr1,covStr1,lenStr2,covStr2,lenStr3,covStr3]]
                    t = Table(data, style={
                        ("FONT", (0, 0), (-1, -1), msyh, 8),
                        ("GRID",(0,0),(7,0),1,colors.black),
                        ("GRID",(0,1),(-1,1),1,colors.black),
                        ("BOX",(8,0),(9,0),1,colors.black),
                        ("BOX",(10,0),(11,0),1,colors.black),
                        ("BOX",(12,0),(13,0),1,colors.black),
                        ("TEXTCOLOR", (0, 0), (-1, -1), colors.black),
                        ('ALIGN', (1, 0), (1, -1), 'CENTER'),
                        # ('SPAN',(9,0),(10,0)), //can only support 2 span
                        # ('SPAN',(11,0),(12,0)),
                        # ('SPAN',(13,0),(14,0)),
                    })

                    for i in range(len(t._argW)):
                        if i == 0 or i == 2 or i == 3:
                            t._argW[i] = 30
                            continue
                        if i == 4 or i == 5 or i == 6:
                            t._argW[i] = 60
                            continue
                        t._argW[i] = 40

                if len(imp['impLen'])==2:
                    data= [[u"序号",u"类型",u"成品Ω",u"层别",u"上/下参考层",u"原稿"+units,u"成品"+units,u"视图面次",u"1线长/覆盖率","",u"2线长/覆盖率",""],
                            [imp['id'],type_cn,finishValue,imp['lyr'],imp['top_ref']+"/"+imp['bot_ref'],orig_width,req_width,imp['tp_layer'],lenStr1,covStr1,lenStr2,covStr2]]
                    t = Table(data, style={
                        ("FONT", (0, 0), (-1, -1), msyh, 8),
                        ("GRID",(0,0),(7,0),1,colors.black),
                        ("GRID",(0,1),(-1,1),1,colors.black),
                        ("BOX",(8,0),(9,0),1,colors.black),
                        ("BOX",(10,0),(11,0),1,colors.black),
                        # ("BOX",(12,0),(13,0),1,colors.black),
                        ("TEXTCOLOR", (0, 0), (-1, -1), colors.black),
                        ('ALIGN', (1, 0), (1, -1), 'CENTER'),
                        # ('SPAN',(9,0),(10,0)), //can only support 2 span
                        # ('SPAN',(11,0),(12,0)),
                        # ('SPAN',(13,0),(14,0)),
                    })

                    for i in range(len(t._argW)):
                        if i == 0 or i == 2 or i == 3 :
                            t._argW[i] = 30
                            continue
                        if i == 4 or i == 5 or i == 6:
                            t._argW[i] = 60
                            continue
                        t._argW[i] = 40

                if len(imp['impLen'])==1:
                    data= [[u"序号",u"类型",u"成品Ω",u"层别",u"上/下参考层",u"原稿"+units,u"成品"+units,u"视图面次",u"1线长/覆盖率",""],
                            [imp['id'],type_cn,finishValue,imp['lyr'],imp['top_ref']+"/"+imp['bot_ref'],orig_width,req_width,imp['tp_layer'],lenStr1,covStr1]]
                    t = Table(data, style={
                        ("FONT", (0, 0), (-1, -1), msyh, 8),
                        ("GRID",(0,0),(7,0),1,colors.black),
                        ("GRID",(0,1),(-1,1),1,colors.black),
                        ("BOX",(8,0),(9,0),1,colors.black),
                        # ("BOX",(10,0),(11,0),1,colors.black),
                        # ("BOX",(12,0),(13,0),1,colors.black),
                        ("TEXTCOLOR", (0, 0), (-1, -1), colors.black),
                        ('ALIGN', (1, 0), (1, -1), 'CENTER'),
                        # ('SPAN',(9,0),(10,0)), //can only support 2 span
                        # ('SPAN',(11,0),(12,0)),
                        # ('SPAN',(13,0),(14,0)),
                    })

                    for i in range(len(t._argW)):
                        if i == 0 or i == 2 or i == 3:
                            t._argW[i] = 30
                            continue
                        if i == 4 or i == 5 or i == 6:
                            t._argW[i] = 60
                            continue
                        t._argW[i] = 40


                doc = SimpleDocTemplate(self.tmpDir+str(imp['id'])+".pdf")
                Story=[]
                Story.append(Paragraph(titleName, titleStyle))
                Story.append(Spacer(1, 0.2 * inch))
                Story.append(t)
                Story.append(Spacer(1, 0.2 * inch))
                Story.append(Image(self.tmpDir+str(imp['id'])+".png", 7.07 * inch, 7.48 * inch))
                doc.build(Story)
            else:
                if imp['type'] == 'differential':
                    type_cn=u"差分阻抗"
                    orig_width=imp['line_width_print']+"/"+imp['spacing_print']
                    req_width=imp['req_line_width_print']+"/"+imp['req_spacing_print']
                elif imp['type'] == 'single-ended':
                    type_cn=u"单端阻抗"
                    orig_width=imp['line_width_print']
                    req_width=imp['req_line_width_print']
                finishValue=imp['imp_value']
                fail_num=int(imp['imp_info']['failnum'])

                data= [[u"序号",u"类型",u"成品Ω",u"层别",u"上/下参考层",u"原稿"+units,u"成品"+units,u"没有合适测点",u"可能原因"],
                        [imp['id'],type_cn,finishValue,imp['lyr'],imp['top_ref']+"/"+imp['bot_ref'],orig_width,req_width,u"没有合适测点",failreason[fail_num]]]
                t = Table(data, style={
                    ("FONT", (0, 0), (-1, -1), msyh, 8),
                    ("GRID",(0,0),(-1, -1),1,colors.black),
                    ("TEXTCOLOR", (0, 0), (-1, -1), colors.black),
                    ('ALIGN', (1, 0), (1, -1), 'CENTER'),
                })

                for i in range(len(t._argW)):
                    if i == 7 or i == 8 :
                        t._argW[i] = 70
                        continue
                    t._argW[i] = 50

                doc = SimpleDocTemplate(self.tmpDir+str(imp['id'])+".pdf")
                Story=[]
                Story.append(Paragraph(titleName, titleStyle))
                Story.append(Spacer(1, 0.2 * inch))
                Story.append(t)
                doc.build(Story)


    def createTPReport(self):
        for imp in self.impList:
            if imp['has_tp']==1:
                if imp['type'] == 'differential':
                    # f.COM("print,title=,layer_name=%s\;%s,mirrored_layers=,draw_profile=no,drawing_per_layer=no,label_layers=no,dest=pdf_file,num_copies=1,dest_fname=%s,paper_size=A4,scale_to=0,nx=1,ny=1,orient=portrait,paper_orient=portrait,paper_width=0,paper_height=0,paper_units=inch,auto_tray=no,page_numbering=no,top_margin=0.5,bottom_margin=0.5,left_margin=0.5,right_margin=0.5,x_spacing=0,y_spacing=0,color1=990000,color2=9900,color3=99,color4=990099,color5=999900,color6=9999"%(imp['tp_layer'],imp['tpLayerName'],self.tmpDir+str(imp['id'])+"_1.pdf"))

                    if os_type == "Linux":
                        f.COM("print,title=,layer_name=%s\;%s,mirrored_layers=,draw_profile=no,drawing_per_layer=no,label_layers=no,dest=ps_file,num_copies=1,dest_fname=%s,paper_size=A4,scale_to=0,nx=1,ny=1,orient=portrait,paper_orient=portrait,paper_width=0,paper_height=0,paper_units=inch,auto_tray=no,page_numbering=no,top_margin=0.5,bottom_margin=0.5,left_margin=0.5,right_margin=0.5,x_spacing=0,y_spacing=0,color1=990000,color2=9900,color3=99,color4=990099,color5=999900,color6=9999"%(imp['tp_layer'],imp['tpLayerName'],self.tmpDir+str(imp['id'])+"_1.ps"))
                        if os.path.exists(self.tmpDir+str(imp['id'])+"_1.ps"):
                            os.system("ps2pdf %s %s"%(self.tmpDir+str(imp['id'])+"_1.ps",self.tmpDir+str(imp['id'])+"_1.pdf"))

                if imp['type'] == 'single-ended':
                    # f.COM("print,title=,layer_name=%s\;%s\;%s,mirrored_layers=,draw_profile=no,drawing_per_layer=no,label_layers=no,dest=pdf_file,num_copies=1,dest_fname=%s,paper_size=A4,scale_to=0,nx=1,ny=1,orient=portrait,paper_orient=portrait,paper_width=0,paper_height=0,paper_units=inch,auto_tray=no,page_numbering=no,top_margin=0.5,bottom_margin=0.5,left_margin=0.5,right_margin=0.5,x_spacing=0,y_spacing=0,color1=990000,color2=9900,color3=99,color4=990099,color5=999900,color6=9999"%(imp['tp_layer'],imp['tpLayerName'],imp['pgtpLayerName'],self.tmpDir+str(imp['id'])+"_1.pdf"))
                    
                    if os_type == "Linux":
                        f.COM("print,title=,layer_name=%s\;%s\;%s,mirrored_layers=,draw_profile=no,drawing_per_layer=no,label_layers=no,dest=ps_file,num_copies=1,dest_fname=%s,paper_size=A4,scale_to=0,nx=1,ny=1,orient=portrait,paper_orient=portrait,paper_width=0,paper_height=0,paper_units=inch,auto_tray=no,page_numbering=no,top_margin=0.5,bottom_margin=0.5,left_margin=0.5,right_margin=0.5,x_spacing=0,y_spacing=0,color1=990000,color2=9900,color3=99,color4=990099,color5=999900,color6=9999"%(imp['tp_layer'],imp['tpLayerName'],imp['pgtpLayerName'],self.tmpDir+str(imp['id'])+"_1.ps"))
                        if os.path.exists(self.tmpDir+str(imp['id'])+"_1.ps"):
                            os.system("ps2pdf %s %s"%(self.tmpDir+str(imp['id'])+"_1.ps",self.tmpDir+str(imp['id'])+"_1.pdf"))
                    f.COM('delete_layer, layer=' + imp['pgtpLayerName'])
                
                

    def mergePDF(self):
        expense_reports=[]
        for i in range(len(self.impList)+1):
            fileName=str(i)+".pdf"
            fileName1=str(i)+"_1.pdf"
            if os.path.isfile(self.tmpDir+fileName):
                expense_reports.append(self.tmpDir+fileName)
            if os.path.isfile(self.tmpDir+fileName1):
                expense_reports.append(self.tmpDir+fileName1)
        pdfFileListName=" ".join(expense_reports)
        # print("/usr/bin/pdftk %s cat output %s"%(pdfFileListName,self.tmpDir+theOnepdfName))
        os.system("/usr/bin/pdftk %s cat output %s"%(pdfFileListName,self.theOnepdfName))
        QMessageBox.information(self,u"info",u"报告创建完成，请查看%s"%(self.theOnepdfName),QMessageBox.Ok)
        return
        if os.path.exists(self.theOnepdfName):
            os.system("mv %s %s"%(self.theOnepdfName,paramDict['rep_path']+"/"+paramDict['rep_filename']+"-old.pdf"))
            if os.path.exists(self.theOnepdfName):
                QMessageBox.information(self,u"info",u"PDF报告被打开，请关闭报告后重新创建",QMessageBox.Ok)
                return
        # else:
        os.system("gs -q -dPDFSETTINGS=/ebook -dNOPAUSE -sDEVICE=pdfwrite -sOUTPUTFILE=%s -dBATCH %s"%(self.theOnepdfName,pdfFileListName))
        QMessageBox.information(self,u"info",u"报告创建完成，请查看%s"%(self.theOnepdfName),QMessageBox.Ok)

    def mergePDF3(self):
        self.theOnepdfName=paramDict['rep_path']+"/"+paramDict['rep_prefix']+paramDict['rep_filename']+paramDict['rep_suffix']+".pdf"
        merger = PdfMerger()
        for i in range(len(self.impList)+1):
            fileName=str(i)+".pdf"
            fileName1=str(i)+"_1.pdf"
            if os.path.isfile(self.tmpDir+fileName):
                merger.append(self.tmpDir+fileName)
            if os.path.isfile(self.tmpDir+fileName1):
                merger.append(self.tmpDir+fileName1)
        merger.write(self.theOnepdfName)
        merger.close()
        QMessageBox.information(self,u"info",u"报告创建完成，请查看%s"%(self.theOnepdfName),QMessageBox.Ok)



    def createImpMiscLyr(self):
        # if len(self.impList) == 0:
        self.createImpList()
        for imp in self.impList:
            if imp['type'] == 'differential':
                impLayerName=str(imp['id'])+"_imp-"+imp['lyr']+"-"+imp['imp_value']+"ohm-diff-"+imp['line_width_print']+"-"+imp['spacing_print']
            elif imp['type'] == 'single-ended':
                impLayerName=str(imp['id'])+"_imp-"+imp['lyr']+"-"+imp['imp_value']+"ohm-sing-"+imp['line_width_print']
            info = f.DO_INFO('-t layer -e %s/%s/%s -d EXISTS'%(jobName,stepName,impLayerName))
            if info['gEXISTS'] == "no":
                f.COM("create_layer,layer=%s,context=misc,type=signal,polarity=positive"%(impLayerName))


    def runILA(self):
        # if len(self.impList) == 0:
        self.createImpList()
        idList=[]
        for imp in self.impList:
            f.COM("imp_cnsts_change,imp_id=%s,ilr_dfm_use=yes"%(imp['id']))
            idList.append(str(imp['id']))
        f.COM("imp_refresh_tbl,refresh_table=yes")
        id_str="\\;".join(idList)
        id_str=id_str+"\\;"

        f.COM("chklist_single,action=frontline_dfm_impedance_lines_repair,show=no")
        f.COM("units,type=mm")
        f.COM("chklist_cupd,chklist=frontline_dfm_impedance_lines_repair,nact=1,params=((pp_imp_layer=.affected)(pp_imp_id_str=%s)(pp_search_distance=25.4)(pp_min_cu_spacing=0)(pp_min_drl_spacing=0)(pp_min_rout_spacing=0)),mode=regular"%(id_str))
        f.COM("chklist_cnf_act,chklist=frontline_dfm_impedance_lines_repair,nact=1,cnf=no")
        # f.COM("chklist_run_act,chklist=frontline_imp_rec_simp,nact=1")
        f.COM("chklist_run,chklist=frontline_dfm_impedance_lines_repair,nact=1")
        f.COM("units,type=inch")
        f.COM("chklist_res_group_repair_show,chklist=frontline_dfm_impedance_lines_repair,nact=1,x=0,y=0,w=0,h=0,is_run_results=no,is_cf_resume=yes")
        f.COM("zoom_mode,zoom=zoom,family=general")
        self.pause()

    def pause(self):
        self.hide()
        f.COM("affected_layer,name=,mode=all,affected=no")
        #for CEE
        f.COM("units,type=mm")
        f.PAUSE("please click continue to show the impedance process window!")
        self.show()
        self.move((QtWidgets.QApplication.desktop().width() - self.width())/2,(QtWidgets.QApplication.desktop().height() - self.height())/2)
    


    def pushButton_selectImpListFile_clicked(self):
        directory = QFileDialog.getOpenFileName(self,"Select File",scriptDir)
        if directory[0] != "":
            param = directory[0].replace("\\","/")
            self.lineEdit_ImpListFilePath.setText(param)
            self.load_impList(param)

    def pushButton_saveAsImpList_clicked(self):
        file_path = QFileDialog.getSaveFileName(self,"Save As",scriptDir)
        if file_path[0] != "":
            self.saveImpList(file_path[0])


    def pushButton_saveImpList_clicked(self):
        file_path=str(self.lineEdit_ImpListFilePath.text())
        if file_path != "":
            self.saveImpList(file_path)
        else:
            QMessageBox.information(self,u"info",u"请输入文件路径",QMessageBox.Ok)
            return

    def saveImpList(self,filePath):
        self.createImpList()
        tmpKeyNameList=['type','lyr','top_ref','bot_ref','line_width_mil','req_line_width_mil','spacing_mil','req_spacing_mil','imp_value']
        csvList=[]
        for imp in self.impList:
            lineList=[]
            for keyName in tmpKeyNameList:
                lineList.append(str(imp[keyName]))
            csvList.append(",".join(lineList))
        text="\n".join(csvList)
        csvFile=open(filePath,'w')
        csvFile.write(text)
        csvFile.close()

    def cmb1ValueChange(self,num):
        if num == -1:
            return
        sender=self.sender()
        senderName=sender.objectName().__str__()
        senderNameList=senderName.split("_")
        row=int(senderNameList[1])
        col=int(senderNameList[2])
        curText=sender.currentText().__str__()
        if curText != "":
            self.tableView_ImpList.indexWidget(self.realModel.index(row,col+1)).setCurrentIndex(num-1)
            self.tableView_ImpList.indexWidget(self.realModel.index(row,col+2)).setCurrentIndex(num+1)
        else:
            self.tableView_ImpList.indexWidget(self.realModel.index(row,col+1)).setCurrentIndex(0)
            self.tableView_ImpList.indexWidget(self.realModel.index(row,col+2)).setCurrentIndex(0)            

    def pushButton_addImp_clicked(self):
        curRowCount=self.realModel.rowCount()
        self.realModel.setRowCount(curRowCount+1)
        cmb0 = QComboBox()
        # cmb0.setEditable(True)
        cmb0.addItems(['differential','single-ended'])
        self.tableView_ImpList.setIndexWidget(self.realModel.index(curRowCount,0),cmb0)
        cmb1 = QComboBox()
        cmb1.addItems(self.boardLyrList)
        cmb1.setObjectName('comboBox_%s_%s'%(curRowCount,1))
        cmb1.currentIndexChanged.connect(self.cmb1ValueChange)
        self.tableView_ImpList.setIndexWidget(self.realModel.index(curRowCount,1),cmb1)
    
        cmb2 = QComboBox()
        cmb2.addItems(self.boardLyrList)
        self.tableView_ImpList.setIndexWidget(self.realModel.index(curRowCount,2),cmb2)
        cmb3 = QComboBox()
        cmb3.addItems(self.boardLyrList)
        self.tableView_ImpList.setIndexWidget(self.realModel.index(curRowCount,3),cmb3)

        # self.realModel.setItem(curRowCount,1,QStandardItem())
        # self.realModel.setItem(curRowCount,2,QStandardItem())
        # self.realModel.setItem(curRowCount,3,QStandardItem())
        self.realModel.setItem(curRowCount,4,QStandardItem())
        self.realModel.setItem(curRowCount,5,QStandardItem())
        self.realModel.setItem(curRowCount,6,QStandardItem())
        self.realModel.setItem(curRowCount,7,QStandardItem())
        self.realModel.setItem(curRowCount,8,QStandardItem())

    def tableViewRightMenu(self, pos):
#         print(pos)
        
        curIndex=self.tableView_ImpList.indexAt(pos)
        rowNum = curIndex.row()
        
        if rowNum != -1:
            menu = QMenu()
            item1 = menu.addAction(u'复制')
            item2 = menu.addAction(u'删除')
            # item3 = menu.addAction(u'添加')
            # 将坐标转化为相对于屏幕的
            screenPos = self.tableView_ImpList.mapToGlobal(pos)
            screenPos.setY(screenPos.y()+30)
            action = menu.exec_(screenPos)

            if action == item1:
#                 itemList=self.realModel.takeRow(rowNum)
                itemList=[QStandardItem(self.realModel.item(rowNum, 0)),
                          QStandardItem(self.realModel.item(rowNum, 1)),
                          QStandardItem(self.realModel.item(rowNum, 2)),
                          QStandardItem(self.realModel.item(rowNum, 3)),
                          QStandardItem(self.realModel.item(rowNum, 4)),
                          QStandardItem(self.realModel.item(rowNum, 5)),
                          QStandardItem(self.realModel.item(rowNum, 6)),
                          QStandardItem(self.realModel.item(rowNum, 7)),
                          QStandardItem(self.realModel.item(rowNum, 8)),
                        #   QStandardItem(self.realModel.item(rowNum, 9)),
                          ]
                          
                self.realModel.appendRow(itemList)


            elif action == item2:
                self.realModel.removeRow(rowNum)
            else:
                return

    def load_impList(self,impFilePath):
        if os.path.exists(impFilePath):
            impf=open(impFilePath,'r')
        else:
            return
        self.rawImpList=[]
        impLineList=impf.readlines()
        impf.close()

        # impList=[]
        i=1
        
        for impLine in impLineList:
            tmpImpDict={}
            tmpImpDict['id']=i
            lineArr=impLine.strip().split(",")
            if lineArr[0] != "differential" and lineArr[0] != "single-ended":

                QMessageBox.information(self,u"info",u"File Format is not correct, please check!",QMessageBox.Ok)
                return
            for j in range(len(self.keyNameList)):
                value=lineArr[j]
                if value == "\\" or value == "0.00" or value=="0" or value=="0.0":
                    value=""
                    # if j <4 :
                    #     value=""
                    # else:
                    #     value='0'
                if units=="um":
                    tmpImpDict[self.keyNameList[j]]=value
                    if value!="":
                        if j==4 or j==5 or j==6 or j==7:
                            tmpImpDict[self.keyNameList[j]]=str(round(float(value)*25.4,1))
                else:
                    tmpImpDict[self.keyNameList[j]]=value
            # if tmpImpDict['req_spacing']=='0' and tmpImpDict['type'] == 'differential':
            #     tmpImpDict['req_spacing']=str(float(tmpImpDict['spacing'])-(float(tmpImpDict['req_line_width'])-float(tmpImpDict['line_width'])))
            self.rawImpList.append(tmpImpDict)
            i=i+1
        row=0
        self.realModel.clear()
        
        # self.realModel.setHorizontalHeaderLabels(["Type","Layer",u"top ref layer",'bot ref layer',u"line width",u"required line width",u"spacing",u"required spacing",u"coplanar Dist",u"imp Value"])
        self.realModel.setHorizontalHeaderLabels([u"类型",u"层",u"顶层参考层",u"底层参考层",u"线宽("+units+")",u"目标线宽("+units+")",u"间距("+units+")",u"目标间距("+units+")",u"阻值(Ω)"])
        for imp in self.rawImpList:
            # ['type','lyr','top_ref','bot_ref','line_width','req_line_width','spacing','req_spacing','imp_value']
            for j in range(len(self.keyNameList)):
                self.realModel.setItem(row,j,QStandardItem(imp[self.keyNameList[j]]))
            row = row + 1
        # print(self.realModel.rowCount())
        self.tableView_ImpList.reset() #Must add this reset even though model is cleaned.
        self.tableView_ImpList.setModel(self.realModel)

    def openParamWindow(self):
        #Correct format to create child window for main Qt window, and the child window should be QDialog
        self.ParamWindow = ParamWindow(self)
#         self.ParamWindow.setWindowTitle("Output Log")
        self.ParamWindow.show()
        return

    def exit(self):
        if os.path.exists(self.tmpDir):
            os.system("rm -rf %s"%(self.tmpDir))
        sys.exit()

    def closeEvent(self,event):
        # self.saveParam()
        if os.path.exists(self.tmpDir):
            os.system("rm -rf %s"%(self.tmpDir))
        sys.exit()

    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(931, 600)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.centralwidget)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.frame_2 = QtWidgets.QFrame(self.centralwidget)
        font = QtGui.QFont()
        font.setPointSize(11)
        self.frame_2.setFont(font)
        self.frame_2.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_2.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_2.setObjectName("frame_2")
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout(self.frame_2)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.frame = QtWidgets.QFrame(self.frame_2)
        self.frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame.setObjectName("frame")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.frame)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.label = QtWidgets.QLabel(self.frame)
        font = QtGui.QFont()
        font.setFamily("MS Shell Dlg 2")
        font.setPointSize(11)
        self.label.setFont(font)
        self.label.setObjectName("label")
        self.horizontalLayout.addWidget(self.label)
        self.lineEdit_ImpListFilePath = QtWidgets.QLineEdit(self.frame)
        self.lineEdit_ImpListFilePath.setObjectName("lineEdit_ImpListFilePath")
        self.horizontalLayout.addWidget(self.lineEdit_ImpListFilePath)
        self.pushButton_selectImpListFile = QtWidgets.QPushButton(self.frame)
        self.pushButton_selectImpListFile.setMaximumSize(QtCore.QSize(50, 16777215))
        self.pushButton_selectImpListFile.setObjectName("pushButton_selectImpListFile")
        self.horizontalLayout.addWidget(self.pushButton_selectImpListFile)
        self.horizontalLayout_2.addWidget(self.frame)
        spacerItem = QtWidgets.QSpacerItem(50, 20, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout_2.addItem(spacerItem)
        self.pushButton_param = QtWidgets.QPushButton(self.frame_2)
        font = QtGui.QFont()
        font.setFamily("MS Shell Dlg 2")
        font.setPointSize(11)
        self.pushButton_param.setFont(font)
        self.pushButton_param.setObjectName("pushButton_param")
        self.horizontalLayout_2.addWidget(self.pushButton_param)
        self.pushButton_createMiscLyr = QtWidgets.QPushButton(self.frame_2)
        font = QtGui.QFont()
        font.setFamily("MS Shell Dlg 2")
        font.setPointSize(11)
        self.pushButton_createMiscLyr.setFont(font)
        self.pushButton_createMiscLyr.setObjectName("pushButton_createMiscLyr")
        self.horizontalLayout_2.addWidget(self.pushButton_createMiscLyr)
        self.pushButton_pause = QtWidgets.QPushButton(self.frame_2)
        font = QtGui.QFont()
        font.setFamily("MS Shell Dlg 2")
        font.setPointSize(11)
        self.pushButton_pause.setFont(font)
        self.pushButton_pause.setObjectName("pushButton_pause")
        self.horizontalLayout_2.addWidget(self.pushButton_pause)
        self.verticalLayout_2.addWidget(self.frame_2)
        self.frame_3 = QtWidgets.QFrame(self.centralwidget)
        font = QtGui.QFont()
        font.setPointSize(11)
        self.frame_3.setFont(font)
        self.frame_3.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_3.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_3.setObjectName("frame_3")
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout(self.frame_3)
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.tableView_ImpList = QtWidgets.QTableView(self.frame_3)
        self.tableView_ImpList.setObjectName("tableView_ImpList")
        self.horizontalLayout_3.addWidget(self.tableView_ImpList)
        self.frame_4 = QtWidgets.QFrame(self.frame_3)
        self.frame_4.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_4.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_4.setObjectName("frame_4")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.frame_4)
        self.verticalLayout.setObjectName("verticalLayout")
        self.pushButton_saveImpList = QtWidgets.QPushButton(self.frame_4)
        font = QtGui.QFont()
        font.setFamily("MS Shell Dlg 2")
        font.setPointSize(11)
        self.pushButton_saveImpList.setFont(font)
        self.pushButton_saveImpList.setObjectName("pushButton_saveImpList")
        self.verticalLayout.addWidget(self.pushButton_saveImpList)
        self.pushButton_saveAsImpList = QtWidgets.QPushButton(self.frame_4)
        font = QtGui.QFont()
        font.setFamily("MS Shell Dlg 2")
        font.setPointSize(11)
        self.pushButton_saveAsImpList.setFont(font)
        self.pushButton_saveAsImpList.setObjectName("pushButton_saveAsImpList")
        self.verticalLayout.addWidget(self.pushButton_saveAsImpList)
        self.pushButton_addImp = QtWidgets.QPushButton(self.frame_4)
        self.pushButton_addImp.setObjectName("pushButton_addImp")
        self.verticalLayout.addWidget(self.pushButton_addImp)
        spacerItem1 = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.verticalLayout.addItem(spacerItem1)
        self.horizontalLayout_3.addWidget(self.frame_4)
        self.verticalLayout_2.addWidget(self.frame_3)
        self.frame_5 = QtWidgets.QFrame(self.centralwidget)
        font = QtGui.QFont()
        font.setPointSize(11)
        self.frame_5.setFont(font)
        self.frame_5.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_5.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_5.setObjectName("frame_5")
        self.horizontalLayout_4 = QtWidgets.QHBoxLayout(self.frame_5)
        self.horizontalLayout_4.setObjectName("horizontalLayout_4")
        spacerItem2 = QtWidgets.QSpacerItem(450, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout_4.addItem(spacerItem2)
        self.pushButton_ILR = QtWidgets.QPushButton(self.frame_5)
        font = QtGui.QFont()
        font.setFamily("MS Shell Dlg 2")
        font.setPointSize(11)
        self.pushButton_ILR.setFont(font)
        self.pushButton_ILR.setObjectName("pushButton_ILR")
        self.horizontalLayout_4.addWidget(self.pushButton_ILR)
        self.pushButton_createTP = QtWidgets.QPushButton(self.frame_5)
        font = QtGui.QFont()
        font.setFamily("MS Shell Dlg 2")
        font.setPointSize(11)
        self.pushButton_createTP.setFont(font)
        self.pushButton_createTP.setObjectName("pushButton_createTP")
        self.horizontalLayout_4.addWidget(self.pushButton_createTP)
        self.pushButton_createTPReport = QtWidgets.QPushButton(self.frame_5)
        font = QtGui.QFont()
        font.setFamily("MS Shell Dlg 2")
        font.setPointSize(11)
        self.pushButton_createTPReport.setFont(font)
        self.pushButton_createTPReport.setObjectName("pushButton_createTPReport")
        self.horizontalLayout_4.addWidget(self.pushButton_createTPReport)
        self.pushButton_ILA = QtWidgets.QPushButton(self.frame_5)
        font = QtGui.QFont()
        font.setFamily("MS Shell Dlg 2")
        font.setPointSize(11)
        self.pushButton_ILA.setFont(font)
        self.pushButton_ILA.setObjectName("pushButton_ILA")
        self.horizontalLayout_4.addWidget(self.pushButton_ILA)
        self.pushButton_exit = QtWidgets.QPushButton(self.frame_5)
        font = QtGui.QFont()
        font.setFamily("MS Shell Dlg 2")
        font.setPointSize(11)
        self.pushButton_exit.setFont(font)
        self.pushButton_exit.setObjectName("pushButton_exit")
        self.horizontalLayout_4.addWidget(self.pushButton_exit)
        self.verticalLayout_2.addWidget(self.frame_5)
        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.actionHelp = QtWidgets.QAction(MainWindow)
        self.actionHelp.setObjectName("actionHelp")
        self.actionExit = QtWidgets.QAction(MainWindow)
        self.actionExit.setObjectName("actionExit")

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "阻抗处理"))
        self.label.setText(_translate("MainWindow", "阻抗表路径:"))
        self.pushButton_selectImpListFile.setText(_translate("MainWindow", "..."))
        self.pushButton_param.setText(_translate("MainWindow", "参数"))
        self.pushButton_createMiscLyr.setText(_translate("MainWindow", "创建阻抗辅助层"))
        self.pushButton_pause.setText(_translate("MainWindow", "PAUSE"))
        self.pushButton_saveImpList.setText(_translate("MainWindow", "保存阻抗表"))
        self.pushButton_saveAsImpList.setText(_translate("MainWindow", "另存阻抗表"))
        self.pushButton_addImp.setText(_translate("MainWindow", "添加阻抗线"))
        self.pushButton_ILR.setText(_translate("MainWindow", "自动识别阻抗线"))
        self.pushButton_createTP.setText(_translate("MainWindow", "生成外层测点"))
        self.pushButton_createTPReport.setText(_translate("MainWindow", "生成测点报告"))
        self.pushButton_ILA.setText(_translate("MainWindow", "调整阻抗线(线宽/线距)"))
        self.pushButton_exit.setText(_translate("MainWindow", "退出"))
        self.actionHelp.setText(_translate("MainWindow", "Help"))
        self.actionExit.setText(_translate("MainWindow", "Exit"))


class ParamWindow(QtWidgets.QDialog):
    global paramDict
    global units,bigunits
    global unitValueList
    def __init__(self, parent=None):
        super(ParamWindow, self).__init__(parent)
        self.parent=parent
        self.setupUi(self)


# class ParamWindow(QtWidgets.QDialog,Ui_MainWindow_Param):
#     global paramDict
#     def __init__(self, parent=None):
#         super(ParamWindow, self).__init__(parent)
#         #must define self.parent, so that class functions can use parent later
#         self.parent=parent
#         self.setupUi(self)

        # self.setMinimumSize(QtCore.QSize(900, 400))
        self.setWindowTitle("Setup Parameters")

        self.setParams()
        self.pushButton_selectReportDir.clicked.connect(self.pushButton_selectReportDir_clicked)
        for lineEdit in self.scrollArea.findChildren(QtWidgets.QLineEdit):
            lineEdit.returnPressed.connect(self.lineEditReturnPressed)
            lineEdit.editingFinished.connect(self.lineEditReturnPressed)
        
        self.checkBox_need_shortest.stateChanged.connect(self.checkBoxStateChange)
        self.checkBox_need_middle.stateChanged.connect(self.checkBoxStateChange)


    def close(self):
        # self.saveParameters()
        self.setParent(None)
        self.deleteLater()
        return super(ParamWindow, self).close()

    def closeEvent(self,event):
        pass
        # self.saveParameters()

    def pushButton_selectReportDir_clicked(self):
        directory = QFileDialog.getExistingDirectory(self,"Select Directory","")
        # param = str(directory).replace("\\","/")
        param = directory.replace("\\","/")
        # param = directory
        self.lineEdit_rep_path.setText(param)

    def setParams(self):
        #keyName is same as the json keys
        for keyName in paramDict.keys():
            
            if keyName == "need_shortest" or keyName == "need_middle":
                widgetName="checkBox_"+keyName
                if paramDict[keyName] == "yes":
                    vars(self)[widgetName].setChecked(True)
            elif keyName == "units":
                widgetName="comboBox_"+keyName
                if paramDict[keyName] == "mm":
                    vars(self)[widgetName].setCurrentIndex(0)
                else:
                    vars(self)[widgetName].setCurrentIndex(1)


            else:
                widgetName="lineEdit_"+keyName
                if units=="um":
                    if keyName in unitValueList:
                        vars(self)[widgetName].setText(str(round(float(paramDict[keyName])*25.4,1)))
                    else:
                        vars(self)[widgetName].setText(paramDict[keyName])
                else:
                    vars(self)[widgetName].setText(paramDict[keyName])
        self.lineEdit_rep_filename.setText(jobName)
        paramDict['rep_filename']=jobName
        self.groupBox_ila.hide()

    def lineEditReturnPressed(self):
        sender=self.sender()
        senderName=sender.objectName().__str__()
        senderNameList=senderName.split("_",1)
        keyName=senderNameList[1]
        curText=sender.text()

        #all widget name is same as json parameter names
        paramDict[keyName]=curText
        if paramDict['units']=="mm":
            if keyName in unitValueList:
                paramDict[keyName]=str(round(float(curText)/25.4,3))


    def checkBoxStateChange(self):
        sender=self.sender()
        senderName=sender.objectName().__str__()
        senderNameList=senderName.split("_",1)
        keyName=senderNameList[1]

        if sender.isChecked():
            paramDict[keyName]="yes"
        else:
            paramDict[keyName]="no"

    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(732, 826)
        self.gridLayout = QtWidgets.QGridLayout(Dialog)
        self.gridLayout.setObjectName("gridLayout")
        self.scrollArea = QtWidgets.QScrollArea(Dialog)
        self.scrollArea.setWidgetResizable(True)
        self.scrollArea.setObjectName("scrollArea")
        self.scrollAreaWidgetContents = QtWidgets.QWidget()
        self.scrollAreaWidgetContents.setGeometry(QtCore.QRect(0, 0, 687, 1158))
        self.scrollAreaWidgetContents.setObjectName("scrollAreaWidgetContents")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.scrollAreaWidgetContents)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.frame_18 = QtWidgets.QFrame(self.scrollAreaWidgetContents)
        font = QtGui.QFont()
        font.setPointSize(10)
        self.frame_18.setFont(font)
        self.frame_18.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_18.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_18.setObjectName("frame_18")
        self.horizontalLayout_17 = QtWidgets.QHBoxLayout(self.frame_18)
        self.horizontalLayout_17.setObjectName("horizontalLayout_17")
        self.label_17 = QtWidgets.QLabel(self.frame_18)
        self.label_17.setObjectName("label_17")
        self.horizontalLayout_17.addWidget(self.label_17)
        self.comboBox_units = QtWidgets.QComboBox(self.frame_18)
        self.comboBox_units.setMinimumSize(QtCore.QSize(60, 0))
        self.comboBox_units.setObjectName("comboBox_units")
        self.comboBox_units.addItem("mm")
        self.comboBox_units.addItem("inch")
        self.comboBox_units.setDisabled(True)
        self.horizontalLayout_17.addWidget(self.comboBox_units)
        spacerItem = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout_17.addItem(spacerItem)
        self.verticalLayout_2.addWidget(self.frame_18)
        self.groupBox_ilr = QtWidgets.QGroupBox(self.scrollAreaWidgetContents)
        font = QtGui.QFont()
        font.setFamily("MS Shell Dlg 2")
        font.setPointSize(10)
        self.groupBox_ilr.setFont(font)
        self.groupBox_ilr.setObjectName("groupBox_ilr")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.groupBox_ilr)
        self.verticalLayout.setObjectName("verticalLayout")
        self.frame = QtWidgets.QFrame(self.groupBox_ilr)
        self.frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame.setObjectName("frame")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.frame)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.label = QtWidgets.QLabel(self.frame)
        self.label.setObjectName("label")
        self.horizontalLayout.addWidget(self.label)
        self.lineEdit_diff_min_len = QtWidgets.QLineEdit(self.frame)
        self.lineEdit_diff_min_len.setObjectName("lineEdit_diff_min_len")
        self.horizontalLayout.addWidget(self.lineEdit_diff_min_len)
        self.verticalLayout.addWidget(self.frame)
        self.frame_2 = QtWidgets.QFrame(self.groupBox_ilr)
        self.frame_2.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_2.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_2.setObjectName("frame_2")
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout(self.frame_2)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.label_2 = QtWidgets.QLabel(self.frame_2)
        self.label_2.setObjectName("label_2")
        self.horizontalLayout_2.addWidget(self.label_2)
        self.lineEdit_min_diff_percent = QtWidgets.QLineEdit(self.frame_2)
        self.lineEdit_min_diff_percent.setObjectName("lineEdit_min_diff_percent")
        self.horizontalLayout_2.addWidget(self.lineEdit_min_diff_percent)
        self.verticalLayout.addWidget(self.frame_2)
        self.frame_3 = QtWidgets.QFrame(self.groupBox_ilr)
        self.frame_3.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_3.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_3.setObjectName("frame_3")
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout(self.frame_3)
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.label_3 = QtWidgets.QLabel(self.frame_3)
        self.label_3.setObjectName("label_3")
        self.horizontalLayout_3.addWidget(self.label_3)
        self.lineEdit_trace_width_tol = QtWidgets.QLineEdit(self.frame_3)
        self.lineEdit_trace_width_tol.setObjectName("lineEdit_trace_width_tol")
        self.horizontalLayout_3.addWidget(self.lineEdit_trace_width_tol)
        self.verticalLayout.addWidget(self.frame_3)
        self.frame_4 = QtWidgets.QFrame(self.groupBox_ilr)
        self.frame_4.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_4.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_4.setObjectName("frame_4")
        self.horizontalLayout_4 = QtWidgets.QHBoxLayout(self.frame_4)
        self.horizontalLayout_4.setObjectName("horizontalLayout_4")
        self.label_4 = QtWidgets.QLabel(self.frame_4)
        self.label_4.setObjectName("label_4")
        self.horizontalLayout_4.addWidget(self.label_4)
        self.lineEdit_spacing_tol = QtWidgets.QLineEdit(self.frame_4)
        self.lineEdit_spacing_tol.setObjectName("lineEdit_spacing_tol")
        self.horizontalLayout_4.addWidget(self.lineEdit_spacing_tol)
        self.verticalLayout.addWidget(self.frame_4)
        self.verticalLayout_2.addWidget(self.groupBox_ilr)
        self.groupBox_tp = QtWidgets.QGroupBox(self.scrollAreaWidgetContents)
        font = QtGui.QFont()
        font.setFamily("MS Shell Dlg 2")
        font.setPointSize(10)
        self.groupBox_tp.setFont(font)
        self.groupBox_tp.setObjectName("groupBox_tp")
        self.gridLayout_3 = QtWidgets.QGridLayout(self.groupBox_tp)
        self.gridLayout_3.setObjectName("gridLayout_3")
        self.frame_5 = QtWidgets.QFrame(self.groupBox_tp)
        self.frame_5.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_5.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_5.setObjectName("frame_5")
        self.horizontalLayout_5 = QtWidgets.QHBoxLayout(self.frame_5)
        self.horizontalLayout_5.setObjectName("horizontalLayout_5")
        self.label_5 = QtWidgets.QLabel(self.frame_5)
        self.label_5.setObjectName("label_5")
        self.horizontalLayout_5.addWidget(self.label_5)
        self.lineEdit_tp_imp_min_len = QtWidgets.QLineEdit(self.frame_5)
        self.lineEdit_tp_imp_min_len.setObjectName("lineEdit_tp_imp_min_len")
        self.horizontalLayout_5.addWidget(self.lineEdit_tp_imp_min_len)
        self.gridLayout_3.addWidget(self.frame_5, 0, 0, 1, 2)
        self.frame_9 = QtWidgets.QFrame(self.groupBox_tp)
        self.frame_9.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_9.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_9.setObjectName("frame_9")
        self.horizontalLayout_9 = QtWidgets.QHBoxLayout(self.frame_9)
        self.horizontalLayout_9.setObjectName("horizontalLayout_9")
        self.label_9 = QtWidgets.QLabel(self.frame_9)
        self.label_9.setObjectName("label_9")
        self.horizontalLayout_9.addWidget(self.label_9)
        self.lineEdit_tp_min_coverage_percent = QtWidgets.QLineEdit(self.frame_9)
        self.lineEdit_tp_min_coverage_percent.setObjectName("lineEdit_tp_min_coverage_percent")
        self.horizontalLayout_9.addWidget(self.lineEdit_tp_min_coverage_percent)
        self.gridLayout_3.addWidget(self.frame_9, 0, 2, 1, 1)
        self.frame_7 = QtWidgets.QFrame(self.groupBox_tp)
        self.frame_7.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_7.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_7.setObjectName("frame_7")
        self.horizontalLayout_7 = QtWidgets.QHBoxLayout(self.frame_7)
        self.horizontalLayout_7.setObjectName("horizontalLayout_7")
        self.label_7 = QtWidgets.QLabel(self.frame_7)
        self.label_7.setObjectName("label_7")
        self.horizontalLayout_7.addWidget(self.label_7)
        self.lineEdit_tp_pgpad_max_dist = QtWidgets.QLineEdit(self.frame_7)
        self.lineEdit_tp_pgpad_max_dist.setObjectName("lineEdit_tp_pgpad_max_dist")
        self.horizontalLayout_7.addWidget(self.lineEdit_tp_pgpad_max_dist)
        self.gridLayout_3.addWidget(self.frame_7, 2, 0, 1, 3)
        self.checkBox_need_shortest = QtWidgets.QCheckBox(self.groupBox_tp)
        self.checkBox_need_shortest.setObjectName("checkBox_need_shortest")
        self.gridLayout_3.addWidget(self.checkBox_need_shortest, 5, 0, 1, 1)
        self.checkBox_need_middle = QtWidgets.QCheckBox(self.groupBox_tp)
        self.checkBox_need_middle.setObjectName("checkBox_need_middle")
        self.gridLayout_3.addWidget(self.checkBox_need_middle, 5, 2, 1, 1)
        self.frame_14 = QtWidgets.QFrame(self.groupBox_tp)
        self.frame_14.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_14.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_14.setObjectName("frame_14")
        self.horizontalLayout_14 = QtWidgets.QHBoxLayout(self.frame_14)
        self.horizontalLayout_14.setObjectName("horizontalLayout_14")
        self.label_14 = QtWidgets.QLabel(self.frame_14)
        self.label_14.setObjectName("label_14")
        self.horizontalLayout_14.addWidget(self.label_14)
        self.lineEdit_tp_max_width = QtWidgets.QLineEdit(self.frame_14)
        self.lineEdit_tp_max_width.setObjectName("lineEdit_tp_max_width")
        self.horizontalLayout_14.addWidget(self.lineEdit_tp_max_width)
        self.gridLayout_3.addWidget(self.frame_14, 4, 0, 1, 3)
        self.frame_8 = QtWidgets.QFrame(self.groupBox_tp)
        self.frame_8.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_8.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_8.setObjectName("frame_8")
        self.horizontalLayout_8 = QtWidgets.QHBoxLayout(self.frame_8)
        self.horizontalLayout_8.setObjectName("horizontalLayout_8")
        self.label_8 = QtWidgets.QLabel(self.frame_8)
        self.label_8.setObjectName("label_8")
        self.horizontalLayout_8.addWidget(self.label_8)
        self.lineEdit_tp_min_width = QtWidgets.QLineEdit(self.frame_8)
        self.lineEdit_tp_min_width.setObjectName("lineEdit_tp_min_width")
        self.horizontalLayout_8.addWidget(self.lineEdit_tp_min_width)
        self.gridLayout_3.addWidget(self.frame_8, 3, 0, 1, 3)
        self.frame_6 = QtWidgets.QFrame(self.groupBox_tp)
        self.frame_6.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_6.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_6.setObjectName("frame_6")
        self.horizontalLayout_6 = QtWidgets.QHBoxLayout(self.frame_6)
        self.horizontalLayout_6.setObjectName("horizontalLayout_6")
        self.label_6 = QtWidgets.QLabel(self.frame_6)
        self.label_6.setObjectName("label_6")
        self.horizontalLayout_6.addWidget(self.label_6)
        self.lineEdit_tp_num = QtWidgets.QLineEdit(self.frame_6)
        self.lineEdit_tp_num.setObjectName("lineEdit_tp_num")
        self.horizontalLayout_6.addWidget(self.lineEdit_tp_num)
        self.gridLayout_3.addWidget(self.frame_6, 1, 0, 1, 3)
        self.verticalLayout_2.addWidget(self.groupBox_tp)
        self.groupBox_report = QtWidgets.QGroupBox(self.scrollAreaWidgetContents)
        font = QtGui.QFont()
        font.setFamily("MS Shell Dlg 2")
        font.setPointSize(10)
        self.groupBox_report.setFont(font)
        self.groupBox_report.setObjectName("groupBox_report")
        self.gridLayout_2 = QtWidgets.QGridLayout(self.groupBox_report)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.frame_15 = QtWidgets.QFrame(self.groupBox_report)
        self.frame_15.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_15.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_15.setObjectName("frame_15")
        self.horizontalLayout_15 = QtWidgets.QHBoxLayout(self.frame_15)
        self.horizontalLayout_15.setObjectName("horizontalLayout_15")
        self.label_15 = QtWidgets.QLabel(self.frame_15)
        self.label_15.setObjectName("label_15")
        self.horizontalLayout_15.addWidget(self.label_15)
        self.lineEdit_rep_prefix = QtWidgets.QLineEdit(self.frame_15)
        self.lineEdit_rep_prefix.setObjectName("lineEdit_rep_prefix")
        self.horizontalLayout_15.addWidget(self.lineEdit_rep_prefix)
        self.gridLayout_2.addWidget(self.frame_15, 2, 0, 1, 1)
        self.frame_16 = QtWidgets.QFrame(self.groupBox_report)
        self.frame_16.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_16.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_16.setObjectName("frame_16")
        self.horizontalLayout_16 = QtWidgets.QHBoxLayout(self.frame_16)
        self.horizontalLayout_16.setObjectName("horizontalLayout_16")
        self.label_16 = QtWidgets.QLabel(self.frame_16)
        self.label_16.setObjectName("label_16")
        self.horizontalLayout_16.addWidget(self.label_16)
        self.lineEdit_rep_suffix = QtWidgets.QLineEdit(self.frame_16)
        self.lineEdit_rep_suffix.setObjectName("lineEdit_rep_suffix")
        self.horizontalLayout_16.addWidget(self.lineEdit_rep_suffix)
        self.gridLayout_2.addWidget(self.frame_16, 2, 1, 1, 1)
        self.frame_13 = QtWidgets.QFrame(self.groupBox_report)
        self.frame_13.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_13.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_13.setObjectName("frame_13")
        self.horizontalLayout_13 = QtWidgets.QHBoxLayout(self.frame_13)
        self.horizontalLayout_13.setObjectName("horizontalLayout_13")
        self.label_13 = QtWidgets.QLabel(self.frame_13)
        self.label_13.setObjectName("label_13")
        self.horizontalLayout_13.addWidget(self.label_13)
        self.lineEdit_rep_path = QtWidgets.QLineEdit(self.frame_13)
        self.lineEdit_rep_path.setObjectName("lineEdit_rep_path")
        self.horizontalLayout_13.addWidget(self.lineEdit_rep_path)
        self.pushButton_selectReportDir = QtWidgets.QPushButton(self.frame_13)
        self.pushButton_selectReportDir.setMaximumSize(QtCore.QSize(50, 16777215))
        self.pushButton_selectReportDir.setObjectName("pushButton_selectReportDir")
        self.horizontalLayout_13.addWidget(self.pushButton_selectReportDir)
        self.gridLayout_2.addWidget(self.frame_13, 0, 0, 1, 2)
        self.frame_17 = QtWidgets.QFrame(self.groupBox_report)
        self.frame_17.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_17.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_17.setObjectName("frame_17")
        self.horizontalLayout_18 = QtWidgets.QHBoxLayout(self.frame_17)
        self.horizontalLayout_18.setObjectName("horizontalLayout_18")
        self.label_18 = QtWidgets.QLabel(self.frame_17)
        self.label_18.setObjectName("label_18")
        self.horizontalLayout_18.addWidget(self.label_18)
        self.lineEdit_rep_filename = QtWidgets.QLineEdit(self.frame_17)
        self.lineEdit_rep_filename.setObjectName("lineEdit_rep_filename")
        self.horizontalLayout_18.addWidget(self.lineEdit_rep_filename)
        self.gridLayout_2.addWidget(self.frame_17, 1, 0, 1, 2)
        self.verticalLayout_2.addWidget(self.groupBox_report)
        self.groupBox_ila = QtWidgets.QGroupBox(self.scrollAreaWidgetContents)
        font = QtGui.QFont()
        font.setFamily("MS Shell Dlg 2")
        font.setPointSize(10)
        self.groupBox_ila.setFont(font)
        self.groupBox_ila.setObjectName("groupBox_ila")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout(self.groupBox_ila)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.frame_10 = QtWidgets.QFrame(self.groupBox_ila)
        self.frame_10.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_10.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_10.setObjectName("frame_10")
        self.horizontalLayout_10 = QtWidgets.QHBoxLayout(self.frame_10)
        self.horizontalLayout_10.setObjectName("horizontalLayout_10")
        self.label_10 = QtWidgets.QLabel(self.frame_10)
        self.label_10.setObjectName("label_10")
        self.horizontalLayout_10.addWidget(self.label_10)
        self.lineEdit_ila_min_cu_dist = QtWidgets.QLineEdit(self.frame_10)
        self.lineEdit_ila_min_cu_dist.setObjectName("lineEdit_ila_min_cu_dist")
        self.horizontalLayout_10.addWidget(self.lineEdit_ila_min_cu_dist)
        self.verticalLayout_3.addWidget(self.frame_10)
        self.frame_11 = QtWidgets.QFrame(self.groupBox_ila)
        self.frame_11.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_11.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_11.setObjectName("frame_11")
        self.horizontalLayout_11 = QtWidgets.QHBoxLayout(self.frame_11)
        self.horizontalLayout_11.setObjectName("horizontalLayout_11")
        self.label_11 = QtWidgets.QLabel(self.frame_11)
        self.label_11.setObjectName("label_11")
        self.horizontalLayout_11.addWidget(self.label_11)
        self.lineEdit_ila_min_drill_dist = QtWidgets.QLineEdit(self.frame_11)
        self.lineEdit_ila_min_drill_dist.setObjectName("lineEdit_ila_min_drill_dist")
        self.horizontalLayout_11.addWidget(self.lineEdit_ila_min_drill_dist)
        self.verticalLayout_3.addWidget(self.frame_11)
        self.frame_12 = QtWidgets.QFrame(self.groupBox_ila)
        self.frame_12.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_12.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_12.setObjectName("frame_12")
        self.horizontalLayout_12 = QtWidgets.QHBoxLayout(self.frame_12)
        self.horizontalLayout_12.setObjectName("horizontalLayout_12")
        self.label_12 = QtWidgets.QLabel(self.frame_12)
        self.label_12.setObjectName("label_12")
        self.horizontalLayout_12.addWidget(self.label_12)
        self.lineEdit_ila_spacing_search_dist = QtWidgets.QLineEdit(self.frame_12)
        self.lineEdit_ila_spacing_search_dist.setObjectName("lineEdit_ila_spacing_search_dist")
        self.horizontalLayout_12.addWidget(self.lineEdit_ila_spacing_search_dist)
        self.verticalLayout_3.addWidget(self.frame_12)
        self.verticalLayout_2.addWidget(self.groupBox_ila)
        self.scrollArea.setWidget(self.scrollAreaWidgetContents)
        self.gridLayout.addWidget(self.scrollArea, 0, 0, 1, 1)

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "Dialog"))
        self.label_17.setText(_translate("Dialog", "单位："))
        self.groupBox_ilr.setTitle(_translate("Dialog", "阻抗线识别参数"))
        self.label.setText(_translate("Dialog", "差分阻抗最短长度("+units+"):"))
        self.lineEdit_diff_min_len.setToolTip(_translate("Dialog", "小于此数值长度的线路不会被识别为差分阻抗线"))
        self.label_2.setText(_translate("Dialog", "差分阻抗两线最小相似度(%):"))
        self.lineEdit_min_diff_percent.setToolTip(_translate("Dialog", "差分阻抗线2条线段长度百分比，小于此数值不会被识别为差分阻抗线"))
        self.label_3.setText(_translate("Dialog", "线宽最大差异("+units+"):"))
        self.lineEdit_trace_width_tol.setToolTip(_translate("Dialog", "阻抗线线宽误差，大于或小于此误差值不会识别为对应类型阻抗线"))
        self.label_4.setText(_translate("Dialog", "线距最大差异("+units+"):"))
        self.lineEdit_spacing_tol.setToolTip(_translate("Dialog", "差分阻抗线线距误差，小于或大于此误差值不会被识别为对应类型差分阻抗线"))
        self.groupBox_tp.setTitle(_translate("Dialog", "外层测点生成参数"))
        self.label_5.setText(_translate("Dialog", "测试阻抗线最小长度("+bigunits+"):"))
        self.lineEdit_tp_imp_min_len.setToolTip(_translate("Dialog", "用于生成测点的阻抗线长度最小值，小于此数值不会用来生成外层测点"))
        self.label_9.setText(_translate("Dialog", "参考层最小覆盖率(%):"))
        self.label_7.setText(_translate("Dialog", "单端阻抗接地测点距目标测点最大距离("+units+"):"))
        self.checkBox_need_shortest.setText(_translate("Dialog", "需识别最短线"))
        self.checkBox_need_middle.setText(_translate("Dialog", "需识别中值线"))
        self.label_14.setText(_translate("Dialog", "测点pad短边最大长度("+units+"):"))
        self.label_8.setText(_translate("Dialog", "测点pad短边最小长度("+units+"):"))
        self.label_6.setText(_translate("Dialog", "每类阻抗线测点组数量:"))
        self.lineEdit_tp_num.setToolTip(_translate("Dialog", "每类阻抗线需产生外层测点对数量"))
        self.groupBox_report.setTitle(_translate("Dialog", "测点报告生成参数"))
        self.label_15.setText(_translate("Dialog", "报告文件名前缀:"))
        self.label_16.setText(_translate("Dialog", "报告文件名后缀:"))
        self.label_13.setText(_translate("Dialog", "报告输出路径:"))
        self.pushButton_selectReportDir.setText(_translate("Dialog", "..."))
        self.label_18.setText(_translate("Dialog", "报告文件名:"))
        self.groupBox_ila.setTitle(_translate("Dialog", "阻抗线调整参数"))
        self.label_10.setText(_translate("Dialog", "最小线路距离("+units+"):"))
        self.label_11.setText(_translate("Dialog", "最小钻孔距离("+units+"):"))
        self.label_12.setText(_translate("Dialog", "间距额外识别距离("+units+"):"))
        self.lineEdit_ila_spacing_search_dist.setToolTip(_translate("Dialog", "如果某差分阻抗线间距大于设置距离+此数值，不会移动线路到目标间距"))


if __name__ == "__main__":
#     # app = QtGui.QApplication(sys.argv)
#     # window = MyApp()
#     # window.show()
#     # window.move((QtGui.QApplication.desktop().width() - window.width())/2,(QtGui.QApplication.desktop().height() - window.height())/2)
#     # sys.exit(app.exec_())

    app = QtWidgets.QApplication(sys.argv)
    window = MyApp()
    window.show()
    window.move((QtWidgets.QApplication.desktop().width() - window.width())/2,(QtWidgets.QApplication.desktop().height() - window.height())/2)
    sys.exit(app.exec_())