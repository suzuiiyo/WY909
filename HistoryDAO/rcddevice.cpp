#include "rcddevice.h"
RcdDevice::RcdDevice()
    : m_GUID(0)
    , m_isConnected(false)
    , m_pullFileTime(0)
{

}

RcdDevice::RcdDevice(int guid, const QString &iedName, const QString &ip, const QString &iedCateGory)
    : m_GUID(guid)
    , m_iedName(iedName)
    , m_ip(ip)
    , m_iedCateGory(iedCateGory)
    , m_isConnected(false)
    , m_pullFileTime(0)
{

}

RcdDevice::~RcdDevice()
{
    clearFileRcd();
}

void RcdDevice::setPullFileTime(qint64 time)
{
    if(m_pullFileTime < time)
        m_pullFileTime = time;
}

FileRcd *RcdDevice::fileRcd(const QString &name) const
{
    foreach (FileRcd *file, m_lstFileRcd)
    {
        if(file->name() == name)
            return file;
    }

    return NULL;
}

FileRcd *RcdDevice::getNewestFileRcd() const
{
    bool tip = false;
    qint64 newestTime = 0;
    QString newestFileName = "";
    foreach (FileRcd *file, m_lstFileRcd)
    {
        if(file->pullingState() == 0 && file->time() > newestTime)
        {
            newestTime = file->time();
            newestFileName = file->name();
            tip = true;
        }
    }

    if(tip)
        return this->fileRcd(newestFileName);
    else
        return NULL;
}

void RcdDevice::clearFileRcd()
{
    qDeleteAll(m_lstFileRcd);
    m_lstFileRcd.clear();
}

FileRcd *RcdDevice::addFileRcd(const QString &name, qint64 time)
{
    FileRcd *fileRcd = this->fileRcd(name);
    if(fileRcd == 0)
    {
        fileRcd = new FileRcd(name, time);
        m_lstFileRcd.append(fileRcd);
    }

    return fileRcd;
}

void RcdDevice::removeFileRcd(FileRcd *fileRcd)
{
    m_lstFileRcd.removeAll(fileRcd);
    delete fileRcd;
}

FileRcd *RcdDevice::pullingFileRcd()
{
    foreach (FileRcd *file, m_lstFileRcd)
    {
        if(file->pullingState() == 1)
            return file;
    }

    return 0;
}

bool RcdDevice::havePullingFileRcd() const
{
    foreach (FileRcd *file, m_lstFileRcd)
    {
        if(file->pullingState() == 1)
            return true;
    }

    return false;
}

bool RcdDevice::haveNotPullFileRcd() const
{
    foreach (FileRcd *file, m_lstFileRcd)
    {
        if(file->pullingState() == 0)
            return true;
    }

    return false;
}

bool RcdDevice::haveFileNotPull() const
{
    foreach (FileRcd *file, m_lstNeedPullRcdFile)
    {
        if(file->pullingState() == 0)
            return true;
    }

    return false;
}

FileRcd *RcdDevice::haveFileIsPulling()
{
    foreach (FileRcd *file, m_lstNeedPullRcdFile)
    {
        if(file->pullingState() == 1)
            return file;
    }

    return NULL;
}

void RcdDevice::addRelationIed(const QString &iedName, const QString &ip)
{
    if(m_lstRelationIed.count(iedName) == 0)
        m_lstRelationIed.insert(iedName, ip);
}

void RcdDevice::addTMChannel(RcdDevice::RelationChannel &channel)
{
    m_lstTMChannel.append(channel);
}

void RcdDevice::addTSChannel(RcdDevice::RelationChannel &channel)
{
    m_lstTSChannel.append(channel);
}

void RcdDevice::clearTMChannel()
{
    m_lstTMChannel.clear();
}

void RcdDevice::clearTSChannel()
{
    m_lstTSChannel.clear();
}

//void RcdDevice::adjustLstNeedPullRcdFile()
//{

//}

