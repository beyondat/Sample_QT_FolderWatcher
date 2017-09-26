#ifndef FOLDERUPDATER_H
#define FOLDERUPDATER_H
#include <QObject>
#include <QDebug>
#include <QFileSystemWatcher>
#include <QDirIterator>

class FolderUpdater : public QObject
{
    Q_OBJECT
public:
    FolderUpdater(QObject* _obj=0) : QObject(_obj)
    {

    }
    ~FolderUpdater()
    {

    }
    QMap<QString, QStringList> _currContents; //maintain list of current contents of each watched directory

public slots:
   void doFolderUpdater(QString path)
   {
    qDebug()<<"[doFolderUpdater]getUpdate"<<path;

      QStringList currEntryList = _currContents[path];
      const QDir dir(path);

      QStringList newEntryList = dir.entryList(QDir::NoDotAndDotDot  | QDir::AllDirs | QDir::Files, QDir::DirsFirst);

      QSet<QString> newDirSet = QSet<QString>::fromList( newEntryList );

      QSet<QString> currentDirSet = QSet<QString>::fromList( currEntryList );

     // Files that have been added
      QSet<QString> newFiles = newDirSet - currentDirSet;
      QStringList newFile = newFiles.toList();

     // Files that have been removed
      QSet<QString> deletedFiles = currentDirSet - newDirSet;
      QStringList deleteFile = deletedFiles.toList();

     // Update the current set
      _currContents[path] = newEntryList;

     if(!newFile.isEmpty() && !deleteFile.isEmpty())
     {
         // File/Dir is renamed

         if(newFile.count() == 1 && deleteFile.count() == 1)
         {
             qDebug()<<"File Renamed from "<<newFile.first()<<" to "<<deleteFile.first();
         }
     }

     else
     {
          // New File/Dir Added to Dir
          if(!newFile.isEmpty())
          {

               qDebug()<<"New Files/Dirs added: "<<newFile;

               foreach(QString file, newFile)
               {
                       //Handle Operation on new files.....
               }
          }

          // File/Dir is deleted from Dir

          if(!deleteFile.isEmpty())
          {
              qDebug()<<"Files/Dirs deleted: "<<deleteFile;
              foreach(QString file, deleteFile)
              {
                  // Handle operation of each deleted file....
              }
          }

      }
   }
   void doFileUpdater(QString _str)
   {
    qDebug()<<"[doFileUpdater]getUpdate"<<_str;
   }
};

#endif // FOLDERUPDATER_H
