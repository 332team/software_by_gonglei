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
   //��ʼλ������
   int StartX = 100,StartY = 100;
   //�����Ⱥ͸߶�
   int tmpXlen = 200,tmpYlen = 150;
   //����ͼ��·��
   char* srcPath = "may.jpg";
   //���ͼ��·��
   char* dstPath = "res.tif";
   //ͼ���ڴ�洢,�ı������ڴ�洢
   GByte* buffTmp,*buffTmp1;
   //ͼ�񲨶���
   int i,j,bandNum;
   //ע������
   GDALAllRegister();
   //��ͼ��
   poSrcDS = (GDALDataset*)GDALOpenShared(srcPath,GA_ReadOnly);
    //��ȡͼ��Ŀ�ȣ��߶ȺͲ�����
   imgXlen = poSrcDS->GetRasterXSize();
   imgYlen = poSrcDS->GetRasterYSize();
   bandNum = poSrcDS->GetRasterCount();

   //����ͼ��Ŀ�Ⱥ͸߶ȷ����ڴ�
   buffTmp1 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
//�������ͼ��
   poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
     dstPath,imgXlen,imgYlen,bandNum,GDT_Byte,NULL);
//��ͼƬ������½���ͼƬ
        for(i = 0;i < bandNum;i ++)
   {
       poSrcDS->GetRasterBand(i + 1)->RasterIO(
        GF_Read,0,0,imgXlen,imgYlen,buffTmp1,imgXlen,imgYlen,GDT_Byte,0,0);
       poDstDS->GetRasterBand(i + 1)->RasterIO(
        GF_Write,0,0,imgXlen,imgYlen,buffTmp1,imgXlen,imgYlen,GDT_Byte,0,0);


   }
   //�����ڴ�
   buffTmp = (GByte*)CPLMalloc(tmpXlen*tmpYlen*sizeof(GByte));
   //��ȡ��ɫͨ��������buffTmp�У�ֻ��Ϊ�˻�ȡ������
   poSrcDS->GetRasterBand(1)->RasterIO(GF_Read,StartX,StartY,tmpXlen,tmpYlen,buffTmp,tmpXlen,tmpYlen,GDT_Byte,0,0);
   //�������򣬽��½�ͼƬ������ı���ɫ
   for(j = 0;j < tmpYlen;j ++)
    for(i = 0;i < tmpXlen;i ++)
   {
       buffTmp[j * tmpXlen  +i] = (GByte)255;
   }

   poDstDS->GetRasterBand(1)->RasterIO(GF_Write,StartX,StartY,tmpXlen,tmpYlen,buffTmp,tmpXlen,tmpYlen,GDT_Byte,0,0);



   //����ڴ�
   CPLFree(buffTmp);
   CPLFree(buffTmp1);
   //�ر�dataset
   GDALClose(poDstDS);
   GDALClose(poSrcDS);
   system("PAUSE");
   return 0;
}
