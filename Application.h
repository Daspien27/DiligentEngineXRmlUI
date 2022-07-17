#pragma once

#define NOMINMAX

#include "ApplicationBuildParams.h"

#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

#define PLATFORM_WIN32 1
#define VULKAN_SUPPORTED
#include "DiligentCore/Graphics/GraphicsEngine/interface/RenderDevice.h"
#include "DiligentCore/Graphics/GraphicsEngine/interface/DeviceContext.h"
#include "DiligentCore/Graphics/GraphicsEngine/interface/SwapChain.h"
#include "DiligentCore/Common/interface/RefCntAutoPtr.hpp"

#include <RmlUi/Core.h>

class application;

class diligent_rml_render_interface : public Rml::RenderInterface
{
public:
	diligent_rml_render_interface(application& app_in);

	// Inherited via Rml::RenderInterface
	virtual void RenderGeometry(Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices,
		Rml::TextureHandle texture, const Rml::Vector2f& translation) override;
	virtual void EnableScissorRegion(bool enable) override;
	virtual void SetScissorRegion(int x, int y, int width, int height) override;
	virtual void SetTransform(const Rml::Matrix4f* transform) override;
	bool LoadTexture(Rml::TextureHandle& texture_handle, Rml::Vector2i& texture_dimensions, const Rml::String& source) override;
	bool GenerateTexture(Rml::TextureHandle& texture_handle, const Rml::byte* source, const Rml::Vector2i& source_dimensions) override;
	void ReleaseTexture(Rml::TextureHandle texture_handle) override;
	
	void begin_frame();
	void present_frame();
private:
	void set_viewport(int new_viewport_width, int new_viewport_height);
	void create_pipeline_states();

private:
	application& app;

	int viewport_width = 0;
	int viewport_height = 0;

	Rml::Matrix4f projection;
	Rml::Matrix4f transform;
	bool use_scissor = false;

	struct pso_and_srb {
		Diligent::RefCntAutoPtr<Diligent::IPipelineState> pipeline_state;
		Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding> shader_resource_binding;
	};
	pso_and_srb rml_color;
	pso_and_srb rml_color_w_scissor;
	pso_and_srb rml_texture;
	pso_and_srb rml_texture_w_scissor;

	Diligent::RefCntAutoPtr<Diligent::IBuffer>        rml_constants_buffer;

	std::unordered_map<Rml::TextureHandle, Diligent::RefCntAutoPtr<Diligent::ITextureView>> rml_textures;
	Diligent::RefCntAutoPtr<Diligent::IBuffer>        rml_vertex_buffer;
	Diligent::RefCntAutoPtr<Diligent::IBuffer>        rml_index_buffer;
};

class application_system_interface : public Rml::SystemInterface
{
public:
	application_system_interface(application& app_in);

	// Inherited via Rml::SystemInterface
	virtual double GetElapsedTime() override;
private:
	application& app;
	std::chrono::high_resolution_clock::time_point start;
};

template <typename callback_ptr>
struct is_application_callback_trait : std::false_type {};

template <typename ret, typename... args>
struct is_application_callback_trait<ret(*)(application&, args...)> : std::true_type {};

template <auto callback_ptr>
concept is_application_callback = is_application_callback_trait<decltype(callback_ptr)>::value;

class application {
	friend class diligent_rml_render_interface;
	friend class application_system_interface;

	static void process_framebuffer_size_callback(application& app, int width, int height);
	static void process_window_content_scale_callback(application& app, float xscale, [[maybe_unused]] float yscale);
	static void process_key_callback(application& app, int glfw_key, int scancode, int glfw_action, int glfw_mods);
	static void process_char_callback(application& app, unsigned int codepoint);
	static void process_cursor_enter_callback(application& app, int entered);
	static void process_cursor_pos_callback(application& app, double xpos, double ypos);
	static void process_mouse_button_callback(application& app, int button, int glfw_action, int glfw_mods);
	static void process_scroll_callback(application& app, [[maybe_unused]] double xoffset, double yoffset);

	static application& get_application_ref(GLFWwindow* window);

	template <auto callback_ptr> requires is_application_callback<callback_ptr>
		constexpr auto app_callbacks() {
			return [](GLFWwindow* window, auto... args) {
				auto& app = get_application_ref(window);
				callback_ptr(app, args...);
			};
		}

	void setup_callbacks();
	void initialize_glfw(const application_build_params& appbp);
	void initialize_diligent_engine(const application_build_params& appbp);
	void initialize_rml(const application_build_params& appbp);
	void init(const application_build_params& appbp);

	void poll_events();
	bool should_terminate();

	void update();
	void render();

	int last_rml_mods() const;
public:
	application(const application_build_params& appbp);
	~application();
	void run();
private:

	GLFWwindow* window;
	int last_glfw_mods;

	Diligent::RefCntAutoPtr<Diligent::IRenderDevice> device;
	Diligent::RefCntAutoPtr<Diligent::IDeviceContext> immediate_context;
	Diligent::RefCntAutoPtr<Diligent::ISwapChain> swap_chain;

	std::unique_ptr<application_system_interface> rml_system_interface;
	std::unique_ptr<diligent_rml_render_interface> rml_render_interface;
	Rml::Context* context;
};