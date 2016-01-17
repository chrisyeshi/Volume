#ifndef VOLUMEGLCUDA_H
#define VOLUMEGLCUDA_H

#include "volumegl.h"
#include "volumecuda.h"
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

struct cudaGraphicsResource;

namespace yy {

template <class TVolumeGL>
class TVolumeGLCUDA : public virtual IVolumeGL, public virtual IVolumeCUDA
{
public:
	TVolumeGLCUDA(const std::shared_ptr<IVolume>& volume)
      : resource(nullptr)
    {
        std::shared_ptr<IVolumeGL> volGL = std::dynamic_pointer_cast<IVolumeGL>(volume);
        if (!volGL)
            volGL.reset(new TVolumeGL(volume));
        this->volume = volGL;
    }
    virtual ~TVolumeGLCUDA()
    {
        // TODO: wrap it with gpuAssert()
        if (resource) cudaGraphicsUnregisterResource(resource);
    }

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
    virtual QSharedPointer<QOpenGLTexture> getTexture() const { return volume->getTexture(); }
    virtual void setFilter(Filter filter) { volume->setFilter(filter); }
    virtual Filter getFilter() const { return volume->getFilter(); }
    virtual cudaGraphicsResource* getCUDAResource() const
    {
        if (!resource)
            cudaGraphicsGLRegisterImage(&resource, volume->getTexture()->textureId(), GL_TEXTURE_3D, cudaGraphicsRegisterFlagsReadOnly);
        return resource;
    }

private:
    std::shared_ptr<IVolumeGL> volume;
    mutable cudaGraphicsResource* resource;
};

typedef TVolumeGLCUDA<VolumeGL> VolumeGLCUDA;

} // namespace yy

#endif // VOLUMEGLCUDA_H
