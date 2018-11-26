#include <iostream>
#include <math.h>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")

int main()
{
    //输入图像多光谱
   GDALDataset* poSrcDSdgp;
    //输入图像全色
   GDALDataset* poSrcDSqs;
   //输出图像
   GDALDataset* poDstDS;
   //图像的宽度和高度
   int imgXlen,imgYlen;
   //输入图像多光谱路径
   char* srcPathdgp = "duoguangpu.bmp";
   //输入图像全色路径
   char* srcPathqs = "quanse.bmp";
   //输出图像路径
   char* dstPath = "res.tif";
   //图像RGB缓存
   float* buffTmpR,* buffTmpG,* buffTmpB;
  //图像IHS缓存
   float* buffTmpI,* buffTmpH,* buffTmpS;
   //图像波段数
   int i,j,bandNum,a,b;
   //GRB --> IHS
   float tran1[3][3] = {1/3,1/3,1/3,//rgb -->i
            -sqrt(2.0f)/6,-sqrt(2.0f)/6,sqrt(2.0f)/3,//rgb -->h
            1/sqrt(2.0f),-1/sqrt(2.0f),0};//rgb -->s
   //IHS --> RGB
   float tran2[3][3] = {1,-1/sqrt(2.0f),1/sqrt(2.0f),//ihs -->r
            1,-1/sqrt(2.0f),-1/sqrt(2.0f),//ihs --> g
            1,sqrt(2.0f),0};//ihs --> b
   //注册驱动
   GDALAllRegister();
   //打开图像
   poSrcDSdgp = (GDALDataset*)GDALOpenShared(srcPathdgp,GA_ReadOnly);
   poSrcDSqs = (GDALDataset*)GDALOpenShared(srcPathqs,GA_ReadOnly);
   //获取图像的宽度，高度和波段数
   imgXlen = poSrcDSdgp->GetRasterXSize();
   imgYlen = poSrcDSdgp->GetRasterYSize();
   bandNum = poSrcDSdgp->GetRasterCount();
   //根据图像的宽度和高度分配内存
   buffTmpR = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));
   buffTmpG = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));
   buffTmpB = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));
   buffTmpI = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));
   buffTmpH = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));
   buffTmpS = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));
   //创建输出图像
   poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
     dstPath,imgXlen,imgYlen,bandNum,GDT_Byte,NULL);
   //输入多光谱图像的RGB
   poSrcDSdgp->GetRasterBand(1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpR,imgXlen,imgYlen,GDT_Float32,0,0);
   poSrcDSdgp->GetRasterBand(2)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpG,imgXlen,imgYlen,GDT_Float32,0,0);
   poSrcDSdgp->GetRasterBand(3)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpB,imgXlen,imgYlen,GDT_Float32,0,0);
   //输入全色图像的R
   poSrcDSqs->GetRasterBand(1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpI,imgXlen,imgYlen,GDT_Float32,0,0);

          for(int i = 0;i < imgYlen;i ++)
          for(int j = 0;j < imgXlen;j ++)
          {
              //将多光谱图像的RGB转换为HS
              buffTmpH[i * imgXlen + j] = buffTmpR[i * imgXlen + j] * tran1[1][0] + buffTmpG[i * imgXlen + j] * tran1[1][1] + buffTmpB[i * imgXlen + j] * tran1[1][2];
              buffTmpS[i * imgXlen + j] = buffTmpR[i * imgXlen + j] * tran1[2][0] + buffTmpG[i * imgXlen + j] * tran1[2][1] + buffTmpB[i * imgXlen + j] * tran1[2][2];
            //将IHS转换为RGB
              buffTmpR[i * imgXlen + j] = buffTmpI[i * imgXlen + j] * tran2[0][0] + buffTmpH[i * imgXlen + j] * tran2[0][1] + buffTmpS[i * imgXlen + j] * tran2[0][2];
              buffTmpG[i * imgXlen + j] = buffTmpI[i * imgXlen + j] * tran2[1][0] + buffTmpH[i * imgXlen + j] * tran2[1][1] + buffTmpS[i * imgXlen + j] * tran2[1][2];
              buffTmpB[i * imgXlen + j] = buffTmpI[i * imgXlen + j] * tran2[2][0] + buffTmpH[i * imgXlen + j] * tran2[2][1] + buffTmpS[i * imgXlen + j] * tran2[2][2];
          }
          //输出图像
       poDstDS->GetRasterBand(1)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpR,imgXlen,imgYlen,GDT_Float32,0,0);
       poDstDS->GetRasterBand(2)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpG,imgXlen,imgYlen,GDT_Float32,0,0);
       poDstDS->GetRasterBand(3)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpB,imgXlen,imgYlen,GDT_Float32,0,0);


   //清除内存
   CPLFree(buffTmpR);
   CPLFree(buffTmpG);
   CPLFree(buffTmpB);
   CPLFree(buffTmpI);
   CPLFree(buffTmpH);
   CPLFree(buffTmpS);
   //关闭dataset
   GDALClose(poDstDS);
   GDALClose(poSrcDSdgp);
   GDALClose(poSrcDSqs);
   system("PAUSE");
   return 0;
}
