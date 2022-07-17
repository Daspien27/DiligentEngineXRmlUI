#include "Application.h"

#include "DiligentCore/Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h"

namespace {

	int convert_glfw_key_mods_to_rml(int glfw_mods)
	{
		int key_modifier_state = 0;

		if (GLFW_MOD_SHIFT & glfw_mods)
			key_modifier_state |= Rml::Input::KM_SHIFT;

		if (GLFW_MOD_CONTROL & glfw_mods)
			key_modifier_state |= Rml::Input::KM_CTRL;

		if (GLFW_MOD_ALT & glfw_mods)
			key_modifier_state |= Rml::Input::KM_ALT;

		if (GLFW_MOD_CAPS_LOCK & glfw_mods)
			key_modifier_state |= Rml::Input::KM_SCROLLLOCK;

		if (GLFW_MOD_NUM_LOCK & glfw_mods)
			key_modifier_state |= Rml::Input::KM_NUMLOCK;

		return key_modifier_state;
	}

	Rml::Input::KeyIdentifier convert_glfw_key_to_rml(int glfw_key)
	{
		switch (glfw_key)
		{
		case GLFW_KEY_A:             return Rml::Input::KI_A;
		case GLFW_KEY_B:             return Rml::Input::KI_B;
		case GLFW_KEY_C:             return Rml::Input::KI_C;
		case GLFW_KEY_D:             return Rml::Input::KI_D;
		case GLFW_KEY_E:             return Rml::Input::KI_E;
		case GLFW_KEY_F:             return Rml::Input::KI_F;
		case GLFW_KEY_G:             return Rml::Input::KI_G;
		case GLFW_KEY_H:             return Rml::Input::KI_H;
		case GLFW_KEY_I:             return Rml::Input::KI_I;
		case GLFW_KEY_J:             return Rml::Input::KI_J;
		case GLFW_KEY_K:             return Rml::Input::KI_K;
		case GLFW_KEY_L:             return Rml::Input::KI_L;
		case GLFW_KEY_M:             return Rml::Input::KI_M;
		case GLFW_KEY_N:             return Rml::Input::KI_N;
		case GLFW_KEY_O:             return Rml::Input::KI_O;
		case GLFW_KEY_P:             return Rml::Input::KI_P;
		case GLFW_KEY_Q:             return Rml::Input::KI_Q;
		case GLFW_KEY_R:             return Rml::Input::KI_R;
		case GLFW_KEY_S:             return Rml::Input::KI_S;
		case GLFW_KEY_T:             return Rml::Input::KI_T;
		case GLFW_KEY_U:             return Rml::Input::KI_U;
		case GLFW_KEY_V:             return Rml::Input::KI_V;
		case GLFW_KEY_W:             return Rml::Input::KI_W;
		case GLFW_KEY_X:             return Rml::Input::KI_X;
		case GLFW_KEY_Y:             return Rml::Input::KI_Y;
		case GLFW_KEY_Z:             return Rml::Input::KI_Z;

		case GLFW_KEY_0:             return Rml::Input::KI_0;
		case GLFW_KEY_1:             return Rml::Input::KI_1;
		case GLFW_KEY_2:             return Rml::Input::KI_2;
		case GLFW_KEY_3:             return Rml::Input::KI_3;
		case GLFW_KEY_4:             return Rml::Input::KI_4;
		case GLFW_KEY_5:             return Rml::Input::KI_5;
		case GLFW_KEY_6:             return Rml::Input::KI_6;
		case GLFW_KEY_7:             return Rml::Input::KI_7;
		case GLFW_KEY_8:             return Rml::Input::KI_8;
		case GLFW_KEY_9:             return Rml::Input::KI_9;

		case GLFW_KEY_BACKSPACE:     return Rml::Input::KI_BACK;
		case GLFW_KEY_TAB:           return Rml::Input::KI_TAB;

		case GLFW_KEY_ENTER:         return Rml::Input::KI_RETURN;

		case GLFW_KEY_PAUSE:         return Rml::Input::KI_PAUSE;
		case GLFW_KEY_CAPS_LOCK:     return Rml::Input::KI_CAPITAL;

		case GLFW_KEY_ESCAPE:        return Rml::Input::KI_ESCAPE;

		case GLFW_KEY_SPACE:         return Rml::Input::KI_SPACE;
		case GLFW_KEY_PAGE_UP:       return Rml::Input::KI_PRIOR;
		case GLFW_KEY_PAGE_DOWN:     return Rml::Input::KI_NEXT;
		case GLFW_KEY_END:           return Rml::Input::KI_END;
		case GLFW_KEY_HOME:          return Rml::Input::KI_HOME;
		case GLFW_KEY_LEFT:          return Rml::Input::KI_LEFT;
		case GLFW_KEY_UP:            return Rml::Input::KI_UP;
		case GLFW_KEY_RIGHT:         return Rml::Input::KI_RIGHT;
		case GLFW_KEY_DOWN:          return Rml::Input::KI_DOWN;
		case GLFW_KEY_PRINT_SCREEN:  return Rml::Input::KI_SNAPSHOT;
		case GLFW_KEY_INSERT:        return Rml::Input::KI_INSERT;
		case GLFW_KEY_DELETE:        return Rml::Input::KI_DELETE;

		case GLFW_KEY_LEFT_SUPER:    return Rml::Input::KI_LWIN;
		case GLFW_KEY_RIGHT_SUPER:   return Rml::Input::KI_RWIN;

		case GLFW_KEY_KP_0:          return Rml::Input::KI_NUMPAD0;
		case GLFW_KEY_KP_1:          return Rml::Input::KI_NUMPAD1;
		case GLFW_KEY_KP_2:          return Rml::Input::KI_NUMPAD2;
		case GLFW_KEY_KP_3:          return Rml::Input::KI_NUMPAD3;
		case GLFW_KEY_KP_4:          return Rml::Input::KI_NUMPAD4;
		case GLFW_KEY_KP_5:          return Rml::Input::KI_NUMPAD5;
		case GLFW_KEY_KP_6:          return Rml::Input::KI_NUMPAD6;
		case GLFW_KEY_KP_7:          return Rml::Input::KI_NUMPAD7;
		case GLFW_KEY_KP_8:          return Rml::Input::KI_NUMPAD8;
		case GLFW_KEY_KP_9:          return Rml::Input::KI_NUMPAD9;
		case GLFW_KEY_KP_ENTER:      return Rml::Input::KI_NUMPADENTER;
		case GLFW_KEY_KP_MULTIPLY:   return Rml::Input::KI_MULTIPLY;
		case GLFW_KEY_KP_ADD:        return Rml::Input::KI_ADD;
		case GLFW_KEY_KP_SUBTRACT:   return Rml::Input::KI_SUBTRACT;
		case GLFW_KEY_KP_DECIMAL:    return Rml::Input::KI_DECIMAL;
		case GLFW_KEY_KP_DIVIDE:     return Rml::Input::KI_DIVIDE;

		case GLFW_KEY_F1:            return Rml::Input::KI_F1;
		case GLFW_KEY_F2:            return Rml::Input::KI_F2;
		case GLFW_KEY_F3:            return Rml::Input::KI_F3;
		case GLFW_KEY_F4:            return Rml::Input::KI_F4;
		case GLFW_KEY_F5:            return Rml::Input::KI_F5;
		case GLFW_KEY_F6:            return Rml::Input::KI_F6;
		case GLFW_KEY_F7:            return Rml::Input::KI_F7;
		case GLFW_KEY_F8:            return Rml::Input::KI_F8;
		case GLFW_KEY_F9:            return Rml::Input::KI_F9;
		case GLFW_KEY_F10:           return Rml::Input::KI_F10;
		case GLFW_KEY_F11:           return Rml::Input::KI_F11;
		case GLFW_KEY_F12:           return Rml::Input::KI_F12;
		case GLFW_KEY_F13:           return Rml::Input::KI_F13;
		case GLFW_KEY_F14:           return Rml::Input::KI_F14;
		case GLFW_KEY_F15:           return Rml::Input::KI_F15;
		case GLFW_KEY_F16:           return Rml::Input::KI_F16;
		case GLFW_KEY_F17:           return Rml::Input::KI_F17;
		case GLFW_KEY_F18:           return Rml::Input::KI_F18;
		case GLFW_KEY_F19:           return Rml::Input::KI_F19;
		case GLFW_KEY_F20:           return Rml::Input::KI_F20;
		case GLFW_KEY_F21:           return Rml::Input::KI_F21;
		case GLFW_KEY_F22:           return Rml::Input::KI_F22;
		case GLFW_KEY_F23:           return Rml::Input::KI_F23;
		case GLFW_KEY_F24:           return Rml::Input::KI_F24;

		case GLFW_KEY_NUM_LOCK:      return Rml::Input::KI_NUMLOCK;
		case GLFW_KEY_SCROLL_LOCK:   return Rml::Input::KI_SCROLL;

		case GLFW_KEY_LEFT_SHIFT:    return Rml::Input::KI_LSHIFT;
		case GLFW_KEY_LEFT_CONTROL:  return Rml::Input::KI_LCONTROL;
		case GLFW_KEY_RIGHT_SHIFT:   return Rml::Input::KI_RSHIFT;
		case GLFW_KEY_RIGHT_CONTROL: return Rml::Input::KI_RCONTROL;
		case GLFW_KEY_MENU:          return Rml::Input::KI_LMENU;

		case GLFW_KEY_KP_EQUAL:      return Rml::Input::KI_OEM_NEC_EQUAL;
		default: break;
		}

		return Rml::Input::KI_UNKNOWN;
	}
}

