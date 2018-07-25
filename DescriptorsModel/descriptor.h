#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include <QObject>
#include <QVariant>
#include <QDebug>

class Obj;

class Descriptor : public QObject
{
    Q_OBJECT
public:
    explicit Descriptor(QObject *parent = nullptr);
    Descriptor(int objID, int id, QString name, double data);
    Descriptor(const Descriptor &other);

    Descriptor &operator =(const Descriptor &d);
    operator QString() const { return QString::number(objId_) + QString::number(id_) + " : " + name_ + " = " + QString::number(data_);}

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    double data() const;
    void setData(const double &data);

    int objId() const;
    void setObjId(int objId);

signals:

public slots:

private:
    int objId_;
    int id_;
    QString name_;
    double data_;
};

Q_DECLARE_METATYPE(Descriptor);

bool operator ==(const Descriptor &d1, const Descriptor &d2);
QDebug operator<< (QDebug dbg, Descriptor *dsc);
#endif // DESCRIPTOR_H
