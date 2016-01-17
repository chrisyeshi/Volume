#include <memory>
#include <cassert>
#include <cstdlib>
#include <volume.h>
#include <volumeglcuda.h>

using namespace yy;

class VolumeGLMock : public VolumeGL
{
public:
    VolumeGLMock(const std::shared_ptr<IVolume>& volume) : VolumeGL(volume) {}

protected:
	virtual void makeTexture() const
	{
		texture = QSharedPointer<QOpenGLTexture>(reinterpret_cast<QOpenGLTexture*>(rand()), [](QOpenGLTexture*) {});
	}
};

typedef TVolumeGLCUDA<VolumeGLMock> VolumeGLCUDAMock;

int main()
{
	std::unique_ptr<unsigned char[]> data(new unsigned char [8]);
	std::shared_ptr<Volume> v = std::make_shared<Volume>(data, IVolume::DT_Unsigned_Char, 2, 2, 2);

    std::shared_ptr<VolumeGLMock> gl = std::make_shared<VolumeGLMock>(v);
    std::shared_ptr<VolumeGLCUDAMock> glcudaGL = std::make_shared<VolumeGLCUDAMock>(gl);
    std::shared_ptr<VolumeGLCUDAMock> glcuda = std::make_shared<VolumeGLCUDAMock>(v);

    // The CPU volume data is shared among all objects.
	assert(gl->getData() == glcudaGL->getData());
	assert(glcudaGL->getData() == glcuda->getData());

	// when VolumeGLCUDA is initiated with VolumeGL,
	// the OpenGL texture is shared,
	// otherwise the OpenGL textures are different.
	assert(gl->getTexture() == glcudaGL->getTexture());
    assert(gl->getTexture() != glcuda->getTexture());

	return 0;
}
