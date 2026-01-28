/*
  Virtual buffer object OpenGL extension function prototypes (under Windows)
*/

#ifndef NEXDYNFEM_VBO_H
#define NEXDYNFEM_VBO_H

#if defined(_WIN32) || defined(WIN32)

#include <windows.h>

#include <GL/gl.h>
#include <GL/glext.h>

#endif
namespace nexdynfem
{

// call this to initialize the VBO extension
// returns "true" on success and "false" on failure
// if successful, you can then use "glBindBufferARB", 
//   "glBufferDataARB" and "glGenBuffersARB", and "glDeleteBuffersARB"
bool InitializeVBOs(void);

}//namespace nexdynfem

#endif 

