#include "wavefile.h"
#include "iostream"
#include "string.h"
using namespace std;
WaveFile::WaveFile()
{

}

void WaveFile::WavRead(string filename){
    FILE *fp;
    if((fp = fopen(filename.c_str(),"rb"))==NULL)
    {
        exit(0);
    }
    char char_data[4]="";
    char sample[4] = "da";
    fread(&head,sizeof(head),1,fp);
    int temp = sizeof(head);
    int result = strcmp(char_data,sample);
    while(result != 0){
        fread(char_data,2,1,fp);
        result = strcmp(char_data,sample);
    }
    char *char_data2[2];
    fread(char_data2,2,1,fp);
    fread(&head.datalength,4,1,fp);
    totalsample = head.datalength/head.adjustnum;
    bitpersample = head.databitnum / head.channelnum;
    datanum = totalsample*bitpersample/16;
    Data = new short[datanum];
    if(bitpersample==16)
    {
        for(int i=0;!feof(fp) && i <=datanum;i++)
        {
            fread(&Data[i],2,1,fp);
            int temp = Data[i];
            if(head.channelnum==2)
                fseek(fp,2,SEEK_CUR);
        }
    }
    else
    {
        for(int i = 0;!feof(fp)&&i<datanum;i++)
        {
            short low,high;
            fread(&low,1,1,fp);
            if(head.channelnum==2)
                fseek(fp,1,SEEK_CUR);
            fread(&high,1,1,fp);
            if(head.channelnum==2)
                fseek(fp,1,SEEK_CUR);
            Data[i] = (low&0x00ff) | (high<<8 & 0xff00);
        }
    }
    fclose(fp);
}
