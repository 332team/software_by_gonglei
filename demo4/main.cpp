#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")


int main()
{
    //输入图像
   GDALDataset* poSrcDS;
   //输出图像
   GDALDataset* poDstDS1;
   GDALDataset* poDstDS2;
   GDALDataset* poDstDS3;
   GDALDataset* poDstDS4;
   GDALDataset* poDstDS5;
   GDALDataset* poDstDS6;
   //图像的宽度和高度
   int imgXlen,imgYlen;
   //输入图像路径
   char* srcPath = "lena.jpg";
   //输出图像路径
   char* dstPath1 = "res1.tif";
   char* dstPath2 = "res2.tif";
   char* dstPath3 = "res3.tif";
   char* dstPath4 = "res4.tif";
   char* dstPath5 = "res5.tif";
   char* dstPath6 = "res6.tif";
   //图像内存存储,改变区域内存存储
   GByte *buffTmpR,*buffTmpG,*buffTmpB,*buffTmpR1,*buffTmpG1,*buffTmpB1;
   //图像波段数
   int i,j,bandNum,a,b;
   //计算矩阵和
   double sumR,sumG,sumB;
   //6个卷积核
   double k1[3][3] = {0,1,0,1,1,1,0,1,0};//均值模糊
   double k2[5][5] = {1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1};//运动模糊
   double k3[3][3] = {-1,-1,-1,-1,8,-1,-1,-1,-1};//边缘检测
   double k4[3][3] = {-1,-1,-1,-1,9,-1,-1,-1,-1};//锐化
   double k5[3][3] = {-1,-1,0,-1,0,1,0,1,1};//浮雕
   double k6[5][5] = {0.0120,0.1253,0.2736,0.1253,0.0120,
                     0.1253,1.3054,2.8514,1.3054,0.1253,
                     0.2736,2.8514,6.2279,2.8514,0.2736,
                     0.1253,1.3054,2.8514,1.3054,0.1253,
                     0.0120,0.1253,0.2736,0.1253,0.0120};//高斯模糊

   //注册驱动
   GDALAllRegister();
   //打开图像
   poSrcDS = (GDALDataset*)GDALOpenShared(srcPath,GA_ReadOnly);
    //获取图像的宽度，高度和波段数
   imgXlen = poSrcDS->GetRasterXSize();
   imgYlen = poSrcDS->GetRasterYSize();
   bandNum = poSrcDS->GetRasterCount();

   //根据图像的宽度和高度分配内存
   buffTmpR = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
   buffTmpG = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
   buffTmpB = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
   buffTmpR1 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
   buffTmpG1 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
   buffTmpB1 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
//创建输出图像
   poDstDS1 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
     dstPath1,imgXlen,imgYlen,bandNum,GDT_Byte,NULL);

   //k1
      //输入三个通道的值
       poSrcDS->GetRasterBand(1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpR,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS->GetRasterBand(2)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpG,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS->GetRasterBand(3)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpB,imgXlen,imgYlen,GDT_Byte,0,0);
       //矩阵求和
        for(j = 0;j < imgYlen;j ++)
        for(i = 0;i < imgXlen;i ++)
       {
           sumR = sumG = sumB = 0;
           //边界直接设为0
           if(j == 0 || i == 0 || j == imgYlen - 1 || i == imgXlen - 1)
           {
                buffTmpR1[j * imgXlen  +i] = (GByte)0;
                buffTmpG1[j * imgXlen  +i] = (GByte)0;
                buffTmpB1[j * imgXlen  +i] = (GByte)0;
           }

           else
           {
               for(a = j - 1;a <= j + 1;a ++)
                for(b = i - 1;b <= i + 1;b ++)
               {
                   sumR +=  buffTmpR[a * imgXlen  +b] * k1[a - j + 1][b - i + 1];
                   sumG +=  buffTmpG[a * imgXlen  +b] * k1[a - j + 1][b - i + 1];
                   sumB +=  buffTmpB[a * imgXlen  +b] * k1[a - j + 1][b - i + 1];
               }
                sumR *= 0.2;
                sumG *= 0.2;
                sumB *= 0.2;
                buffTmpR1[j * imgXlen  +i] = (GByte)sumR;
                buffTmpG1[j * imgXlen  +i] = (GByte)sumG;
                buffTmpB1[j * imgXlen  +i] = (GByte)sumB;
           }

       }
      poDstDS1->GetRasterBand(1)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpR1,imgXlen,imgYlen,GDT_Byte,0,0);
       poDstDS1->GetRasterBand(2)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpG1,imgXlen,imgYlen,GDT_Byte,0,0);
        poDstDS1->GetRasterBand(3)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpB1,imgXlen,imgYlen,GDT_Byte,0,0);

        //k2
        poDstDS2 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
     dstPath2,imgXlen,imgYlen,bandNum,GDT_Byte,NULL);
   poSrcDS->GetRasterBand(1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpR,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS->GetRasterBand(2)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpG,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS->GetRasterBand(3)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpB,imgXlen,imgYlen,GDT_Byte,0,0);
        for(j = 0;j < imgYlen;j ++)
        for(i = 0;i < imgXlen;i ++)
       {
           sumR = sumG = sumB = 0;
           if(j == 0 || i == 0 || j == imgYlen - 1 || i == imgXlen - 1 || j == 1 || i == 1 || j == imgYlen - 2 || i == imgXlen - 2)
           {
                buffTmpR1[j * imgXlen  +i] = (GByte)0;
                 buffTmpG1[j * imgXlen  +i] = (GByte)0;
                  buffTmpB1[j * imgXlen  +i] = (GByte)0;
           }

           else
           {
               for(a = j - 2;a <= j + 2;a ++)
                for(b = i - 2;b <= i + 2;b ++)
               {
                   sumR +=  buffTmpR[a * imgXlen  +b] * k2[a - j + 2][b - i + 2];
                   sumG +=  buffTmpG[a * imgXlen  +b] * k2[a - j + 2][b - i + 2];
                   sumB +=  buffTmpB[a * imgXlen  +b] * k2[a - j + 2][b - i + 2];
               }
                sumR *= 0.2;
                sumG *= 0.2;
                sumB *= 0.2;
                buffTmpR1[j * imgXlen  +i] = (GByte)sumR;
                buffTmpG1[j * imgXlen  +i] = (GByte)sumG;
                buffTmpB1[j * imgXlen  +i] = (GByte)sumB;
           }

       }
      poDstDS2->GetRasterBand(1)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpR1,imgXlen,imgYlen,GDT_Byte,0,0);
       poDstDS2->GetRasterBand(2)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpG1,imgXlen,imgYlen,GDT_Byte,0,0);
        poDstDS2->GetRasterBand(3)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpB1,imgXlen,imgYlen,GDT_Byte,0,0);
