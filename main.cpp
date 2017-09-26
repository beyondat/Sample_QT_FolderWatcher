#include <QCoreApplication>

#include "folderupdater.h"

void watch( QObject* ca, const QString& dir )
{
    QFileSystemWatcher* wc = new QFileSystemWatcher(ca);
    wc->addPath(dir);
    wc->addPath("C:/C/새 텍스트 문서.txt");
    wc->addPath("C:/C/2016 하반기 신규입사자 소개_황병대.pptx");

    FolderUpdater* fu = new FolderUpdater(ca);

    QObject::connect(wc, SIGNAL(directoryChanged(QString)), fu, SLOT(doFolderUpdater(QString)));
    QObject::connect(wc, SIGNAL(fileChanged(QString)), fu, SLOT(doFileUpdater(QString)));
    QFileInfo f(dir);

    if(f.isDir())
    {
         const QDir dirw(dir);
         fu->_currContents[dir] = dirw.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
         wc->addPaths(dirw.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst));
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    const QString dir = "C:/C";
    watch(&a,dir);
    qDebug() << "Started watching " << dir;
    return a.exec();
}
