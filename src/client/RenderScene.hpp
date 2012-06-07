#ifndef _RENDERSCENE_HPP_
#define _RENDERSCENE_HPP_

class GFX;

class RenderScene
{
    public:
        RenderScene(GFX* parent);
        virtual void run() = 0;
        virtual void render() = 0;
    protected:
        GFX* parent;
};

#endif //_RENDERSCENE_HPP_