//k3
 poDstDS3 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
     dstPath3,imgXlen,imgYlen,bandNum,GDT_Byte,NULL);
   poSrcDS->GetRasterBand(1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpR,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS->GetRasterBand(2)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpG,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS->GetRasterBand(3)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpB,imgXlen,imgYlen,GDT_Byte,0,0);
        for(j = 0;j < imgYlen;j ++)
        for(i = 0;i < imgXlen;i ++)
       {
           sumR = sumG = sumB = 0;
           if(j == 0 || i == 0 || j == imgYlen - 1 || i == imgXlen - 1)
           {
                buffTmpR1[j * imgXlen  +i] = (GByte)0;
                buffTmpG1[j * imgXlen  +i] = (GByte)0;
                buffTmpB1[j * imgXlen  +i] = (GByte)0;
           }

           else
           {
               for(a = j - 1;a <= j + 1;a ++)
                for(b = i - 1;b <= i + 1;b ++)
               {
                   sumR +=  buffTmpR[a * imgXlen  +b] * k3[a - j + 1][b - i + 1];
                   sumG +=  buffTmpG[a * imgXlen  +b] * k3[a - j + 1][b - i + 1];
                   sumB +=  buffTmpB[a * imgXlen  +b] * k3[a - j + 1][b - i + 1];
               }
                buffTmpR1[j * imgXlen  +i] = (GByte)sumR;
                buffTmpG1[j * imgXlen  +i] = (GByte)sumG;
                buffTmpB1[j * imgXlen  +i] = (GByte)sumB;
           }

       }
      poDstDS3->GetRasterBand(1)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpR1,imgXlen,imgYlen,GDT_Byte,0,0);
       poDstDS3->GetRasterBand(2)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpG1,imgXlen,imgYlen,GDT_Byte,0,0);
        poDstDS3->GetRasterBand(3)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpB1,imgXlen,imgYlen,GDT_Byte,0,0);

