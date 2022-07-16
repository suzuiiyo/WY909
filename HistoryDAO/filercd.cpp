#include "filercd.h"
FileRcd::FileRcd()
    : m_time(0)
    , m_nPullCount(0)
    , m_pullingState(0)
    , m_tranisentTaskState(0)
{

}

FileRcd::FileRcd(const QString &name, qint64 time)
    : m_name(name)
    , m_time(time)
    , m_nPullCount(0)
    , m_pullingState(0)
    , m_tranisentTaskState(0)
{

}

void FileRcd::addFile(const QString &strFile)
{
    if(!m_lstFile.contains(strFile))
        m_lstFile.append(strFile);
}
