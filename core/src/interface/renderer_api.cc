#ifndef SOFTRD_RENDERER_API_H_
#define SOFTRD_RENDERER_API_H_

#include <vector>

namespace softrd {

class RendererAPI {
   public:
    RendererAPI(const int width, const int height);
    void RunExample();
    ~RendererAPI();

   private:
};

}  // namespace softrd

#endif  // SOFTRD_RENDERER_API_H_