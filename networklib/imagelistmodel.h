#ifndef IMAGELISTMODEL_H
#define IMAGELISTMODEL_H

#include <QObject>
#include<QAbstractListModel>
#include<imagefile.h>

class ImageListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ImageListModel(QObject *parent = nullptr);
    enum UserRoles{
        UserRole=Qt::UserRole+1
    };

    QHash<int,QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index,int role) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;

    bool existes(QUrl imageUrl);

    bool removeRows(int row=0, int count=0, const QModelIndex &parent=QModelIndex());

    void addImage(ImageFile* u);
    /// if there is an empty or default image will returns it else returns nullptr
    ImageFile* getNewImage();
    ImageFile* getImage(int fileId);
    QList<ImageFile*> getList();
signals:
    void scrolledToEnd() const;
public slots:
    void imageDeleted();
private:
    QList<ImageFile*> m_List;

};

#endif // IMAGELISTMODEL_H
