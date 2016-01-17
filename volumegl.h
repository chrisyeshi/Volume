#ifndef VOLUMEGL_H
#define VOLUMEGL_H

#include "volumefilter.h"
#include <memory>
#include <map>
#include <QSharedPointer>
#include <QOpenGLTexture>

namespace yy {

class IVolumeGL : public virtual IVolumeFilter
{
public:
    virtual QSharedPointer<QOpenGLTexture> getTexture() const = 0;
};

class VolumeGL : public IVolumeGL
{
public:
    VolumeGL(const std::shared_ptr<IVolume>& volume);

    virtual int w() const { return volume->w(); }
    virtual int h() const { return volume->h(); }
    virtual int d() const { return volume->d(); }
    virtual float sx() const { return volume->sx(); }
    virtual float sy() const { return volume->sy(); }
    virtual float sz() const { return volume->sz(); }
    virtual DataType pixelType() const { return volume->pixelType(); }
    virtual unsigned int nBytesPerVoxel() const { return volume->nBytesPerVoxel(); }
    virtual unsigned int nBytes() const { return volume->nBytes(); }
    virtual const Stats& getStats() const { return volume->getStats(); }
    virtual const std::unique_ptr<unsigned char []>& getData() const { return volume->getData(); }
    virtual void normalized() { volume->normalized(); }
    virtual QSharedPointer<QOpenGLTexture> getTexture() const;
    virtual void setFilter(Filter filter);
    virtual Filter getFilter() const { return volume->getFilter(); }
    virtual void makeTexture() const;

protected:
    std::shared_ptr<IVolumeFilter> volume;
    mutable QSharedPointer<QOpenGLTexture> texture;

    static std::map<Filter, QOpenGLTexture::Filter> filter2qgl;
};

} // namespace yy

#endif // VOLUMEGL_H
