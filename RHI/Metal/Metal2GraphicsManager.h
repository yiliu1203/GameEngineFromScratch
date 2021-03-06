#pragma once
#include "GraphicsManager.hpp"
#include "portable.hpp"
#include "IPipelineStateManager.hpp"

OBJC_CLASS(Metal2Renderer);

namespace My {
    class Metal2GraphicsManager : public GraphicsManager
    {
    public:
       	int Initialize() final;
	    void Finalize() final;

        void Draw() final;
        void Present() final;
    
        void SetPipelineState(const std::shared_ptr<PipelineState>& pipelineState) final;

        void DrawBatch(const std::vector<std::shared_ptr<DrawBatchContext>>& batches) final;

        int32_t GenerateCubeShadowMapArray(const uint32_t width, const uint32_t height, const uint32_t count) final;
        int32_t GenerateShadowMapArray(const uint32_t width, const uint32_t height, const uint32_t count) final;
        void BeginShadowMap(const Light& light, const int32_t shadowmap, const uint32_t width, const uint32_t height, const int32_t layer_index) final;
        void EndShadowMap(const int32_t shadowmap, const int32_t layer_index) final;
        void SetShadowMaps(const Frame& frame) final;
        void DestroyShadowMap(int32_t& shadowmap) final;

        // skybox
        void DrawSkyBox() final;

        // compute shader tasks
        void GenerateAndBindTextureForWrite(const char* id, const uint32_t slot_index, const uint32_t width, const uint32_t height) final;
        void Dispatch(const uint32_t width, const uint32_t height, const uint32_t depth) final;

        void SetRenderer(Metal2Renderer* renderer) { m_pRenderer = renderer; }

    private:
        void BeginScene(const Scene& scene) final;
        void EndScene() final;

        void BeginFrame(const Frame& frame) final;
        void EndFrame() final;

        void BeginPass() final;
        void EndPass() final;

        void BeginCompute() final;
        void EndCompute() final;

        void initializeGeometries(const Scene& scene) override;
        void initializeSkyBox(const Scene& scene) override;
        void initializeTerrain(const Scene& scene) override;

    private:
        Metal2Renderer* m_pRenderer;
    };
}
