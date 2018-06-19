#pragma once

#include "common/exports.hpp"


// https://blog.molecular-matters.com/2014/02/21/schema-based-entity-component-data-for-fast-iteration-times/

// http://bitsquid.blogspot.co.at/2011/09/managing-decoupling-part-4-id-lookup.html
class  MA_API RenderComponent
{
public:
    void render();
    //{
    //    /* Work with and modify state... */
    //}

private:
    // Mesh, textures, shaders, etc. ...
};