void application::process_framebuffer_size_callback(application& app, int width, int height) {
	if (app.context)
		app.context->SetDimensions(Rml::Vector2i(width, height));
}

void application::process_window_content_scale_callback(application& app, float xscale, float yscale) {
	if (app.context)
		app.context->SetDensityIndependentPixelRatio(xscale);
}

inline void application::process_key_callback(application& app, int glfw_key, int scancode, int glfw_action, int glfw_mods) {
	app.last_glfw_mods = glfw_mods;
}

inline void application::process_char_callback(application& app, unsigned int codepoint) {
	if (app.context) {
		app.context->ProcessTextInput(static_cast<Rml::Character>(codepoint));
	}
}

inline void application::process_cursor_enter_callback(application& app, int entered) {

	if (app.context && !entered) {
		double x, y;
		glfwGetCursorPos(app.window, &x, &y);
		app.context->ProcessMouseMove(static_cast<int> (x), static_cast<int> (y),
			app.last_rml_mods());
	}
}

inline void application::process_cursor_pos_callback(application& app, double xpos, double ypos) {
	if (app.context) {
		app.context->ProcessMouseMove(static_cast<int> (xpos), static_cast<int> (ypos),
			app.last_rml_mods());
	}
}

inline void application::process_mouse_button_callback(application& app, int button, int glfw_action, int glfw_mods) {
	app.last_glfw_mods = glfw_mods;

	if (app.context) {
		switch (glfw_action)
		{
		case GLFW_PRESS:
			app.context->ProcessMouseButtonDown(button, app.last_rml_mods());
			break;
		case GLFW_RELEASE:
			app.context->ProcessMouseButtonUp(button, app.last_rml_mods());
			break;
		}
	}
}