//k4
 poDstDS4 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
     dstPath4,imgXlen,imgYlen,bandNum,GDT_Byte,NULL);
   poSrcDS->GetRasterBand(1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpR,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS->GetRasterBand(2)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpG,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS->GetRasterBand(3)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpB,imgXlen,imgYlen,GDT_Byte,0,0);
        for(j = 0;j < imgYlen;j ++)
        for(i = 0;i < imgXlen;i ++)
       {
           sumR = sumG = sumB = 0;
           if(j == 0 || i == 0 || j == imgYlen - 1 || i == imgXlen - 1)
           {
                buffTmpR1[j * imgXlen  +i] = (GByte)0;
                 buffTmpG1[j * imgXlen  +i] = (GByte)0;
                  buffTmpB1[j * imgXlen  +i] = (GByte)0;
           }

           else
           {
               for(a = j - 1;a <= j + 1;a ++)
                for(b = i - 1;b <= i + 1;b ++)
               {
                   sumR +=  buffTmpR[a * imgXlen  +b] * k4[a - j + 1][b - i + 1];
                   sumG +=  buffTmpG[a * imgXlen  +b] * k4[a - j + 1][b - i + 1];
                   sumB +=  buffTmpB[a * imgXlen  +b] * k4[a - j + 1][b - i + 1];
               }

                buffTmpR1[j * imgXlen  +i] = (GByte)sumR;
                buffTmpG1[j * imgXlen  +i] = (GByte)sumG;
                buffTmpB1[j * imgXlen  +i] = (GByte)sumB;
           }

       }
      poDstDS4->GetRasterBand(1)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpR1,imgXlen,imgYlen,GDT_Byte,0,0);
       poDstDS4->GetRasterBand(2)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpG1,imgXlen,imgYlen,GDT_Byte,0,0);
        poDstDS4->GetRasterBand(3)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpB1,imgXlen,imgYlen,GDT_Byte,0,0);

       //k5
  poDstDS5 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
     dstPath5,imgXlen,imgYlen,bandNum,GDT_Byte,NULL);
   poSrcDS->GetRasterBand(1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpR,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS->GetRasterBand(2)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpG,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS->GetRasterBand(3)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpB,imgXlen,imgYlen,GDT_Byte,0,0);
        for(j = 0;j < imgYlen;j ++)
        for(i = 0;i < imgXlen;i ++)
       {
           sumR = sumG = sumB = 0;
           if(j == 0 || i == 0 || j == imgYlen - 1 || i == imgXlen - 1)
           {
                buffTmpR1[j * imgXlen  +i] = (GByte)0;
                 buffTmpG1[j * imgXlen  +i] = (GByte)0;
                  buffTmpB1[j * imgXlen  +i] = (GByte)0;
           }

           else
           {
               for(a = j - 1;a <= j + 1;a ++)
                for(b = i - 1;b <= i + 1;b ++)
               {
                   sumR +=  buffTmpR[a * imgXlen  +b] * k5[a - j + 1][b - i + 1];
                   sumG +=  buffTmpG[a * imgXlen  +b] * k5[a - j + 1][b - i + 1];
                   sumB +=  buffTmpB[a * imgXlen  +b] * k5[a - j + 1][b - i + 1];
               }
                sumR += 128;
                if(sumR > 255)
                    sumR = 255;
                else if(sumR < 0)
                    sumR = 0;
                  sumG += 128;
                if(sumG > 255)
                    sumG = 255;
                else if(sumG < 0)
                    sumG = 0;
                      sumB += 128;
                if(sumB > 255)
                    sumB = 255;
                else if(sumB < 0)
                    sumB = 0;
                buffTmpR1[j * imgXlen  +i] = (GByte)sumR ;
                buffTmpG1[j * imgXlen  +i] = (GByte)sumG ;
                buffTmpB1[j * imgXlen  +i] = (GByte)sumB ;
           }

       }
      poDstDS5->GetRasterBand(1)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpR1,imgXlen,imgYlen,GDT_Byte,0,0);
       poDstDS5->GetRasterBand(2)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpG1,imgXlen,imgYlen,GDT_Byte,0,0);
        poDstDS5->GetRasterBand(3)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpB1,imgXlen,imgYlen,GDT_Byte,0,0);

