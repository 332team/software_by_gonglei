#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")

int main()
{
    //����ͼ��
   GDALDataset* poSrcDS;
   //���ͼ��
   GDALDataset* poDstDS;
   //ͼ��Ŀ�Ⱥ͸߶�
   int imgXlen,imgYlen;
   //��ʼλ�����꣬��ɫ�ͺ�ɫ
   int StartX1 = 300,StartY1 = 300;
   int StartX2 = 500,StartY2 = 500;
   //�����Ⱥ͸߶ȣ���ɫ��ɫ
   int tmpXlen1 = 200,tmpYlen1 = 50;
   int tmpXlen2 = 50,tmpYlen2 = 100;
   //����ͼ��·��
   char* srcPath = "may.jpg";
   //���ͼ��·��
   char* dstPath = "res.tif";
   //ͼ���ڴ�洢
   GByte* buffTmp;
   //ͼ�񲨶���
   int i,j,bandNum,k;
   //ע������
   GDALAllRegister();
   //��ͼ��
   poSrcDS = (GDALDataset*)GDALOpenShared(srcPath,GA_ReadOnly);
    //��ȡͼ��Ŀ�ȣ��߶ȺͲ�����
   imgXlen = poSrcDS->GetRasterXSize();
   imgYlen = poSrcDS->GetRasterYSize();
   bandNum = poSrcDS->GetRasterCount();

   //����ͼ��Ŀ�Ⱥ͸߶ȷ����ڴ�
   buffTmp = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
//�������ͼ��
   poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
     dstPath,imgXlen,imgYlen,bandNum,GDT_Byte,NULL);
//free
//��ͼƬ������½���ͼƬ
       for(i = 0;i < bandNum;i ++)
   {
       poSrcDS->GetRasterBand(i + 1)->RasterIO(
        GF_Read,0,0,imgXlen,imgYlen,buffTmp,imgXlen,imgYlen,GDT_Byte,0,0);
       poDstDS->GetRasterBand(i + 1)->RasterIO(
        GF_Write,0,0,imgXlen,imgYlen,buffTmp,imgXlen,imgYlen,GDT_Byte,0,0);


   }
CPLFree(buffTmp);
   //�����ɫ�����ڴ�
buffTmp = (GByte*)CPLMalloc(tmpXlen1*tmpYlen1*sizeof(GByte));

for(k = 1;k <= 3;k ++)
{
    //���λ�ȡͨ��1 2 3������bufftmp
   poSrcDS->GetRasterBand(k)->RasterIO(GF_Read,StartX1,StartY1,tmpXlen1,tmpYlen1,buffTmp,tmpXlen1,tmpYlen1,GDT_Byte,0,0);
   //�������򣬽��½�ͼƬ������ı���ɫ
   for(j = 0;j < tmpYlen1;j ++)
    for(i = 0;i < tmpXlen1;i ++)
   {
       //��255
       buffTmp[j * tmpXlen1  +i] = (GByte)255;
   }
   poDstDS->GetRasterBand(k)->RasterIO(GF_Write,StartX1,StartY1,tmpXlen1,tmpYlen1,buffTmp,tmpXlen1,tmpYlen1,GDT_Byte,0,0);
}
CPLFree(buffTmp);
   //�����ɫ�����ڴ�
   buffTmp = (GByte*)CPLMalloc(tmpXlen2*tmpYlen2*sizeof(GByte));
   //��ȡ��ɫͨ��������buffTmp�У�ֻ��Ϊ�˻�ȡ������
   for(k = 1;k <= 3;k ++)
   {
       //���λ��1,2,3ͨ��
       poSrcDS->GetRasterBand(k)->RasterIO(GF_Read,StartX2,StartY2,tmpXlen2,tmpYlen2,buffTmp,tmpXlen2,tmpYlen2,GDT_Byte,0,0);

       for(j = 0;j < tmpYlen2;j ++)
        for(i = 0;i < tmpXlen2;i ++)
       {
           //��0
           buffTmp[j * tmpXlen2  +i] = (GByte)0;
       }
       poDstDS->GetRasterBand(k)->RasterIO(GF_Write,StartX2,StartY2,tmpXlen2,tmpYlen2,buffTmp,tmpXlen2,tmpYlen2,GDT_Byte,0,0);
   }

   //����ڴ�
   CPLFree(buffTmp);
   //�ر�dataset
   GDALClose(poDstDS);
   GDALClose(poSrcDS);
   system("PAUSE");
   return 0;
}