inline void application::process_scroll_callback(application& app, double xoffset, double yoffset) {
	if (app.context) {
		app.context->ProcessMouseWheel(static_cast<float> (-yoffset), app.last_rml_mods());
	}
}

inline application& application::get_application_ref(GLFWwindow* window) {
	auto user_pointer = glfwGetWindowUserPointer(window);

	if (!user_pointer) throw std::runtime_error("Unable to retrieve window user pointer.");

	return *reinterpret_cast<application*> (user_pointer);
}

inline void application::setup_callbacks() {

	// Window events
	glfwSetFramebufferSizeCallback(window, app_callbacks<&application::process_framebuffer_size_callback>());
	glfwSetWindowContentScaleCallback(window, app_callbacks<&application::process_window_content_scale_callback>());

	//Key events

	glfwSetKeyCallback(window, app_callbacks<&application::process_key_callback>());
	glfwSetCharCallback(window, app_callbacks<&application::process_char_callback>());

	// Mouse input
	glfwSetCursorEnterCallback(window, app_callbacks<&application::process_cursor_enter_callback>());
	glfwSetCursorPosCallback(window, app_callbacks<&application::process_cursor_pos_callback>());
	glfwSetMouseButtonCallback(window, app_callbacks<&application::process_mouse_button_callback>());
	glfwSetScrollCallback(window, app_callbacks<&application::process_scroll_callback>());
}

inline void application::initialize_glfw(const application_build_params& appbp) {
	if (auto res = glfwInit(); res == GLFW_FALSE) {
		throw std::runtime_error("GLFW failed to initialize.");
	}

	if (!glfwVulkanSupported()) {
		throw std::runtime_error("GLFW failed to initialize Vulkan.");
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, appbp.allow_resize ? GLFW_TRUE : GLFW_FALSE);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

	window = glfwCreateWindow(appbp.width, appbp.height, appbp.application_name.c_str(), nullptr, nullptr);

	glfwSetWindowUserPointer(window, this);

	setup_callbacks();

}

