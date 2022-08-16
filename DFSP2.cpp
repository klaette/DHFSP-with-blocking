#include <tchar.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>  
#include <conio.h>  
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "limits.h"
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <numeric>
#include <vector>
#include<iomanip>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include<random>
#include<ctime>
#pragma once
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)

using namespace std;
#include "com.h"
#include "NEH.h"
#include "DABC.h"
#include "IG.h"
#include "GA.h"
#include "EMBO.h"
//#include "IGM.h"
//#include "EA.h"
#include "CRO.h"
//#include "SS.h"
//#include "IG_Swap.h"
//#include "IG_LXP.h"
//#include "VIG.h"
//#include "DDE.h"
//#include "PSO.h"
#include "MN_IG.h"
#include "IG_BLOCK.h"
//#include "IGM.h"
//#include "Calibration.h"
//#include "RunIns.h"
//#include "IG_new.h"

#define _CRT_SECURE_NO_WARNINGS

void main()
{
    for (int Counter = 2; Counter < 3; Counter++)
    {
        int CPU = 10;
        // int CPU = 10 * Counter;
        int Psize = 20;
        float Mcoefficien = 0.0;
        float Crossovercoefficient = 0.1;
        float Selectcoefficient = 0.0;
        int Iter = 4000;
        int nochange = 10;
        int blenway = 3;


        cout << "Test_CPU=" << CPU << endl;

        vector<vector<int>>SpanFactory_DABC;
        SpanFactory_DABC.resize(270);
        for (int ins = 0; ins < SpanFactory_DABC.size(); ins++)
            SpanFactory_DABC[ins].resize(30, 0);

        vector<vector<int>>SpanFactory_CRO;
        SpanFactory_CRO.resize(270);
        for (int ins = 0; ins < SpanFactory_CRO.size(); ins++)
            SpanFactory_CRO[ins].resize(30, 0);

      /*  vector<vector<int>>SpanFactory_DDE;
        SpanFactory_DDE.resize(270);
        for (int ins = 0; ins < SpanFactory_DDE.size(); ins++)
            SpanFactory_DDE[ins].resize(5, 0);*/

        vector<vector<int>>SpanFactory_IG;
        SpanFactory_IG.resize(270);
        for (int ins = 0; ins < SpanFactory_IG.size(); ins++)
            SpanFactory_IG[ins].resize(30, 0);

        vector<vector<int>>SpanFactory_PSO;
        SpanFactory_PSO.resize(270);
        for (int ins = 0; ins < SpanFactory_PSO.size(); ins++)
            SpanFactory_PSO[ins].resize(30, 0);

        vector<vector<int>>SpanFactory_GA;
        SpanFactory_GA.resize(270);
        for (int ins = 0; ins < SpanFactory_GA.size(); ins++)
            SpanFactory_GA[ins].resize(30, 0);

        vector<vector<int>>SpanFactory_EMBO;
        SpanFactory_EMBO.resize(270);
        for (int ins = 0; ins < SpanFactory_EMBO.size(); ins++)
            SpanFactory_EMBO[ins].resize(30, 0);

        vector<vector<int>>SpanFactory_MN_IG;
        SpanFactory_MN_IG.resize(270);
        for (int ins = 0; ins < SpanFactory_MN_IG.size(); ins++)
            SpanFactory_MN_IG[ins].resize(30, 0);

        vector<vector<int>>SpanFactory_IG_BLOCK;
        SpanFactory_IG_BLOCK.resize(270);
        for (int ins = 0; ins < SpanFactory_IG_BLOCK.size(); ins++)
            SpanFactory_IG_BLOCK[ins].resize(30, 0);

        vector<vector<int>>SpanFactory_EA;
        SpanFactory_EA.resize(270);
        for (int ins = 0; ins < SpanFactory_EA.size(); ins++)
            SpanFactory_EA[ins].resize(30, 0);

        string FileDirectory = "Result\\";    //
        ostringstream str;
        str << "Test_Algorithms_cpu=" << CPU << ".txt";    //不同的算法
        ofstream ofile;
        ofile.open(FileDirectory + str.str());

        char fileName1[30];
        FILE* f1;
        sprintf(fileName1, "RPI_H.txt");
        f1 = fopen(fileName1, "a+");
        

        for (int Ins = 90; Ins < 91; Ins++)
        {
            Read(Ins);
            cout << "工件：" << gJobs << " 阶段：" << InStage << " 工厂：" << gFactory << endl;
           
            long TimeLimit = CPU * gJobs * InStage;

            double min_DABC = INT_MAX;
            double min_CRO = INT_MAX;
            double min_DDE = INT_MAX;
            double min_IG = INT_MAX;
            double min_PSO = INT_MAX;
            double min_GA = INT_MAX;
            double min_EMBO = INT_MAX;
            double min_MN_IG = INT_MAX;
            double min_IG_BLOCK = INT_MAX;
            double min_EA = INT_MAX;

            double min_IGM = INT_MAX;
            double min_IGN = INT_MAX;
            double min_span = INT_MAX;

            vector<double> RPI;
            RPI.resize(12);


           //cout << "DABC:";
           // cout << endl;
          
           // 
          
           //  ofile << "DABC" << "\n";
           // 
           // for (int i = 0; i < 1; i++)        //每个测试用例执行30遍
           // {
           //     srand(i + 100 + Ins);
           //     //SpanFactory[Ins][i] = GA(TimeLimit, Psize);
           //     SpanFactory_DABC[Ins][i] = DABC_Compared(TimeLimit, 18, 3);
           //     DABC_Compared_Curve(TimeLimit, 18, 3,0,0,Ins);
           //     //SpanFactory[Ins][i] = HDDE(TimeLimit, Psize, Mcoefficien, Crossovercoefficient, Selectcoefficient, Iter);   //不同的算法
           //     ofile << SpanFactory_DABC[Ins][i] << "\t";
           //     //cout << SpanFactory_DABC[Ins][i] << "\t";

           //     if (SpanFactory_DABC[Ins][i] < min_DABC)
           //         min_DABC = SpanFactory_DABC[Ins][i];
           //     if (min_DABC < min_span)
           //         min_span = min_DABC;
           // }

           //
           // //cout << endl;

            cout << "CRO:";
            cout << endl;
            ofile << "\n";
            ofile << "CRO" << "\n";
            for (int i = 0; i < 1; i++)        //每个测试用例执行5遍
            {
                srand(i + 100 + Ins);
                //SpanFactory[Ins][i] = GA(TimeLimit, Psize);
                //SpanFactory_CRO[Ins][i] = CRO(TimeLimit, 150, 0.7, 10, 50);
                CRO_Compared_Curve(TimeLimit, 150, 0.7, 10, 50, 0, 0, Ins);
                //SpanFactory[Ins][i] = HDDE(TimeLimit, Psize, Mcoefficien, Crossovercoefficient, Selectcoefficient, Iter);   //不同的算法
                ofile << SpanFactory_CRO[Ins][i] << "\t";
                // cout << SpanFactory_CRO[Ins][i] << "\t";

                if (SpanFactory_CRO[Ins][i] < min_CRO)
                    min_CRO = SpanFactory_CRO[Ins][i];
                if (min_CRO < min_span)
                    min_span = min_CRO;

            }
           // // cout << endl;

           ////  //cout << "DDE:";
           //// // cout << endl;
           // //ofile << "\n";
           // //ofile << "DDE" << "\n";
           // //for (int i = 0; i < 5; i++)        //每个测试用例执行5遍
           // //{
           // //    srand(i + 100 + Ins);
           // //    //SpanFactory[Ins][i] = GA(TimeLimit, Psize);
           // //    //SpanFactory_IG[Ins][i] = IG_Compared(TimeLimit, Psize, Mcoefficien);
           // //    SpanFactory_DDE[Ins][i] = DDE(TimeLimit, Psize, Mcoefficien, Crossovercoefficient, Selectcoefficient, Iter);   //不同的算法
           // //    ofile << SpanFactory_DDE[Ins][i] << "\t";
           // //    // cout << SpanFactory_DDE[Ins][i] << "\t";

           // //    if (SpanFactory_DDE[Ins][i] < min_DDE)
           // //        min_DDE = SpanFactory_DDE[Ins][i];
           // //    if (min_DDE < min_span)
           // //        min_span = min_DDE;
           // //}
           ////// // cout << endl;

           //////  //cout << "IG_Compared:";
           ////// // cout << endl;
           // ofile << "\n";
           // ofile << "IG" << "\n";
           // for (int i = 0; i < 1; i++)        //每个测试用例执行5遍
           // {
           //     srand(i + 100 + Ins);
           //     //SpanFactory[Ins][i] = GA(TimeLimit, Psize);
           //     SpanFactory_IG[Ins][i] = IG_Compared(TimeLimit, 1, Mcoefficien);
           //     IG_Compared_Curve(TimeLimit, 1, Mcoefficien, 0, 0, Ins);
           //     //SpanFactory[Ins][i] = HDDE(TimeLimit, Psize, Mcoefficien, Crossovercoefficient, Selectcoefficient, Iter);   //不同的算法
           //     ofile << SpanFactory_IG[Ins][i] << "\t";
           //     // cout << SpanFactory_IG[Ins][i] << "\t";
           //   
           //     if (SpanFactory_IG[Ins][i] < min_IG)
           //         min_IG = SpanFactory_IG[Ins][i];
           //     if (min_IG < min_span)
           //         min_span = min_IG;
           //    

           // }
           //// //cout << min_IG << endl;
           ////// cout << endl;

           // ofile << "\n";
           // ofile << "PSO" << "\n";
           // for (int i = 0; i < 1; i++)        //每个测试用例执行5遍
           // {
           //     srand(i + 100 + Ins);
           //     //SpanFactory[Ins][i] = GA(TimeLimit, Psize);
           //     SpanFactory_PSO[Ins][i] = PSO(TimeLimit, 50, 200, 1.1, 1.1);
           //     PSO_Curve(TimeLimit, 50, 200, 1.1, 1.1, 0, 0, Ins);
           //     //SpanFactory[Ins][i] = HDDE(TimeLimit, Psize, Mcoefficien, Crossovercoefficient, Selectcoefficient, Iter);   //不同的算法
           //     ofile << SpanFactory_PSO[Ins][i] << "\t";
           //     // cout << SpanFactory_IG[Ins][i] << "\t";

           //     if (SpanFactory_PSO[Ins][i] < min_PSO)
           //         min_PSO = SpanFactory_PSO[Ins][i];
           //     if (min_PSO < min_span)
           //         min_span = min_PSO;

           // }


           // ofile << "\n";
           // ofile << "GA" << "\n";
           // for (int i = 0; i < 1; i++)        //每个测试用例执行5遍
           // {
           //     srand(i + 100 + Ins);
           //     SpanFactory_GA[Ins][i] = GA_Compared(TimeLimit, 100, 0.7, 0.1);
           //     GA_Compared_Curve(TimeLimit, 100, 0.7, 0.1, 0, 0, Ins);
           //     ofile << SpanFactory_GA[Ins][i] << "\t";
           //     if (SpanFactory_GA[Ins][i] < min_GA)
           //         min_GA = SpanFactory_GA[Ins][i];
           //     if (min_GA < min_span)
           //         min_span = min_GA;
           //   
           // }

          
           // ofile << "\n";
           // ofile << "EMBO" << "\n";
           // for (int i = 0; i < 1; i++)        //每个测试用例执行5遍
           // {
           //     srand(i + 100 + Ins);
           //     SpanFactory_EMBO[Ins][i] = EMBO_Compared(25, 3, 1, 10, 1000, gJobs, TimeLimit);
           //     EMBO_Compared_Curve(25, 3, 1, 10, 1000, gJobs, TimeLimit, 0, 0, Ins);
           //     ofile << SpanFactory_EMBO[Ins][i] << "\t";
           //     if (SpanFactory_EMBO[Ins][i] < min_EMBO)
           //         min_EMBO = SpanFactory_EMBO[Ins][i];
           //     if (min_EMBO < min_span)
           //         min_span = min_EMBO;

           // }


            ofile << "\n";
            ofile << "IG_BLOCK" << "\n";



            for (int i = 0; i < 30; i++)        //每个测试用例执行5遍
            {
                srand(i + 100 + Ins);
                //SpanFactory[Ins][i] = GA(TimeLimit, Psize);
                SpanFactory_IG_BLOCK[Ins][i] = IG_BLOCK(TimeLimit, 3, Mcoefficien, 0.5, 0.8, 0.5);
                /*if (Ins == 0)
                {
                    IG_BLOCK_Curve(TimeLimit, 3, Mcoefficien, 0.5, 0.8, 0.5,0,0,Ins);
                }*/
                IG_BLOCK_Curve(TimeLimit, 3, Mcoefficien, 0.5, 0.8, 0.5, 0, 0, Ins);
                //SpanFactory[Ins][i] = HDDE(TimeLimit, Psize, Mcoefficien, Crossovercoefficient, Selectcoefficient, Iter);   //不同的算法
                ofile << SpanFactory_IG_BLOCK[Ins][i] << "\t";
                // cout << SpanFactory_IG[Ins][i] << "\t";

                if (SpanFactory_IG_BLOCK[Ins][i] < min_IG_BLOCK)
                    min_IG_BLOCK = SpanFactory_IG_BLOCK[Ins][i];
                if (min_IG_BLOCK < min_span)
                    min_span = min_IG_BLOCK;
            }




            //ofile << "\n";
            //ofile << "MN_IG" << "\n";
            //for (int i = 0; i < 1; i++)        //每个测试用例执行5遍
            //{
            //    srand(i + 100 + Ins);
            //    SpanFactory_MN_IG[Ins][i] = MN_IG_Compared(TimeLimit, 1, Mcoefficien);
            //    MN_IG_Compared_Curve(TimeLimit, 1, Mcoefficien,0,0,Ins);
            //    ofile << SpanFactory_MN_IG[Ins][i] << "\t";
            //    if (SpanFactory_MN_IG[Ins][i] < min_MN_IG)
            //        min_MN_IG = SpanFactory_MN_IG[Ins][i];
            //    if (min_MN_IG < min_span)
            //        min_span = min_MN_IG;
            //    
            //}
         

            //ofile << "\n";
            //ofile << "EA" << "\n";
            //for (int i = 0; i < 30; i++)        //每个测试用例执行30遍
            //{
            //    srand(i + 100 + Ins);
            //    SpanFactory_EA[Ins][i] = EA(TimeLimit,50);
            //    //EA_Curve(TimeLimit, 50, 0, 0, Ins);
            //    ofile << SpanFactory_EA[Ins][i] << "\t";
            //    if (SpanFactory_EA[Ins][i] < min_EA)
            //        min_EA = SpanFactory_EA[Ins][i];
            //    if (min_EA < min_span)
            //        min_span = min_EA;

            //}

            
        /*    if (Ins == 1)
            {
                DABC_Compared_Curve(TimeLimit, 18, 3, 0, 0, Ins);
                CRO_Compared_Curve(TimeLimit, 150, 0.7, 10, 50,0,0,Ins);
                DDE_Curve(TimeLimit, Psize, Mcoefficien, Crossovercoefficient, Selectcoefficient, Iter,0,0,Ins);
                IG_Compared_Curve(TimeLimit, 18, 3, 0, 0, Ins);
                PSO_Curve(TimeLimit, 50, 200, 1.1, 1.1,0,0,Ins);
                GA_Compared_Curve(TimeLimit, 100, 0.7, 0.1, 0, 0, Ins);
                EMBO_Compared_Curve(51, 3, 1, 10, 1000, gJobs, TimeLimit,0,0,Ins);
                MN_IG_Compared_Curve(TimeLimit, 18, 3, 0, 0, Ins);
            }*/
           // cout << "IGM:";
            //cout << endl;
            //for (int i = 0; i < 5; i++)        //每个测试用例执行5遍
            //{
            //    srand(i + 100 + Ins);
            //    SpanFactory_IGM[Ins][i] = IGM(TimeLimit, 3, nochange, blenway);
            //    //SpanFactory[Ins][i] = IG_Compared(TimeLimit, Psize, Mcoefficien);
            //     //SpanFactory[Ins][i] = HDDE(TimeLimit, Psize, Mcoefficien, Crossovercoefficient, Selectcoefficient, Iter);   //不同的算法
            //    ofile << SpanFactory_IGM[Ins][i] << "\t";
            //    //  cout << SpanFactory_IGM[Ins][i] << "\t";

            //    if (SpanFactory_IGM[Ins][i] < min_IGM)
            //        min_IGM = SpanFactory_IGM[Ins][i];
            //    if (min_IGM < min_span)
            //        min_span = min_IGM;
            //    // cout << min_IGM << endl;
            //}
            //  cout << endl;

           //  // cout << "IG_New:";
           //  // cout << endl;
           // for (int i = 0; i < 5; i++)        //每个测试用例执行5遍
           // {
           //     srand(i + 100 + Ins);
           //     SpanFactory_IGN[Ins][i] = GA(TimeLimit, Psize);
           //    // SpanFactory_IGN[Ins][i] = IG_New(TimeLimit, 1, Mcoefficien);
           //     //SpanFactory[Ins][i] = HDDE(TimeLimit, Psize, Mcoefficien, Crossovercoefficient, Selectcoefficient, Iter);   //不同的算法
           //     ofile << SpanFactory_IGN[Ins][i] << "\t";
           //     //  cout << SpanFactory_IGN[Ins][i] << "\t";

           //     if (SpanFactory_IGN[Ins][i] < min_IGN)
           //         min_IGN = SpanFactory_IGN[Ins][i];
           //     if (min_IGN < min_span)
           //         min_span = min_IGN;

           // }
            // cout << endl;
             
         /*    RPI[0] = (min_CRO - min_IGN) / min_IGN;
              RPI[0] = (min_CRO - min_IGN) / min_IGN;
              RPI[1] = (min_DDE - min_IGN) / min_IGN;*/
            // RPI[2] = (min_IG - min_IGN) / min_IGN;
            // RPI[3] = (min_IGM - min_IGN) / min_IGN;
           //  RPI[4] = (min_IGN - min_IGN) / min_IGN;
             
             //fprintf(f1, "DABC\n");
            fprintf(f1, "%d * %d * %d\n", gJobs, InStage, gFactory);
      /*      RPI[0] = (min_DABC - min_span) / min_span;
            fprintf(f1, "DABC:%lf , ", RPI[0]);
            RPI[1] = (min_CRO - min_span) / min_span;
            fprintf(f1, "CRO:%lf , ", RPI[1]);
            RPI[2] = (min_IG - min_span) / min_span;
            fprintf(f1, "IG:%lf , ", RPI[2]);
            RPI[3] = (min_PSO - min_span) / min_span;
            fprintf(f1, "PSO:%lf , ", RPI[3]);
            RPI[4] = (min_GA - min_span) / min_span;
            fprintf(f1, "GA:%lf , ", RPI[4]);
            RPI[5] = (min_EMBO - min_span) / min_span;
            fprintf(f1, "EMBO:%lf , ", RPI[5]);*/
           // RPI[6] = (min_IG_BLOCK - min_span) / min_span;
           // fprintf(f1, "IG_BLOCK:%lf , ", RPI[6]);
           ///* RPI[7] = (min_MN_IG - min_span) / min_span;
           // fprintf(f1, "MN_IG:%lf , ", RPI[7]);*/
           // RPI[8] = (min_EA - min_span) / min_span;
           // fprintf(f1, "EA:%lf , ", RPI[8]);

            fprintf(f1, "\n");

           // cout << "DABC:" << RPI[0] << " , " << "CRO:" << RPI[1] << " , " << "IG:" << RPI[2] << " , " << "DPSO:" << RPI[3] << " , " << "GA:" << RPI[4] << " , " << "EMBO:" << RPI[5] << " , " <<  "IG_BLOCK:" << RPI[6] << " , " << "MN_IG:" << RPI[7] << endl;
           /* cout << "IG_BLOCK:" << RPI[6] << " , " << "EA:" << RPI[8] << endl;*/
            cout << endl;
            // cout << min_span << endl;
            ofile << endl;


        }
        fclose(f1);
        ofile.close();
    }
}
