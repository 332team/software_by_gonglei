#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")
/*
直接将Superman覆盖在space上不行，只能把space的rgb改掉
int main()
{
   //输入图像space Superman
   GDALDataset* poSrcDS1;
   GDALDataset* poSrcDS2;
   //输出图像
   GDALDataset* poDstDS;
   //图像的宽度和高度
   int imgXlen,imgYlen;
   //r g b
    GByte r,g,b;
   //输入图像路径
   char* srcPath1 = "space.jpg";
   char* srcPath2 = "superman.jpg";
   //输出图像路径
   char* dstPath = "res.tif";
   //图像内存存储
   GByte* buffTmp;
   //存储superman三个通道
   GByte* buffTmpR;
   GByte* buffTmpG;
   GByte* buffTmpB;
   //存储space三个通道
   GByte* buffTmpR1;
   GByte* buffTmpG1;
   GByte* buffTmpB1;
   //图像波段数
   int i,j,bandNum;
   //注册驱动
   GDALAllRegister();
   //打开图像space
   poSrcDS1 = (GDALDataset*)GDALOpenShared(srcPath1,GA_ReadOnly);
    //获取图片superman
   poSrcDS2 = (GDALDataset*)GDALOpenShared(srcPath2,GA_ReadOnly);


    //获取图像的宽度，高度和波段数
   imgXlen = poSrcDS1->GetRasterXSize();
   imgYlen = poSrcDS1->GetRasterYSize();
   bandNum = poSrcDS1->GetRasterCount();

   //根据图像的宽度和高度分配内存
   buffTmp = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
//创建输出图像
   poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
     dstPath,imgXlen,imgYlen,bandNum,GDT_Byte,NULL);
//free
//将图片输出到新建的图片
       for(i = 0;i < bandNum;i ++)
   {
       poSrcDS1->GetRasterBand(i + 1)->RasterIO(
        GF_Read,0,0,imgXlen,imgYlen,buffTmp,imgXlen,imgYlen,GDT_Byte,0,0);
       poDstDS->GetRasterBand(i + 1)->RasterIO(
        GF_Write,0,0,imgXlen,imgYlen,buffTmp,imgXlen,imgYlen,GDT_Byte,0,0);


   }





       //获得Superman1,2,3通道
       buffTmpR = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
       buffTmpG = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
       buffTmpB = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
       poSrcDS2->GetRasterBand(1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpR,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS2->GetRasterBand(2)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpG,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS2->GetRasterBand(3)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpB,imgXlen,imgYlen,GDT_Byte,0,0);


   //10<r<160; 条件2：100<g<220; 条件3：10<b<110,背景范围



       for(j = 0;j < imgYlen;j ++)
        for(i = 0;i < imgXlen;i ++)
       {

          //获得当前像素的rgb
           r = buffTmpR[j * imgXlen  +i];
           g = buffTmpG[j * imgXlen  +i];
           b = buffTmpB[j * imgXlen  +i];
           if(!(r > 10 && r < 160 && g > 100 && g < 220 && b > 10 && b < 110))//不是背景，是Superman
          {
       poDstDS->GetRasterBand(1)->RasterIO(GF_Write,i,j,1,1,buffTmpR,imgXlen,imgYlen,GDT_Byte,0,0);
       poDstDS->GetRasterBand(2)->RasterIO(GF_Write,i,j,1,1,buffTmpG,imgXlen,imgYlen,GDT_Byte,0,0);
       poDstDS->GetRasterBand(3)->RasterIO(GF_Write,i,j,1,1,buffTmpB,imgXlen,imgYlen,GDT_Byte,0,0);


           }
       }
 //将修改后的图片输出


   //清除内存
CPLFree(buffTmp);
    CPLFree(buffTmpR);
     CPLFree(buffTmpG);
      CPLFree(buffTmpB);

   //关闭dataset
   GDALClose(poDstDS);
   GDALClose(poSrcDS1);
    GDALClose(poSrcDS2);
   system("PAUSE");
   return 0;
}

*/
int main()
{
   //输入图像space Superman
   GDALDataset* poSrcDS1;
   GDALDataset* poSrcDS2;
   //输出图像
   GDALDataset* poDstDS;
   //图像的宽度和高度
   int imgXlen,imgYlen;
   //r g b
    GByte r,g,b;
   //输入图像路径
   char* srcPath1 = "space.jpg";
   char* srcPath2 = "superman.jpg";
   //输出图像路径
   char* dstPath = "res.tif";
   //图像内存存储
   GByte* buffTmp;
   //存储superman三个通道
   GByte* buffTmpR;
   GByte* buffTmpG;
   GByte* buffTmpB;
   //存储space三个通道
   GByte* buffTmpR1;
   GByte* buffTmpG1;
   GByte* buffTmpB1;
   //图像波段数
   int i,j,bandNum;
   //注册驱动
   GDALAllRegister();
   //打开图像space
   poSrcDS1 = (GDALDataset*)GDALOpenShared(srcPath1,GA_ReadOnly);
    //获取图片superman
   poSrcDS2 = (GDALDataset*)GDALOpenShared(srcPath2,GA_ReadOnly);

    //获取图像space的宽度，高度和波段数，两张图片一样大
   imgXlen = poSrcDS1->GetRasterXSize();
   imgYlen = poSrcDS1->GetRasterYSize();
   bandNum = poSrcDS1->GetRasterCount();

//创建输出图像
   poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
     dstPath,imgXlen,imgYlen,bandNum,GDT_Byte,NULL);




       //获得Superman1,2,3通道
       buffTmpR = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
       buffTmpG = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
       buffTmpB = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
       poSrcDS2->GetRasterBand(1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpR,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS2->GetRasterBand(2)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpG,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS2->GetRasterBand(3)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpB,imgXlen,imgYlen,GDT_Byte,0,0);
       // 获得space 1,2,3通道
       buffTmpR1 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
       buffTmpG1 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
       buffTmpB1 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
       poSrcDS1->GetRasterBand(1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpR1,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS1->GetRasterBand(2)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpG1,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS1->GetRasterBand(3)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpB1,imgXlen,imgYlen,GDT_Byte,0,0);

   //10<r<160; 条件2：100<g<220; 条件3：10<b<110,背景范围



       for(j = 0;j < imgYlen;j ++)
        for(i = 0;i < imgXlen;i ++)
       {
          //获得当前像素的rgb
           r = buffTmpR[j * imgXlen  +i];
           g = buffTmpG[j * imgXlen  +i];
           b = buffTmpB[j * imgXlen  +i];
           if(!(r > 10 && r < 160 && g > 100 && g < 220 && b > 10 && b < 110))//不是背景，是Superman
           {
            //把space的rgb改成Superman
            buffTmpR1[j * imgXlen  +i] = r;
            buffTmpG1[j * imgXlen  +i] = g;
            buffTmpB1[j * imgXlen  +i] = b;


           }
       }
 //将修改后的图片输出
       poDstDS->GetRasterBand(1)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpR1,imgXlen,imgYlen,GDT_Byte,0,0);
       poDstDS->GetRasterBand(2)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpG1,imgXlen,imgYlen,GDT_Byte,0,0);
       poDstDS->GetRasterBand(3)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpB1,imgXlen,imgYlen,GDT_Byte,0,0);

   //清除内存

    CPLFree(buffTmpR);
     CPLFree(buffTmpG);
      CPLFree(buffTmpB);
        CPLFree(buffTmpR1);
     CPLFree(buffTmpG1);
      CPLFree(buffTmpB1);
   //关闭dataset
   GDALClose(poDstDS);
   GDALClose(poSrcDS1);
    GDALClose(poSrcDS2);
   system("PAUSE");
   return 0;
}
