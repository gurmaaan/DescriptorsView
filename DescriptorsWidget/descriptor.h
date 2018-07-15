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
    Descriptor(int id, QString name, QVariant data);
    Descriptor(const Descriptor &other);

    Descriptor &operator =(const Descriptor &d);

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    QVariant data() const;
    void setData(const QVariant &data);

signals:

public slots:

private:
    int id_;
    QString name_;
    QVariant data_;
};

Q_DECLARE_METATYPE(Descriptor);

bool operator ==(const Descriptor &d1, const Descriptor &d2);
QDebug operator <<(QDebug dbg, const Descriptor &dsc);
#endif // DESCRIPTOR_H
