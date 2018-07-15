#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QDebug>
#include "descriptor.h"

class Obj : public QObject
{
    Q_OBJECT
public:
    explicit Obj(QObject *parent = nullptr);
    Obj(const Obj &other);
    Obj(int id, QString name);
    Obj(int id, QString name, QVector<Descriptor *> &descriptors);

    Obj &operator =(const Obj &o);

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    QVector<Descriptor *> descriptors() const;
    void setDescriptors(const QVector<Descriptor *> &descriptors);
    void apendDescriptor(Descriptor *descriptor);

signals:

public slots:

private:
    int id_;
    QString name_;
    QVector<Descriptor *> descriptors_;
};

Q_DECLARE_METATYPE(Obj);

bool operator ==(const Obj &o1, const Obj &o2);
QDebug operator <<(QDebug dbg, const Obj &o);

#endif // OBJECT_H
