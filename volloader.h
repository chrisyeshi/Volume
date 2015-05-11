//
//
//
//
// factory class for creating the real volume loader depend on the file type
//
//
//
//

#ifndef VOLLOADER_H
#define VOLLOADER_H

#include <QString>
#include <memory>
#include <map>
#include "volume.h"

namespace yy
{

class VolLoader
{
public:
    virtual ~VolLoader() {}
    virtual std::shared_ptr<Volume> open() = 0;
};

} // namespace yy

#endif // VOLLOADER_H
