#ifndef DMFREADER_H
#define DMFREADER_H

#include "CmtdFile.h"

class CMarkup;
class CDMFReader
{
public:
    CDMFReader();
    CDMFReader(CCmtdFile* pCmtdFile);
    virtual ~CDMFReader();
    bool readFile(const QString& strPath);
    bool saveFile(const QString& strPath);
protected:
    bool readComtradeModel();
    bool readBus();
    bool readLine();
    bool readTrans();
    bool readGenerator();
    bool readExciter();
    bool readWinding(CEleTrans* pTrans);
    bool readAChanel();
    bool readDChanel();

    bool writeAChanel();
    bool writeDChanel();
    bool writeBus();
    bool writeLine();
    bool writeTrans();
    bool writeGenerator();
    bool writeExciter();
public:
    CCmtdFile* m_pCmtdFile;
    CMarkup* m_pDMF;
};

#endif // DMFREADER_H
