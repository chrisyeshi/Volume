#include "volumegl.h"
#include <cassert>

namespace yy {

std::map<VolumeGL::Filter, QOpenGLTexture::Filter> VolumeGL::filter2qgl
        = { { IVolumeFilter::Filter_Linear, QOpenGLTexture::Linear },
            { IVolumeFilter::Filter_Nearest, QOpenGLTexture::Nearest } };

VolumeGL::VolumeGL(const std::shared_ptr<IVolume>& volume)
{
    std::shared_ptr<IVolumeFilter> volFtr = std::dynamic_pointer_cast<IVolumeFilter>(volume);
    if (!volFtr)
        volFtr.reset(new VolumeFilter(volume));
    this->volume = volFtr;
}

QSharedPointer<QOpenGLTexture> VolumeGL::getTexture() const
{
    if (!texture)
        makeTexture();
    return texture;
}

void VolumeGL::setFilter(Filter filter)
{
    volume->setFilter(filter);
    if (texture)
    {
        assert(filter2qgl.count(filter) > 0);
        texture->setMinMagFilters(filter2qgl[filter], filter2qgl[filter]);
    }
}

void VolumeGL::makeTexture() const
{
    static std::map<Volume::DataType, QOpenGLTexture::PixelType> dt2pt
            = {{Volume::DT_Char, QOpenGLTexture::Int8},
               {Volume::DT_Unsigned_Char, QOpenGLTexture::UInt8},
               {Volume::DT_Float, QOpenGLTexture::Float32}};
    if (0 == dt2pt.count(pixelType()))
    {
        std::cout << "VolumeGL::Unsupported pixel type..." << std::endl;
        return;
    }
    texture = QSharedPointer<QOpenGLTexture>(new QOpenGLTexture(QOpenGLTexture::Target3D));
    texture->setFormat(QOpenGLTexture::R32F);
    texture->setSize(w(), h(), d());
    texture->allocateStorage();
    texture->setData(QOpenGLTexture::Red, dt2pt[pixelType()], getData().get());
    assert(filter2qgl.count(getFilter()) > 0);
    texture->setMinMagFilters(filter2qgl[getFilter()], filter2qgl[getFilter()]);
    texture->setWrapMode(QOpenGLTexture::ClampToEdge);
}

} // namespace yy
