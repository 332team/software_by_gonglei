```
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
   GDALDataset* poDstDS1;
   GDALDataset* poDstDS2;
   //图像的宽度和高度
   int imgXlen,imgYlen;
   //输入图像多光谱路径
   char* srcPathdgp = "Mul_large.tif";
   //输入图像全色路径
   char* srcPathqs = "Pan_large.tif";
   //输出图像路径
   char* dstPath1 = "res1.tif";
   char* dstPath2 = "res2.tif";
   //图像RGB缓存
   float* buffTmpR,* buffTmpG,* buffTmpB;
  //图像IHS缓存
   float* buffTmpI,* buffTmpH,* buffTmpS;
   //图像波段数
   int i,j,bandNum,a,b,k,l,f1,f2,x,y;
   //几个分块
   int n,m;
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
   n = imgXlen / 256;
   m = imgYlen / 256;

   //根据图像的宽度和高度分配内存
   buffTmpR = (float*)CPLMalloc(256*256*sizeof(float));
   buffTmpG = (float*)CPLMalloc(256*256*sizeof(float));
   buffTmpB = (float*)CPLMalloc(256*256*sizeof(float));
   buffTmpI = (float*)CPLMalloc(256*256*sizeof(float));
   buffTmpH = (float*)CPLMalloc(256*256*sizeof(float));
   buffTmpS = (float*)CPLMalloc(256*256*sizeof(float));
   //创建输出图像
   poDstDS1 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
     dstPath1,imgXlen,imgYlen,bandNum,GDT_Byte,NULL);
//1

   for(int i = 0;i <= m;i ++)//第几个横块y
   for(int j = 0;j <= n;j ++)//第几个竖块x
   {
       k = i * 256;//起点行y
       l = j * 256;//起点列x
       if(i == m)
        f1 = imgYlen;
       else
        f1 = k + 256;
       if(j == n)
        f2 = imgXlen;
       else
        f2 = l + 256;

  //输入多光谱图像的RGB
   poSrcDSdgp->GetRasterBand(1)->RasterIO(GF_Read,l,k,f2 - l,f1 - k,buffTmpR,f2 - l,f1 - k,GDT_Float32,0,0);
   poSrcDSdgp->GetRasterBand(2)->RasterIO(GF_Read,l,k,f2 - l,f1 - k,buffTmpG,f2 - l,f1 - k,GDT_Float32,0,0);
   poSrcDSdgp->GetRasterBand(3)->RasterIO(GF_Read,l,k,f2 - l,f1 - k,buffTmpB,f2 - l,f1 - k,GDT_Float32,0,0);
   //输入全色图像的R
   poSrcDSqs->GetRasterBand(1)->RasterIO(GF_Read,l,k,f2 - l,f1 - k,buffTmpI,f2 - l,f1 - k,GDT_Float32,0,0);
       for(y = 0;y < f1 - k;y ++)
       for(x = 0;x < f2 - l;x ++)
       {
          //将多光谱图像的RGB转换为HS
              buffTmpH[y * (f2 - l) + x] = buffTmpR[y * (f2 - l) + x] * tran1[1][0] + buffTmpG[y * (f2 - l) + x] * tran1[1][1] + buffTmpB[y * (f2 - l) + x] * tran1[1][2];
              buffTmpS[y * (f2 - l) + x] = buffTmpR[y * (f2 - l) + x] * tran1[2][0] + buffTmpG[y * (f2 - l) + x] * tran1[2][1] + buffTmpB[y * (f2 - l) + x] * tran1[2][2];
            //将IHS转换为RGB
              buffTmpR[y * (f2 - l) + x] = buffTmpI[y * (f2 - l) + x] * tran2[0][0] + buffTmpH[y * (f2 - l) + x] * tran2[0][1] + buffTmpS[y * (f2 - l) + x] * tran2[0][2];
              buffTmpG[y * (f2 - l) + x] = buffTmpI[y * (f2 - l) + x] * tran2[1][0] + buffTmpH[y * (f2 - l) + x] * tran2[1][1] + buffTmpS[y * (f2 - l) + x] * tran2[1][2];

              buffTmpB[y * (f2 - l) + x] = buffTmpI[y * (f2 - l) + x] * tran2[2][0] + buffTmpH[y * (f2 - l) + x] * tran2[2][1] + buffTmpS[y * (f2 - l) + x] * tran2[2][2];


       }
        //输出图像
       poDstDS1->GetRasterBand(1)->RasterIO(GF_Write,l,k,f2 - l,f1 - k,buffTmpR,f2 - l,f1 - k,GDT_Float32,0,0);
       poDstDS1->GetRasterBand(2)->RasterIO(GF_Write,l,k,f2 - l,f1 - k,buffTmpG,f2 - l,f1 - k,GDT_Float32,0,0);
       poDstDS1->GetRasterBand(3)->RasterIO(GF_Write,l,k,f2 - l,f1 - k,buffTmpB,f2 - l,f1 - k,GDT_Float32,0,0);
   }

//2.

   buffTmpR = (float*)CPLMalloc(imgXlen*256*sizeof(float));
   buffTmpG = (float*)CPLMalloc(imgXlen*256*sizeof(float));
   buffTmpB = (float*)CPLMalloc(imgXlen*256*sizeof(float));
   buffTmpI = (float*)CPLMalloc(imgXlen*256*sizeof(float));
   buffTmpH = (float*)CPLMalloc(imgXlen*256*sizeof(float));
   buffTmpS = (float*)CPLMalloc(imgXlen*256*sizeof(float));

 //创建输出图像
   poDstDS2 = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
     dstPath2,imgXlen,imgYlen,bandNum,GDT_Byte,NULL);

   for(int i = 0;i <= m;i ++)//第几个横块y
   {
       k = i * 256;//起点行y
       if(i == m)
        f1 = imgYlen;
       else
        f1 = k + 256;

  //输入多光谱图像的RGB
   poSrcDSdgp->GetRasterBand(1)->RasterIO(GF_Read,0,k,imgXlen,f1 - k,buffTmpR,imgXlen,f1 - k,GDT_Float32,0,0);
   poSrcDSdgp->GetRasterBand(2)->RasterIO(GF_Read,0,k,imgXlen,f1 - k,buffTmpG,imgXlen,f1 - k,GDT_Float32,0,0);
   poSrcDSdgp->GetRasterBand(3)->RasterIO(GF_Read,0,k,imgXlen,f1 - k,buffTmpB,imgXlen,f1 - k,GDT_Float32,0,0);
   //输入全色图像的R
   poSrcDSqs->GetRasterBand(1)->RasterIO(GF_Read,0,k,imgXlen,f1 - k,buffTmpI,imgXlen,f1 - k,GDT_Float32,0,0);
       for(y = 0;y < f1 - k;y ++)
       for(x = 0;x < imgXlen;x ++)
       {
          //将多光谱图像的RGB转换为HS
              buffTmpH[y * imgXlen + x] = buffTmpR[y * imgXlen + x] * tran1[1][0] + buffTmpG[y * imgXlen + x] * tran1[1][1] + buffTmpB[y * imgXlen + x] * tran1[1][2];
              buffTmpS[y * imgXlen + x] = buffTmpR[y * imgXlen + x] * tran1[2][0] + buffTmpG[y * imgXlen + x] * tran1[2][1] + buffTmpB[y * imgXlen + x] * tran1[2][2];
            //将IHS转换为RGB
              buffTmpR[y * imgXlen + x] = buffTmpI[y * imgXlen + x] * tran2[0][0] + buffTmpH[y * imgXlen + x] * tran2[0][1] + buffTmpS[y * imgXlen + x] * tran2[0][2];
              buffTmpG[y * imgXlen + x] = buffTmpI[y * imgXlen + x] * tran2[1][0] + buffTmpH[y * imgXlen + x] * tran2[1][1] + buffTmpS[y * imgXlen + x] * tran2[1][2];

              buffTmpB[y * imgXlen + x] = buffTmpI[y * imgXlen + x] * tran2[2][0] + buffTmpH[y * imgXlen + x] * tran2[2][1] + buffTmpS[y * imgXlen + x] * tran2[2][2];


       }
        //输出图像
       poDstDS2->GetRasterBand(1)->RasterIO(GF_Write,0,k,imgXlen,f1 - k,buffTmpR,imgXlen,f1 - k,GDT_Float32,0,0);
       poDstDS2->GetRasterBand(2)->RasterIO(GF_Write,0,k,imgXlen,f1 - k,buffTmpG,imgXlen,f1 - k,GDT_Float32,0,0);
       poDstDS2->GetRasterBand(3)->RasterIO(GF_Write,0,k,imgXlen,f1 - k,buffTmpB,imgXlen,f1 - k,GDT_Float32,0,0);
   }

   //清除内存
   CPLFree(buffTmpR);
   CPLFree(buffTmpG);
   CPLFree(buffTmpB);
   CPLFree(buffTmpI);
   CPLFree(buffTmpH);
   CPLFree(buffTmpS);
   //关闭dataset
   GDALClose(poDstDS1);
   GDALClose(poDstDS2);
   GDALClose(poSrcDSdgp);
   GDALClose(poSrcDSqs);
   system("PAUSE");
   return 0;
}
```
