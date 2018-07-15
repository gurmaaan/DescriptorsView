#include "descriptor.h"

Descriptor::Descriptor(QObject *parent)
    : QObject(parent)
{
}

Descriptor::Descriptor(int id, QString name, QVariant data)
    :id_(id), name_(name), data_(data)
{

}

Descriptor::Descriptor(const Descriptor &other)
{
    if(this->id() == other.id())
    {
        this->setData( other.data() );
    }
}

Descriptor &Descriptor::operator =(const Descriptor &d)
{
    if (this->id() == d.id() )
    {
        setData(d.data());
        return *this;
    } else
    {
        return *this;
    }
}

int Descriptor::id() const
{
    return id_;
}

void Descriptor::setId(int id)
{
    id_ = id;
}

QString Descriptor::name() const
{
    return name_;
}

void Descriptor::setName(const QString &name)
{
    name_ = name;
}

QVariant Descriptor::data() const
{
    return data_;
}

void Descriptor::setData(const QVariant &data)
{
    data_ = data;
}

bool operator ==(const Descriptor &d1, const Descriptor &d2)
{
    bool idEqual = (d1.id() == d2.id() ? true : false);
    bool valueEqual = (d1.data() == d2.data() ? true : false);
    return idEqual && valueEqual;
}

QDebug operator <<(QDebug dbg, const Descriptor &dsc)
{
    dbg << "\tДескриптор " << dsc.id() << " : " << dsc.name() << " = " << dsc.data().toString() << endl;
}