void application::initialize_diligent_engine(const application_build_params& appbp) {
	using namespace Diligent;
	EngineVkCreateInfo engine_ci;

	auto vk_factory = GetEngineFactoryVk();
	vk_factory->CreateDeviceAndContextsVk(engine_ci, &device, &immediate_context);

	auto handle = glfwGetWin32Window(window);

	if (!swap_chain && handle != nullptr) {
		Win32NativeWindow native_window{ handle };

		SwapChainDesc scdesc;
		scdesc.ColorBufferFormat = Diligent::TEXTURE_FORMAT::TEX_FORMAT_BGRA8_UNORM;
		scdesc.DepthBufferFormat = TEX_FORMAT_D32_FLOAT;

		vk_factory->CreateSwapChainVk(device, immediate_context, scdesc, native_window, &swap_chain);
	}
}

struct ApplicationData {
	bool show_text = true;
	Rml::String animal = "dog";
} my_data;

void application::initialize_rml(const application_build_params& appbp)
{
	rml_system_interface = std::make_unique<application_system_interface>(*this);
	rml_render_interface = std::make_unique<diligent_rml_render_interface>(*this);

	Rml::SetSystemInterface(rml_system_interface.get());
	Rml::SetRenderInterface(rml_render_interface.get());

	Rml::Initialise();

	context = Rml::CreateContext(appbp.application_name, Rml::Vector2i(appbp.width, appbp.height));

	{
		// Tell RmlUi to load the given fonts.
		Rml::LoadFontFace("LatoLatin-Regular.ttf");
		// Fonts can be registered as fallback fonts, as in this case to display emojis.
		Rml::LoadFontFace("NotoEmoji-Regular.ttf", true);

		// Set up data bindings to synchronize application data.
		if (Rml::DataModelConstructor constructor = context->CreateDataModel("animals"))
		{
			constructor.Bind("show_text", &my_data.show_text);
			constructor.Bind("animal", &my_data.animal);
		}

		// Now we are ready to load our document.
		Rml::ElementDocument* document = context->LoadDocument("hello_world.rml");
		document->Show();

		// Replace and style some text in the loaded document.
		Rml::Element* element = document->GetElementById("world");
		element->SetInnerRML(reinterpret_cast<const char*>(u8"🌍"));
		element->SetProperty("font-size", "1.5em");
	}

}

void application::init(const application_build_params& appbp) {
	initialize_glfw(appbp);
	initialize_diligent_engine(appbp);
	initialize_rml(appbp);
}

void application::poll_events()
{
	glfwPollEvents();
}

bool application::should_terminate()
{
	return glfwWindowShouldClose(window);
}

void application::update()
{
	if (context) {
		context->Update();
	}
}

void application::render()
{
	if (rml_render_interface) {
		rml_render_interface->begin_frame();
	}

	if (context) {
		context->Render();
	}

	if (rml_render_interface) {
		rml_render_interface->present_frame();
	}
}

int application::last_rml_mods() const {
	return convert_glfw_key_mods_to_rml(last_glfw_mods);
}

application::application(const application_build_params& appbp) {
	init(appbp);
}

application::~application()
{
	Rml::Shutdown();
	glfwTerminate();
}

void application::run() {
	while (!should_terminate()) {
		poll_events();

		update();

		render();
	}
}


application_system_interface::application_system_interface(application& app_in) : app(app_in), start(std::chrono::high_resolution_clock::now()) {
}

double application_system_interface::GetElapsedTime()
{
	auto last = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = last - start;
	return elapsed.count();
}

#include <limits>
#include "DiligentCore/Graphics/GraphicsTools/interface/MapHelper.hpp"
#include "DiligentTools/TextureLoader/interface/TextureUtilities.h"

namespace {
	template <std::floating_point T>
	consteval Diligent::VALUE_TYPE convert_numeric_type_to_diligent_value_type() {
		switch (8 * sizeof(T)) {
		case 16: return Diligent::VT_FLOAT16;
		case 32: return Diligent::VT_FLOAT32;
		default: return Diligent::VT_UNDEFINED;
		}
	}

	template <std::signed_integral T>
	consteval Diligent::VALUE_TYPE convert_numeric_type_to_diligent_value_type() {
		switch (8 * sizeof(T)) {
		case 8: return Diligent::VT_INT8;
		case 16: return Diligent::VT_INT16;
		case 32: return Diligent::VT_INT32;
		default: return Diligent::VT_UNDEFINED;
		}
	}

