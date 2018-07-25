#include "descriptor.h"

Descriptor::Descriptor(QObject *parent)
    : QObject(parent)
{
}

Descriptor::Descriptor(int objID, int id, QString name, double data)
    :objId_(objID), id_(id), name_(name), data_(data)
{

}

Descriptor::Descriptor(const Descriptor &other)
{
    if(this->id() == other.id() && this->objId() == other.objId())
    {
        this->setData( other.data() );
    }
}

Descriptor &Descriptor::operator =(const Descriptor &d)
{
    if (this->id() == d.id() && this->objId() == d.objId())
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

double Descriptor::data() const
{
    return data_;
}

void Descriptor::setData(const double &data)
{
    data_ = data;
}

int Descriptor::objId() const
{
    return objId_;
}

void Descriptor::setObjId(int objId)
{
    objId_ = objId;
}

bool operator ==(const Descriptor &d1, const Descriptor &d2)
{
    bool objEqual = (d1.objId() == d2.objId() ? true : false);
    bool idEqual = (d1.id() == d2.id() ? true : false);
    bool valueEqual = (d1.data() == d2.data() ? true : false);
    return objEqual && idEqual && valueEqual;
}

QDebug operator<< (QDebug dbg, Descriptor *dsc)
{
    dbg << "\tДескриптор " << dsc->objId()<<dsc->id() << ":" << dsc->name() << " = " << dsc->data();
    return  dbg.nospace();
}
