#ifndef OBJ_H
#define OBJ_H

#include <QObject>
#include <QDebug>
#include <QStandardItem>

#include "Services/itemsservice.h"
#include "Services/stringservice.h"
#include "descriptor.h"

class Obj : public QObject
{
    Q_OBJECT
public:
    explicit Obj(QObject *parent = nullptr);
    Obj(const Obj &o);
    Obj(int id, QString fullName);
    Obj(int id, QString fullName, QVector<Descriptor *> &descriptors);

    Obj &operator =(const Obj &o);

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    QVector<Descriptor *> descriptors() const;
    void setDescriptors(const QVector<Descriptor *> &descriptors);
    void apendDescriptor(Descriptor *descriptor);

    QList<QStandardItem *> modelRow();
    QStandardItem *rowVerticalHeader();

    QString fullName() const;
    void setFullName(const QString &fullName);

signals:

public slots:

private:
    int id_;
    QString name_;
    QString fullName_;
    QVector<Descriptor *> descriptors_;

    ItemsService *is_;
};

Q_DECLARE_METATYPE(Obj);

bool operator ==(const Obj &o1, const Obj &o2);
QDebug operator <<(QDebug dbg, const Obj *o);

#endif // OBJ_H
