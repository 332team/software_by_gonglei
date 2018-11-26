#include <iostream>
#include <math.h>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")

int main()
{
    //����ͼ������
   GDALDataset* poSrcDSdgp;
    //����ͼ��ȫɫ
   GDALDataset* poSrcDSqs;
   //���ͼ��
   GDALDataset* poDstDS;
   //ͼ��Ŀ�Ⱥ͸߶�
   int imgXlen,imgYlen;
   //����ͼ������·��
   char* srcPathdgp = "duoguangpu.bmp";
   //����ͼ��ȫɫ·��
   char* srcPathqs = "quanse.bmp";
   //���ͼ��·��
   char* dstPath = "res.tif";
   //ͼ��RGB����
   float* buffTmpR,* buffTmpG,* buffTmpB;
  //ͼ��IHS����
   float* buffTmpI,* buffTmpH,* buffTmpS;
   //ͼ�񲨶���
   int i,j,bandNum,a,b;
   //GRB --> IHS
   float tran1[3][3] = {1/3,1/3,1/3,//rgb -->i
            -sqrt(2.0f)/6,-sqrt(2.0f)/6,sqrt(2.0f)/3,//rgb -->h
            1/sqrt(2.0f),-1/sqrt(2.0f),0};//rgb -->s
   //IHS --> RGB
   float tran2[3][3] = {1,-1/sqrt(2.0f),1/sqrt(2.0f),//ihs -->r
            1,-1/sqrt(2.0f),-1/sqrt(2.0f),//ihs --> g
            1,sqrt(2.0f),0};//ihs --> b
   //ע������
   GDALAllRegister();
   //��ͼ��
   poSrcDSdgp = (GDALDataset*)GDALOpenShared(srcPathdgp,GA_ReadOnly);
   poSrcDSqs = (GDALDataset*)GDALOpenShared(srcPathqs,GA_ReadOnly);
   //��ȡͼ��Ŀ�ȣ��߶ȺͲ�����
   imgXlen = poSrcDSdgp->GetRasterXSize();
   imgYlen = poSrcDSdgp->GetRasterYSize();
   bandNum = poSrcDSdgp->GetRasterCount();
   //����ͼ��Ŀ�Ⱥ͸߶ȷ����ڴ�
   buffTmpR = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));
   buffTmpG = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));
   buffTmpB = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));
   buffTmpI = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));
   buffTmpH = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));
   buffTmpS = (float*)CPLMalloc(imgXlen*imgYlen*sizeof(float));
   //�������ͼ��
   poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
     dstPath,imgXlen,imgYlen,bandNum,GDT_Byte,NULL);
   //��������ͼ���RGB
   poSrcDSdgp->GetRasterBand(1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpR,imgXlen,imgYlen,GDT_Float32,0,0);
   poSrcDSdgp->GetRasterBand(2)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpG,imgXlen,imgYlen,GDT_Float32,0,0);
   poSrcDSdgp->GetRasterBand(3)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpB,imgXlen,imgYlen,GDT_Float32,0,0);
   //����ȫɫͼ���R
   poSrcDSqs->GetRasterBand(1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpI,imgXlen,imgYlen,GDT_Float32,0,0);

          for(int i = 0;i < imgYlen;i ++)
          for(int j = 0;j < imgXlen;j ++)
          {
              //�������ͼ���RGBת��ΪHS
              buffTmpH[i * imgXlen + j] = buffTmpR[i * imgXlen + j] * tran1[1][0] + buffTmpG[i * imgXlen + j] * tran1[1][1] + buffTmpB[i * imgXlen + j] * tran1[1][2];
              buffTmpS[i * imgXlen + j] = buffTmpR[i * imgXlen + j] * tran1[2][0] + buffTmpG[i * imgXlen + j] * tran1[2][1] + buffTmpB[i * imgXlen + j] * tran1[2][2];
            //��IHSת��ΪRGB
              buffTmpR[i * imgXlen + j] = buffTmpI[i * imgXlen + j] * tran2[0][0] + buffTmpH[i * imgXlen + j] * tran2[0][1] + buffTmpS[i * imgXlen + j] * tran2[0][2];
              buffTmpG[i * imgXlen + j] = buffTmpI[i * imgXlen + j] * tran2[1][0] + buffTmpH[i * imgXlen + j] * tran2[1][1] + buffTmpS[i * imgXlen + j] * tran2[1][2];
              buffTmpB[i * imgXlen + j] = buffTmpI[i * imgXlen + j] * tran2[2][0] + buffTmpH[i * imgXlen + j] * tran2[2][1] + buffTmpS[i * imgXlen + j] * tran2[2][2];
          }
          //���ͼ��
       poDstDS->GetRasterBand(1)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpR,imgXlen,imgYlen,GDT_Float32,0,0);
       poDstDS->GetRasterBand(2)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpG,imgXlen,imgYlen,GDT_Float32,0,0);
       poDstDS->GetRasterBand(3)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpB,imgXlen,imgYlen,GDT_Float32,0,0);


   //����ڴ�
   CPLFree(buffTmpR);
   CPLFree(buffTmpG);
   CPLFree(buffTmpB);
   CPLFree(buffTmpI);
   CPLFree(buffTmpH);
   CPLFree(buffTmpS);
   //�ر�dataset
   GDALClose(poDstDS);
   GDALClose(poSrcDSdgp);
   GDALClose(poSrcDSqs);
   system("PAUSE");
   return 0;
}