	template <std::unsigned_integral T>
	consteval Diligent::VALUE_TYPE convert_numeric_type_to_diligent_value_type() {
		switch (8 * sizeof(T)) {
		case 8: return Diligent::VT_UINT8;
		case 16: return Diligent::VT_UINT16;
		case 32: return Diligent::VT_UINT32;
		default: return Diligent::VT_UNDEFINED;
		}
	}
}

diligent_rml_render_interface::diligent_rml_render_interface(application& app_in) : app(app_in) {
	create_pipeline_states();
}


static const char* rml_main_vertex_shader = R"(

cbuffer constants {
	float4x4 transform;
	float2   translate;
};

struct vs_input {
	float2 position   : ATTRIB0;
	float4 color0     : ATTRIB1;
	float2 tex_coord0 : ATTRIB2;
};

struct ps_input {
	float4 position   : SV_POSITION;
	float2 tex_coord  : TEX_COORD;
	float4 color      : COLOR0;
};

void main(in vs_input vs_in, out ps_input ps_in) {
	ps_in.tex_coord = vs_in.tex_coord0;
	ps_in.color     = vs_in.color0;

	float2 translated_pos = vs_in.position + translate;
	float4 out_position   = transform * float4(translated_pos, 0, 1);

    ps_in.position = out_position;
}
)";

static const char* rml_color_pixel_shader = R"(

struct ps_input {
	float4 position   : SV_POSITION;
	float2 tex_coord  : TEX_COORD;
	float4 color      : COLOR0;
};

struct ps_output {
    float4 color : SV_TARGET;
};

void main(in ps_input ps_in, out ps_output ps_out) {
    ps_out.color = ps_in.color;
    ps_out.color = float4(1.0,0,0,1);
}
)";

static const char* rml_texture_pixel_shader = R"(

Texture2D    _texture;
SamplerState _texture_sampler;

struct ps_input {
	float4 position   : SV_POSITION;
	float2 tex_coord  : TEX_COORD;
	float4 color      : COLOR0;
};

struct ps_output {
    float4 color : SV_TARGET;
};

void main(in ps_input ps_in, out ps_output ps_out) {
	float4 tex_color = _texture.Sample(_texture_sampler, ps_in.tex_coord);
    ps_out.color = mul(ps_in.color, tex_color);
}
)";


namespace {
	// uniform buffer for vertex shader
	struct alignas(16) constants {
		Rml::Matrix4f transform;
		Rml::Vector2f translate;
	};
}

