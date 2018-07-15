#include "obj.h"

Obj::Obj(QObject *parent) : QObject(parent)
{

}

Obj::Obj(const Obj &other)
{
    if ( (this->id() == other.id()) && (descriptors_.count() == other.descriptors().count()) )
    {
        this->setName( other.name() );
        for(int i = 0; i < descriptors_.count(); i++)
        {
            descriptors_.at(i)->setId(other.descriptors().at(i)->id());
            descriptors_.at(i)->setName(other.descriptors().at(i)->name());
            descriptors_.at(i)->setData(other.descriptors().at(i)->data());
        }
    }
}

Obj::Obj(int id, QString name)
    :id_(id), name_(name)
{
}

Obj::Obj(int id, QString name, QVector<Descriptor *> &descriptors)
    :id_(id), name_(name)
{
    for(int i = 0; i < descriptors.count(); i++)
    {
        Descriptor *desc = new Descriptor(descriptors.at(i)->id(), descriptors.at(i)->name(), descriptors.at(i)->data());
        descriptors_.push_back(desc);
    }
}

Obj &Obj::operator =(const Obj &o)
{
    if( (this->id() == o.id()) && (descriptors_.count() == o.descriptors().count()) )
    {
        setName(o.name());
        for(int i = 0; i < descriptors_.count(); i++)
        {
            descriptors_.at(i)->setId(o.descriptors().at(i)->id());
            descriptors_.at(i)->setName(o.descriptors().at(i)->name());
            descriptors_.at(i)->setData(o.descriptors().at(i)->data());
        }
        return *this;
    } else
    {
        return *this;
    }
}

int Obj::id() const
{
    return id_;
}

void Obj::setId(int id)
{
    id_ = id;
}

QString Obj::name() const
{
    return name_;
}

void Obj::setName(const QString &name)
{
    name_ = name;
}

QVector<Descriptor *> Obj::descriptors() const
{
    return descriptors_;
}

void Obj::setDescriptors(const QVector<Descriptor *> &descriptors)
{
    descriptors_ = descriptors;
}

void Obj::apendDescriptor(Descriptor *descriptor)
{
    this->descriptors_.push_back(descriptor);
}

bool operator ==(const Obj &o1, const Obj &o2)
{
    if( (o1.id() == o2.id()) && (o1.descriptors().count() == o2.descriptors().count()) )
        return true;
    else
        return false;
}

QDebug operator <<(QDebug dbg, const Obj &o)
{
    dbg << "Объект " << o.id() << " - " << o.name() << ": " << endl;
    foreach (auto desr, o.descriptors()) {
        dbg << desr;
    }
    dbg << "------------------";
}
