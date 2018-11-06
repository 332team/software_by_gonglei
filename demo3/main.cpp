#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")
/*
ֱ�ӽ�Superman������space�ϲ��У�ֻ�ܰ�space��rgb�ĵ�
int main()
{
   //����ͼ��space Superman
   GDALDataset* poSrcDS1;
   GDALDataset* poSrcDS2;
   //���ͼ��
   GDALDataset* poDstDS;
   //ͼ��Ŀ�Ⱥ͸߶�
   int imgXlen,imgYlen;
   //r g b
    GByte r,g,b;
   //����ͼ��·��
   char* srcPath1 = "space.jpg";
   char* srcPath2 = "superman.jpg";
   //���ͼ��·��
   char* dstPath = "res.tif";
   //ͼ���ڴ�洢
   GByte* buffTmp;
   //�洢superman����ͨ��
   GByte* buffTmpR;
   GByte* buffTmpG;
   GByte* buffTmpB;
   //�洢space����ͨ��
   GByte* buffTmpR1;
   GByte* buffTmpG1;
   GByte* buffTmpB1;
   //ͼ�񲨶���
   int i,j,bandNum;
   //ע������
   GDALAllRegister();
   //��ͼ��space
   poSrcDS1 = (GDALDataset*)GDALOpenShared(srcPath1,GA_ReadOnly);
    //��ȡͼƬsuperman
   poSrcDS2 = (GDALDataset*)GDALOpenShared(srcPath2,GA_ReadOnly);


    //��ȡͼ��Ŀ�ȣ��߶ȺͲ�����
   imgXlen = poSrcDS1->GetRasterXSize();
   imgYlen = poSrcDS1->GetRasterYSize();
   bandNum = poSrcDS1->GetRasterCount();

   //����ͼ��Ŀ�Ⱥ͸߶ȷ����ڴ�
   buffTmp = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
//�������ͼ��
   poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
     dstPath,imgXlen,imgYlen,bandNum,GDT_Byte,NULL);
//free
//��ͼƬ������½���ͼƬ
       for(i = 0;i < bandNum;i ++)
   {
       poSrcDS1->GetRasterBand(i + 1)->RasterIO(
        GF_Read,0,0,imgXlen,imgYlen,buffTmp,imgXlen,imgYlen,GDT_Byte,0,0);
       poDstDS->GetRasterBand(i + 1)->RasterIO(
        GF_Write,0,0,imgXlen,imgYlen,buffTmp,imgXlen,imgYlen,GDT_Byte,0,0);


   }





       //���Superman1,2,3ͨ��
       buffTmpR = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
       buffTmpG = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
       buffTmpB = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
       poSrcDS2->GetRasterBand(1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpR,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS2->GetRasterBand(2)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpG,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS2->GetRasterBand(3)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpB,imgXlen,imgYlen,GDT_Byte,0,0);


   //10<r<160; ����2��100<g<220; ����3��10<b<110,������Χ



       for(j = 0;j < imgYlen;j ++)
        for(i = 0;i < imgXlen;i ++)
       {

          //��õ�ǰ���ص�rgb
           r = buffTmpR[j * imgXlen  +i];
           g = buffTmpG[j * imgXlen  +i];
           b = buffTmpB[j * imgXlen  +i];
           if(!(r > 10 && r < 160 && g > 100 && g < 220 && b > 10 && b < 110))//���Ǳ�������Superman
          {
       poDstDS->GetRasterBand(1)->RasterIO(GF_Write,i,j,1,1,buffTmpR,imgXlen,imgYlen,GDT_Byte,0,0);
       poDstDS->GetRasterBand(2)->RasterIO(GF_Write,i,j,1,1,buffTmpG,imgXlen,imgYlen,GDT_Byte,0,0);
       poDstDS->GetRasterBand(3)->RasterIO(GF_Write,i,j,1,1,buffTmpB,imgXlen,imgYlen,GDT_Byte,0,0);


           }
       }
 //���޸ĺ��ͼƬ���


   //����ڴ�
CPLFree(buffTmp);
    CPLFree(buffTmpR);
     CPLFree(buffTmpG);
      CPLFree(buffTmpB);

   //�ر�dataset
   GDALClose(poDstDS);
   GDALClose(poSrcDS1);
    GDALClose(poSrcDS2);
   system("PAUSE");
   return 0;
}

*/
int main()
{
   //����ͼ��space Superman
   GDALDataset* poSrcDS1;
   GDALDataset* poSrcDS2;
   //���ͼ��
   GDALDataset* poDstDS;
   //ͼ��Ŀ�Ⱥ͸߶�
   int imgXlen,imgYlen;
   //r g b
    GByte r,g,b;
   //����ͼ��·��
   char* srcPath1 = "space.jpg";
   char* srcPath2 = "superman.jpg";
   //���ͼ��·��
   char* dstPath = "res.tif";
   //ͼ���ڴ�洢
   GByte* buffTmp;
   //�洢superman����ͨ��
   GByte* buffTmpR;
   GByte* buffTmpG;
   GByte* buffTmpB;
   //�洢space����ͨ��
   GByte* buffTmpR1;
   GByte* buffTmpG1;
   GByte* buffTmpB1;
   //ͼ�񲨶���
   int i,j,bandNum;
   //ע������
   GDALAllRegister();
   //��ͼ��space
   poSrcDS1 = (GDALDataset*)GDALOpenShared(srcPath1,GA_ReadOnly);
    //��ȡͼƬsuperman
   poSrcDS2 = (GDALDataset*)GDALOpenShared(srcPath2,GA_ReadOnly);

    //��ȡͼ��space�Ŀ�ȣ��߶ȺͲ�����������ͼƬһ����
   imgXlen = poSrcDS1->GetRasterXSize();
   imgYlen = poSrcDS1->GetRasterYSize();
   bandNum = poSrcDS1->GetRasterCount();

//�������ͼ��
   poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
     dstPath,imgXlen,imgYlen,bandNum,GDT_Byte,NULL);




       //���Superman1,2,3ͨ��
       buffTmpR = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
       buffTmpG = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
       buffTmpB = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
       poSrcDS2->GetRasterBand(1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpR,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS2->GetRasterBand(2)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpG,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS2->GetRasterBand(3)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpB,imgXlen,imgYlen,GDT_Byte,0,0);
       // ���space 1,2,3ͨ��
       buffTmpR1 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
       buffTmpG1 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
       buffTmpB1 = (GByte*)CPLMalloc(imgXlen*imgYlen*sizeof(GByte));
       poSrcDS1->GetRasterBand(1)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpR1,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS1->GetRasterBand(2)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpG1,imgXlen,imgYlen,GDT_Byte,0,0);
       poSrcDS1->GetRasterBand(3)->RasterIO(GF_Read,0,0,imgXlen,imgYlen,buffTmpB1,imgXlen,imgYlen,GDT_Byte,0,0);

   //10<r<160; ����2��100<g<220; ����3��10<b<110,������Χ



       for(j = 0;j < imgYlen;j ++)
        for(i = 0;i < imgXlen;i ++)
       {
          //��õ�ǰ���ص�rgb
           r = buffTmpR[j * imgXlen  +i];
           g = buffTmpG[j * imgXlen  +i];
           b = buffTmpB[j * imgXlen  +i];
           if(!(r > 10 && r < 160 && g > 100 && g < 220 && b > 10 && b < 110))//���Ǳ�������Superman
           {
            //��space��rgb�ĳ�Superman
            buffTmpR1[j * imgXlen  +i] = r;
            buffTmpG1[j * imgXlen  +i] = g;
            buffTmpB1[j * imgXlen  +i] = b;


           }
       }
 //���޸ĺ��ͼƬ���
       poDstDS->GetRasterBand(1)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpR1,imgXlen,imgYlen,GDT_Byte,0,0);
       poDstDS->GetRasterBand(2)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpG1,imgXlen,imgYlen,GDT_Byte,0,0);
       poDstDS->GetRasterBand(3)->RasterIO(GF_Write,0,0,imgXlen,imgYlen,buffTmpB1,imgXlen,imgYlen,GDT_Byte,0,0);

   //����ڴ�

    CPLFree(buffTmpR);
     CPLFree(buffTmpG);
      CPLFree(buffTmpB);
        CPLFree(buffTmpR1);
     CPLFree(buffTmpG1);
      CPLFree(buffTmpB1);
   //�ر�dataset
   GDALClose(poDstDS);
   GDALClose(poSrcDS1);
    GDALClose(poSrcDS2);
   system("PAUSE");
   return 0;
}