void diligent_rml_render_interface::create_pipeline_states()
{
	using namespace Diligent;
	GraphicsPipelineStateCreateInfo pipeline_state_create_info;


	pipeline_state_create_info.PSODesc.PipelineType = PIPELINE_TYPE_GRAPHICS;
	pipeline_state_create_info.GraphicsPipeline.NumRenderTargets = 1;
	pipeline_state_create_info.GraphicsPipeline.RTVFormats[0] = app.swap_chain->GetDesc().ColorBufferFormat;
	pipeline_state_create_info.GraphicsPipeline.DSVFormat = app.swap_chain->GetDesc().DepthBufferFormat;
	pipeline_state_create_info.GraphicsPipeline.PrimitiveTopology = PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	pipeline_state_create_info.GraphicsPipeline.DepthStencilDesc.DepthEnable = false;
	pipeline_state_create_info.GraphicsPipeline.DepthStencilDesc.StencilEnable = true;

	StencilOpDesc stencil_desc;

	stencil_desc.StencilFunc = COMPARISON_FUNC_ALWAYS;
	stencil_desc.StencilFailOp = STENCIL_OP_KEEP;
	stencil_desc.StencilDepthFailOp = STENCIL_OP_KEEP;
	stencil_desc.StencilPassOp = STENCIL_OP_KEEP;

	pipeline_state_create_info.GraphicsPipeline.DepthStencilDesc.FrontFace = stencil_desc;

	BlendStateDesc blend_desc;
	blend_desc.RenderTargets[0].BlendEnable = true;
	blend_desc.RenderTargets[0].BlendOp = BLEND_OPERATION_ADD;
	blend_desc.RenderTargets[0].SrcBlend = BLEND_FACTOR_SRC_ALPHA;
	blend_desc.RenderTargets[0].DestBlend = BLEND_FACTOR_INV_SRC_ALPHA;

	pipeline_state_create_info.GraphicsPipeline.BlendDesc = blend_desc;
	pipeline_state_create_info.GraphicsPipeline.RasterizerDesc.CullMode = CULL_MODE_NONE;



	RefCntAutoPtr<IShader> vertex_shader;
	{
		ShaderCreateInfo ShaderCI;
		ShaderCI.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;
		ShaderCI.Desc.ShaderType = SHADER_TYPE_VERTEX;
		ShaderCI.EntryPoint = "main";
		ShaderCI.Desc.Name = "Rml vertex shader";
		ShaderCI.Source = rml_main_vertex_shader;
		app.device->CreateShader(ShaderCI, &vertex_shader);
	}

	RefCntAutoPtr<IShader> color_pixel_shader;
	{
		ShaderCreateInfo ShaderCI;
		ShaderCI.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;
		ShaderCI.Desc.ShaderType = SHADER_TYPE_PIXEL;
		ShaderCI.EntryPoint = "main";
		ShaderCI.Desc.Name = "Rml color shader";
		ShaderCI.Source = rml_color_pixel_shader;
		app.device->CreateShader(ShaderCI, &color_pixel_shader);
	}

	std::array LayoutElems = {
		LayoutElement{0, 0, 4, VT_FLOAT32, False},
		LayoutElement{1, 0, 2, VT_FLOAT32, False},
		LayoutElement{2, 0, 4, VT_FLOAT32, False}
	};

	pipeline_state_create_info.GraphicsPipeline.InputLayout.LayoutElements = LayoutElems.data();
	pipeline_state_create_info.GraphicsPipeline.InputLayout.NumElements = static_cast<unsigned int> (LayoutElems.size());

	pipeline_state_create_info.pVS = vertex_shader;
	pipeline_state_create_info.PSODesc.ResourceLayout.DefaultVariableType = SHADER_RESOURCE_VARIABLE_TYPE_STATIC;

	{
		BufferDesc CBDesc;
		CBDesc.Usage = USAGE_DYNAMIC;
		CBDesc.BindFlags = BIND_UNIFORM_BUFFER;
		CBDesc.CPUAccessFlags = CPU_ACCESS_WRITE;
		CBDesc.Name = "VS constant buffer";
		CBDesc.Size = sizeof(constants);
		app.device->CreateBuffer(CBDesc, nullptr, &rml_constants_buffer);
	}

	pipeline_state_create_info.PSODesc.Name = "Rml Color PSO";
	pipeline_state_create_info.pPS = color_pixel_shader;

	auto create_pso_and_srb = [&](pso_and_srb& pair) {
		app.device->CreateGraphicsPipelineState(pipeline_state_create_info, &pair.pipeline_state);
		pair.pipeline_state->GetStaticVariableByName(SHADER_TYPE_VERTEX, "constants")->Set(rml_constants_buffer);
		pair.pipeline_state->CreateShaderResourceBinding(&pair.shader_resource_binding, true);
	};

	pipeline_state_create_info.GraphicsPipeline.RasterizerDesc.ScissorEnable = false;
	create_pso_and_srb(rml_color);
	pipeline_state_create_info.GraphicsPipeline.RasterizerDesc.ScissorEnable = true;
	create_pso_and_srb(rml_color_w_scissor);

	RefCntAutoPtr<IShader> texture_pixel_shader;
	{
		ShaderCreateInfo ShaderCI;
		ShaderCI.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;
		ShaderCI.Desc.ShaderType = SHADER_TYPE_PIXEL;
		ShaderCI.EntryPoint = "main";
		ShaderCI.Desc.Name = "Rml texture shader";
		ShaderCI.Source = rml_texture_pixel_shader;
		app.device->CreateShader(ShaderCI, &texture_pixel_shader);
	}

	pipeline_state_create_info.PSODesc.Name = "Rml Texture PSO";
	pipeline_state_create_info.pPS = texture_pixel_shader;
	std::array Vars =
	{
		ShaderResourceVariableDesc{SHADER_TYPE_PIXEL, "_texture", SHADER_RESOURCE_VARIABLE_TYPE_DYNAMIC}
	};
	// clang-format on
	pipeline_state_create_info.PSODesc.ResourceLayout.Variables = Vars.data();
	pipeline_state_create_info.PSODesc.ResourceLayout.NumVariables = static_cast<unsigned int> (Vars.size());

	SamplerDesc SamLinearClampDesc
	{
		FILTER_TYPE_LINEAR, FILTER_TYPE_LINEAR, FILTER_TYPE_LINEAR,
		TEXTURE_ADDRESS_CLAMP, TEXTURE_ADDRESS_CLAMP, TEXTURE_ADDRESS_CLAMP
	};

	std::array ImtblSamplers =
	{
		ImmutableSamplerDesc {SHADER_TYPE_PIXEL, "_texture_sampler", SamLinearClampDesc}
	};

	pipeline_state_create_info.PSODesc.ResourceLayout.ImmutableSamplers = ImtblSamplers.data();
	pipeline_state_create_info.PSODesc.ResourceLayout.NumImmutableSamplers = static_cast<unsigned int> (ImtblSamplers.size());

	pipeline_state_create_info.GraphicsPipeline.RasterizerDesc.ScissorEnable = false;
	create_pso_and_srb(rml_texture);
	pipeline_state_create_info.GraphicsPipeline.RasterizerDesc.ScissorEnable = true;
	create_pso_and_srb(rml_texture_w_scissor);
}