FileRcd *RcdDevice::hadPullRcdFile(const QString &name) const
{
    if(m_lstHadPullRcdFile.contains(name))
        return m_lstHadPullRcdFile.value(name);
    else
        return NULL;
}

FileRcd *RcdDevice::addHadPullRcdFile(const QString &name, qint64 time)
{
    FileRcd *fileRcd = this->hadPullRcdFile(name);
    if(fileRcd == NULL)
    {
        fileRcd = new FileRcd(name, time);
        m_lstHadPullRcdFile.insert(name, fileRcd);
    }

    return fileRcd;
}

//void RcdDevice::removeHadPullRcdFile(FileRcd *fileRcd)
//{
//    m_lstHadPullRcdFile.removeAll(fileRcd);
//    delete fileRcd;
//}

void RcdDevice::clearHadPullRcdFile()
{
    FileRcd::Hash::const_iterator iter;
    for(iter=m_lstHadPullRcdFile.begin(); iter!=m_lstHadPullRcdFile.end(); iter++)
    {
        FileRcd *file = (FileRcd*)iter.value();

        if(file != NULL)
        {
            delete file;
            file = NULL;
        }
    }
    m_lstHadPullRcdFile.clear();
}

FileRcd *RcdDevice::needPullRcdFile(const QString &name) const
{
    foreach (FileRcd *file, m_lstNeedPullRcdFile)
    {
        if(file->name() == name)
            return file;
    }

    return NULL;
}

FileRcd *RcdDevice::getNewestNeedPullRcdFile() const
{
    int lstSize = m_lstNeedPullRcdFile.size();
    if(lstSize != 0)
    {
        if(lstSize == 1)
            return m_lstNeedPullRcdFile.at(0);
        else
        {
            bool tip = false;
            qint64 newestTime = 0;
            QString newestFileName = "";
            qint64 fileFTime = 0;
            QString fileF = "";
            qint64 fileMTime = 0;
            QString fileM = "";
            qint64 fileSTime = 0;
            QString fileS = "";
            foreach (FileRcd *file, m_lstNeedPullRcdFile)
            {
                if(file->time() > newestTime)
                {
                    newestTime = file->time();
                    newestFileName = file->name();
                    tip = true;
                }
                if(file->name().contains("_F") && file->time()>fileFTime)
                {
                    fileF = file->name();
                    fileFTime = file->time();
                }
                if(file->name().contains("_M") && file->time()>fileMTime)
                {
                    fileM = file->name();
                    fileMTime = file->time();
                }
                if(file->name().contains("_S") && file->time()>fileSTime)
                {
                    fileS = file->name();
                    fileSTime = file->time();
                }
            }

            if(m_iedCateGory == "Prot")
            {
                if(fileF != "")
                {
                    newestFileName = fileF;
                }
                else
                {
                    if(fileM != "")
                    {
                        newestFileName = fileM;
                    }
                    else
                    {
                        if(fileS != "")
                        {
                            newestFileName = fileS;
                        }
                    }
                }
            }

            if(m_iedCateGory == "SR")
            {
                if(fileF != "")
                    newestFileName = fileF;
            }

            if(tip)
                return this->needPullRcdFile(newestFileName);
            else
                return NULL;
        }
    }
    else
        return NULL;
}

FileRcd *RcdDevice::addNeedPullRcdFile(const QString &name, qint64 time)
{
    FileRcd *fileRcd = this->needPullRcdFile(name);
    if(fileRcd == 0)
    {
        fileRcd = new FileRcd(name, time);
        m_lstNeedPullRcdFile.append(fileRcd);
    }

    return fileRcd;
}

void RcdDevice::removeNeedPullRcdFile(FileRcd *fileRcd)
{
    m_lstNeedPullRcdFile.removeAll(fileRcd);
    delete fileRcd;
}

void RcdDevice::clearNeedPullRcdFile()
{
    qDeleteAll(m_lstNeedPullRcdFile);
    m_lstNeedPullRcdFile.clear();
}