//k6
 poDstDS6 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
     dstPath6,imgXlen,imgYlen,bandNum,GDT_Byte,NULL);
   poSrcDS->GetRasterBand(1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpR,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS->GetRasterBand(2)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpG,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS->GetRasterBand(3)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpB,imgXlen,imgYlen,GDT_Byte,0,0);
        for(j = 0;j < imgYlen;j ++)
        for(i = 0;i < imgXlen;i ++)
       {
           sumR = sumG = sumB = 0;
           if(j == 0 || i == 0 || j == imgYlen - 1 || i == imgXlen - 1 || j == 1 || i == 1 || j == imgYlen - 2 || i == imgXlen - 2)
           {
                buffTmpR1[j * imgXlen  +i] = (GByte)0;
                 buffTmpG1[j * imgXlen  +i] = (GByte)0;
                  buffTmpB1[j * imgXlen  +i] = (GByte)0;
           }

           else
           {
               for(a = j - 2;a <= j + 2;a ++)
                for(b = i - 2;b <= i + 2;b ++)
               {
                   sumR +=  buffTmpR[a * imgXlen  +b] * k6[a - j + 2][b - i + 2];
                   sumG +=  buffTmpG[a * imgXlen  +b] * k6[a - j + 2][b - i + 2];
                   sumB +=  buffTmpB[a * imgXlen  +b] * k6[a - j + 2][b - i + 2];
               }
                sumR /= 25;
                sumG /= 25;
                sumB /= 25;
                buffTmpR1[j * imgXlen  +i] = (GByte)sumR;
                buffTmpG1[j * imgXlen  +i] = (GByte)sumG;
                buffTmpB1[j * imgXlen  +i] = (GByte)sumB;
           }

       }
      poDstDS6->GetRasterBand(1)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpR1,imgXlen,imgYlen,GDT_Byte,0,0);
       poDstDS6->GetRasterBand(2)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpG1,imgXlen,imgYlen,GDT_Byte,0,0);
        poDstDS6->GetRasterBand(3)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpB1,imgXlen,imgYlen,GDT_Byte,0,0);

   //清除内存
   CPLFree(buffTmpR);
  CPLFree(buffTmpG);
  CPLFree(buffTmpB);
     CPLFree(buffTmpR1);
  CPLFree(buffTmpG1);
  CPLFree(buffTmpB1);
   //关闭dataset
   GDALClose(poDstDS1);
   GDALClose(poDstDS2);
   GDALClose(poDstDS3);
   GDALClose(poDstDS4);
   GDALClose(poDstDS5);
   GDALClose(poDstDS6);


   system("PAUSE");
   return 0;
}
