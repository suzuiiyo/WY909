#ifndef SWITCHDEVICE_H
#define SWITCHDEVICE_H
#include <QString>
#include <QList>
#include "ied.h"
#include "optport.h"
#include "fibreoptical.h"
class SwitchDevice
{
public:
    typedef QList<SwitchDevice*> List;
public:
    SwitchDevice();
    ~SwitchDevice();
public:
    QString iedName() const;
    OptPort * nextLinePort() const;
    OptPort * lastLinePort() const;
    FibreOptical * nextLine() const;
    FibreOptical * lastLine() const;
public:
    void setIedName(const QString &iedName);
    void setNextLinePort(OptPort *port);
    void setLastLinePort(OptPort *port);
    void setNextLine(FibreOptical *line);
    void setLastLine(FibreOptical *line);
private:
    QString m_iedName;
    OptPort *m_pNextLinePort;
    OptPort *m_pLastLinePort;
    FibreOptical *m_pLastLine;
    FibreOptical *m_pNextLine;
};

inline QString SwitchDevice::iedName() const
{ return m_iedName;}

inline void SwitchDevice::setIedName(const QString &iedName)
{ m_iedName = iedName;}

inline OptPort * SwitchDevice::nextLinePort() const
{ return m_pNextLinePort;}

inline void SwitchDevice::setNextLinePort(OptPort *port)
{ m_pNextLinePort = port;}

inline OptPort * SwitchDevice::lastLinePort() const
{ return m_pLastLinePort;}

inline void SwitchDevice::setLastLinePort(OptPort *port)
{ m_pLastLinePort = port;}

inline FibreOptical * SwitchDevice::nextLine() const
{ return m_pNextLine;}

inline void SwitchDevice::setNextLine(FibreOptical *line)
{ m_pNextLine = line;}

inline FibreOptical * SwitchDevice::lastLine() const
{ return m_pLastLine;}

inline void SwitchDevice::setLastLine(FibreOptical *line)
{ m_pLastLine = line;}
#endif // SWITCHDEVICE_H
