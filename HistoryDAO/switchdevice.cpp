#include "switchdevice.h"
SwitchDevice::SwitchDevice()
    : m_pNextLinePort(0)
    , m_pLastLinePort(0)
    , m_pLastLine(0)
    , m_pNextLine(0)
{

}

SwitchDevice::~SwitchDevice()
{
    delete m_pNextLinePort;
    delete m_pLastLinePort;
    delete m_pLastLine;
    delete m_pNextLine;
}
