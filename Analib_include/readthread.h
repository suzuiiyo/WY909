#ifndef READTHREAD_H
#define READTHREAD_H

#include <QThread>

class CCmtdFile;
class ReadThread : public QThread
{
    Q_OBJECT
public:
    explicit ReadThread(QObject *parent = 0);
    void setFileInfo(CCmtdFile* pFileInfo);
    virtual void run();
    void setExitFlag();
    void Read_BinaryFile();
    void Read_AsciiFile();
signals:
    void SIG_ReadData_Begin();                   //开始读取信号(可在收到此信号后创建进度条)
    void SIG_ReadData_Percent(int a_nPercent);   //设置进度
    void SIG_ReadData_Finished();                //读取结束（可销毁进度条）
    void SIG_ReadData_Segment();                 //已经加载了一段(可显示波形了)

public slots:

private:
    CCmtdFile* m_pFileInfo;
    volatile bool m_bExit;
};

#endif // READTHREAD_H