void diligent_rml_render_interface::RenderGeometry(Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rml::TextureHandle texture, const Rml::Vector2f& translation)
{
	// Memory requirements
	Diligent::RefCntAutoPtr<Diligent::IBuffer> rml_vertex_buffer;
	Diligent::RefCntAutoPtr<Diligent::IBuffer> rml_index_buffer;

	//Compile geometry
	using namespace Diligent;
	BufferDesc vertex_buffer_descriptor;
	vertex_buffer_descriptor.Name = "Rml vertex buffer";
	vertex_buffer_descriptor.Usage = USAGE_IMMUTABLE;
	vertex_buffer_descriptor.BindFlags = BIND_VERTEX_BUFFER;
	vertex_buffer_descriptor.Size = num_vertices * sizeof(Rml::Vertex);
	BufferData vertex_buffer_data;
	vertex_buffer_data.pData = vertices;
	vertex_buffer_data.DataSize = num_vertices * sizeof(Rml::Vertex);
	app.device->CreateBuffer(vertex_buffer_descriptor, &vertex_buffer_data, &rml_vertex_buffer);

	BufferDesc IndBuffDesc;
	IndBuffDesc.Name = "Rml index buffer";
	IndBuffDesc.Usage = USAGE_IMMUTABLE;
	IndBuffDesc.BindFlags = BIND_INDEX_BUFFER;
	IndBuffDesc.Size = num_indices * sizeof(int);
	BufferData IBData;
	IBData.pData = indices;
	IBData.DataSize = num_indices * sizeof(int);
	app.device->CreateBuffer(IndBuffDesc, &IBData, &rml_index_buffer);

	//Render geometry

	Diligent::MapHelper<constants> cb_constants (app.immediate_context, rml_constants_buffer, Diligent::MAP_WRITE, Diligent::MAP_FLAG_DISCARD);
	constants c;
	c.transform = transform;
	c.translate = translation;
	*cb_constants = c;

	if (texture) {

		auto& pair = use_scissor ? rml_texture_w_scissor : rml_texture;
		app.immediate_context->SetPipelineState(pair.pipeline_state);
		auto& texture_view = rml_textures.at(texture);
		pair.shader_resource_binding->GetVariableByName(SHADER_TYPE_PIXEL, "_texture")->Set(texture_view);
		app.immediate_context->CommitShaderResources(pair.shader_resource_binding, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	}
	else {
		auto& pair = use_scissor ? rml_color_w_scissor : rml_color;
		app.immediate_context->SetPipelineState(pair.pipeline_state);
		app.immediate_context->CommitShaderResources(pair.shader_resource_binding, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	}


	Diligent::Uint64 offset = 0;
	Diligent::IBuffer* buffs[1] = { rml_vertex_buffer.RawPtr() };
	app.immediate_context->SetVertexBuffers(0, 1, buffs, &offset, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION, Diligent::SET_VERTEX_BUFFERS_FLAG_RESET);
	app.immediate_context->SetIndexBuffer(rml_index_buffer, 0, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	Diligent::DrawIndexedAttribs DrawAttrs;
	DrawAttrs.IndexType = VT_UINT32;// convert_numeric_type_to_diligent_value_type<int>(); // doesn't work for signed indices
	DrawAttrs.NumIndices = 6;

	DrawAttrs.Flags = Diligent::DRAW_FLAG_VERIFY_ALL;
	app.immediate_context->DrawIndexed(DrawAttrs);
}

void diligent_rml_render_interface::EnableScissorRegion(bool enable)
{
	use_scissor = enable;
}

void diligent_rml_render_interface::SetScissorRegion(int x, int y, int width, int height)
{
	Diligent::Rect scissor;
	scissor.left   = x;
    scissor.right  = x + width;
    scissor.top    = y;
    scissor.bottom = y + height;
	app.immediate_context->SetScissorRects(1, &scissor, viewport_width, viewport_height);
}

void diligent_rml_render_interface::SetTransform(const Rml::Matrix4f* new_transform)
{
	transform = projection;

	if (new_transform) {
		transform *= transform * (*new_transform);
	}
}


bool diligent_rml_render_interface::LoadTexture(Rml::TextureHandle& texture_handle, Rml::Vector2i& texture_dimensions, const Rml::String& source)
{
	using namespace Diligent;
	RefCntAutoPtr<Diligent::ITextureView> texture_view;
	TextureLoadInfo tex_load_info;
	tex_load_info.Name = "Loaded Texture";
	tex_load_info.IsSRGB = false;
	
	RefCntAutoPtr<ITexture> tex;
	CreateTextureFromFile(source.c_str(), tex_load_info, app.device, &tex);

	texture_view = tex->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);

	auto [loaded_texture, inserted] = rml_textures.try_emplace(texture_view->GetUniqueID(), texture_view);

	texture_handle = loaded_texture->first;
	texture_dimensions.x = texture_view->GetTexture()->GetDesc().Width;
	texture_dimensions.y = texture_view->GetTexture()->GetDesc().Height;
	return inserted;
}

bool diligent_rml_render_interface::GenerateTexture(Rml::TextureHandle& texture_handle, const Rml::byte* source, const Rml::Vector2i& source_dimensions)
{
	using namespace Diligent;
	RefCntAutoPtr<Diligent::ITextureView> texture_view;

	RefCntAutoPtr<ITexture> Tex;
	{
		TextureDesc tex_desc;
		tex_desc.Name = "Generated Texture";
		tex_desc.Type = RESOURCE_DIM_TEX_2D;
		tex_desc.Width = source_dimensions.x;
		tex_desc.Height = source_dimensions.y;
		tex_desc.ArraySize = 1;
		tex_desc.Format = TEX_FORMAT_RGBA8_UNORM;
		tex_desc.BindFlags = BIND_SHADER_RESOURCE | BIND_UNORDERED_ACCESS;

		std::array mipdata = {
			TextureSubResData{source, size_t{tex_desc.Width} * 4u}
		};

		for (int i = 0; i < mipdata[0].Stride; ++i) {
			source[i];
		}
		TextureData tex_data{mipdata.data(), static_cast<unsigned int> (mipdata.size())};
		app.device->CreateTexture(tex_desc, &tex_data, &Tex);
	}

	texture_view = Tex->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);

	auto [generated_texture, inserted] = rml_textures.try_emplace(texture_view->GetUniqueID(), texture_view);
	texture_handle = generated_texture->first;

	return inserted;
}

void diligent_rml_render_interface::ReleaseTexture(Rml::TextureHandle texture_handle)
{
	rml_textures.erase(texture_handle);
}

void diligent_rml_render_interface::set_viewport(int new_viewport_width, int new_viewport_height)
{
	viewport_width = new_viewport_width;
	viewport_height = new_viewport_height;
	
	app.swap_chain->Resize(viewport_width, viewport_height);
}

void diligent_rml_render_interface::begin_frame()
{
	auto current_render_target_view = app.swap_chain->GetCurrentBackBufferRTV();
	auto current_depth_stencil_view = app.swap_chain->GetDepthBufferDSV();
	
	app.immediate_context->SetRenderTargets(1, &current_render_target_view, current_depth_stencil_view, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	
	Rml::Vector4f ClearColor = { 0.f, 0.7f, 0.f, 1.f };
	app.immediate_context->ClearRenderTarget(current_render_target_view, ClearColor, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	app.immediate_context->ClearDepthStencil(current_depth_stencil_view, Diligent::CLEAR_DEPTH_FLAG | Diligent::CLEAR_STENCIL_FLAG, 1.f, 0, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	
	projection = Rml::Matrix4f::ProjectOrtho(0.0f, static_cast<float> (viewport_width), 
		                                     static_cast<float> (viewport_height), 0.0f, 
		                                     -10000.0f, 10000.0f);

	SetTransform(nullptr);
}

void diligent_rml_render_interface::present_frame()
{
	app.immediate_context->Flush();
	app.swap_chain->Present();
}
