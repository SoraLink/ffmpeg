#ifndef WAVEFILE_H
#define WAVEFILE_H

#include<string>
using namespace std;

class WaveFile
{
public:
    struct wavehead
    {
        char sign[4];
        unsigned long int flength;
        char wavesign[4];
        char fmtsign[4];
        unsigned long int unused;
        unsigned short formattype;
        unsigned short channelnum;
        unsigned long int samplerate;
        unsigned long int transferrate;
        unsigned short int adjustnum;
        unsigned short int databitnum;
        char deathDate[4];
        char SubChunkj2ID[4];
        unsigned long int datalength;
    }head;
    unsigned long int totalsample;
    unsigned long int bitpersample;
    unsigned long int datanum;

    short *Data;

    WaveFile();
    ~WaveFile(){}
    void WavRead(string filename);
};

#endif // WAVEFILE_H
